// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/PL_MainCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetSystemLibrary.h"
#include "World/PL_PullableObject.h"
#include "DrawDebugHelpers.h"
#include "World/PL_InteractableActor.h"
#include "World/PL_InteractableObject.h"

/* --- PUBLIC --- */

APL_MainCharacter::APL_MainCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	MovementComponent->bOrientRotationToMovement = true;
	MovementComponent->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 
	MovementComponent->JumpZVelocity = 700.f;
	MovementComponent->AirControl = 0.35f;
	MovementComponent->MaxWalkSpeed = 500.f;
	MovementComponent->MinAnalogWalkSpeed = 20.f;
	MovementComponent->BrakingDecelerationWalking = 2000.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 250.0f;
	CameraBoom->SocketOffset = FVector(100.f, 40.f, 75.f);
	CameraBoom->bUsePawnControlRotation = true; 

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

/* --- PROTECTED --- */

void APL_MainCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void APL_MainCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!PulledObject.IsValid()) return;
	AActor* PulledActor = PulledObject.Get();
	FVector Direction = PulledActor->GetActorLocation() - GetActorLocation();
	Direction.Normalize();
	Direction *= ObjectHoldOrbitRange;
	
	FVector ObjectHoldLocation = GetActorLocation() + Direction;
	ObjectHoldLocation.Z = ObjectHoldHeight;

	const FVector NewLocation = FMath::VInterpTo(PulledActor->GetActorLocation(), ObjectHoldLocation, DeltaSeconds, PullSpeed);
	PulledActor->SetActorLocation(NewLocation, true);
}

void APL_MainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APL_MainCharacter::PerformMove);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APL_MainCharacter::PerformLook);
		
		EnhancedInputComponent->BindAction(PullObjectsAction, ETriggerEvent::Triggered, this, &APL_MainCharacter::PerformObjectPull);
		EnhancedInputComponent->BindAction(PullObjectsAction, ETriggerEvent::Completed, this, &APL_MainCharacter::PerformObjectPull);
		
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APL_MainCharacter::PerformInteraction);
	}
}

void APL_MainCharacter::PerformMove(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (IsValid(Controller))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APL_MainCharacter::PerformLook(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (IsValid(Controller))
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APL_MainCharacter::PerformObjectPull(const FInputActionValue& Value)
{
	const bool bIsPressed = Value.Get<bool>();
	const bool bValidObject = PulledObject.IsValid();
	
	if (bIsPressed && !bValidObject)
	{
		//! Pick up and register to pull
		const FVector StartLocation = GetFollowCamera()->GetComponentLocation();
		const FVector EndLocation = StartLocation + GetFollowCamera()->GetForwardVector() * PullObjectRange;

		FHitResult HitResult;
		if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(), StartLocation, EndLocation, PullObjectTraceRadius, TraceTypeQuery1,
			false, TArray<AActor*>(), EDrawDebugTrace::ForOneFrame, HitResult, true))
		{
			AActor* PulledActor = HitResult.GetActor();
			IPL_PullableObject* Pullable = Cast<IPL_PullableObject>(PulledActor);
			if (Pullable == nullptr) return;
			Pullable->StartPull();
			PulledObject = PulledActor;
		}
	}
	else if (!bIsPressed && bValidObject)
	{
		//! End the pull and launch the object
		IPL_PullableObject* Pullable = Cast<IPL_PullableObject>(PulledObject);
		Pullable->EndPull();

		const FVector StartLocation = GetFollowCamera()->GetComponentLocation();
		const FVector EndLocation = StartLocation + GetFollowCamera()->GetForwardVector() * 1000.0f;

		FVector AimLocation = EndLocation;
		
		FHitResult HitResult;
		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility))
		{
			AimLocation = HitResult.Location;
		}

		FVector ForceDirection = AimLocation - PulledObject->GetActorLocation();
		ForceDirection.Normalize();
		ForceDirection *= ObjectLaunchForce;
		
		Pullable->Launch(ForceDirection);

		PulledObject.Reset();
	}
}

void APL_MainCharacter::PerformInteraction(const FInputActionValue& Value)
{
	if (!Value.Get<bool>()) return;

	TArray<AActor*> InteractableActors;
	if (UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), InteractionRange, InteractionTypeQueries,
		APL_InteractableActor::StaticClass(), TArray<AActor*>(),  InteractableActors))
	{
		//! TODO: Make this an actor component and cache entered actors instead
		Algo::Sort(InteractableActors, [this](const AActor* A, const AActor* B) { return GetDistanceTo(A) < GetDistanceTo(B); });
		IPL_InteractableObject* Interactable = Cast<IPL_InteractableObject>(InteractableActors[0]);

		if (Interactable == nullptr) return;
		Interactable->StartInteraction();
	}
}




