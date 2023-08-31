// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "PL_MainCharacter.generated.h"


UCLASS(config=Game)
class APL_MainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APL_MainCharacter();
	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void PerformMove(const FInputActionValue& Value);
	void PerformLook(const FInputActionValue& Value);
	void PerformJetpack(const FInputActionValue& Value);

	void PerformObjectPull(const FInputActionValue& Value);
	void PerformInteraction(const FInputActionValue& Value);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UCameraComponent> FollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UParticleSystemComponent> ParticleSystemComponent;

	/*UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Settings|Gameplay", meta = (AllowPrivateAccess))
	FGameplayTagContainer PullObjectTags;*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Gameplay", meta = (AllowPrivateAccess))
	float PullObjectTraceRadius = 50.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Gameplay", meta = (AllowPrivateAccess))
	float PullObjectRange = 2000.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Gameplay", meta = (AllowPrivateAccess))
	float PullSpeed = 1.2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Gameplay", meta = (AllowPrivateAccess))
	float ObjectHoldHeight = 150.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Gameplay", meta = (AllowPrivateAccess))
	float ObjectHoldOrbitRange = 75.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Gameplay", meta = (AllowPrivateAccess))
	float ObjectLaunchForce = 2000.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Gameplay", meta = (AllowPrivateAccess))
	float InteractionRange = 200.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Gameplay", meta = (AllowPrivateAccess))
	TArray<TEnumAsByte<EObjectTypeQuery>> InteractionTypeQueries;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Gameplay", meta = (AllowPrivateAccess))
	float JetpackForce = 1000.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Input", meta = (AllowPrivateAccess))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Input", meta = (AllowPrivateAccess))
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Input", meta = (AllowPrivateAccess))
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Input", meta = (AllowPrivateAccess))
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Input", meta = (AllowPrivateAccess))
	TObjectPtr<UInputAction> PullObjectsAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Input", meta = (AllowPrivateAccess))
	TObjectPtr<UInputAction> InteractAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Input", meta = (AllowPrivateAccess))
	TObjectPtr<UInputAction> JetpackAction;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Runtime Data", meta = (AllowPrivateAccess))
	TWeakObjectPtr<AActor> PulledObject;

	bool bJetpackFireStarted = false;
};
