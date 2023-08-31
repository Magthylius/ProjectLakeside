// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PL_InteractableDoor.h"

APL_InteractableDoor::APL_InteractableDoor()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	RootComponent = SceneRoot;

	DoorStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Door Static Mesh");
	DoorStaticMesh->SetMobility(EComponentMobility::Movable);
	DoorStaticMesh->SetEnableGravity(false);
	DoorStaticMesh->SetSimulatePhysics(false);
	DoorStaticMesh->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
}

void APL_InteractableDoor::StartInteraction()
{
	Super::StartInteraction();
	ToggleDoorOpening();
}

void APL_InteractableDoor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	DoorStaticMesh->SetRelativeRotation(FMath::RInterpTo(DoorStaticMesh->GetRelativeRotation(), TargetRotation, DeltaSeconds, 1.f), true);
}

void APL_InteractableDoor::ToggleDoorOpening()
{
	bIsOpened = !bIsOpened;
	TargetRotation = bIsOpened ? OpenedDoorRotation : ClosedDoorRotation;
}
