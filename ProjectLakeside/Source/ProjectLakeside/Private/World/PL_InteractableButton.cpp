// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PL_InteractableButton.h"

APL_InteractableButton::APL_InteractableButton()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Body Static Mesh");
	StaticMeshComponent->SetMobility(EComponentMobility::Static);
	StaticMeshComponent->SetEnableGravity(false);
	StaticMeshComponent->SetSimulatePhysics(false);
	RootComponent = StaticMeshComponent;
	
	PrimaryActorTick.bCanEverTick = true;
}

void APL_InteractableButton::StartInteraction()
{
	Super::StartInteraction();
	
	//! TODO: reset ball
	if (GEngine) GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Cyan, "RESET BALL");
}
