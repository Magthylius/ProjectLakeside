// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PL_InteractableNPC.h"

APL_InteractableNPC::APL_InteractableNPC()
{
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh Component");
	RootComponent = SkeletalMeshComponent;
}

void APL_InteractableNPC::StartInteraction()
{
	Super::StartInteraction();
	StartDialogue();
}

void APL_InteractableNPC::StartDialogue()
{
	//! TODO: Implement dialogue system here
	if (GEngine) GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Yellow, "Knock knock, who's there?");
}
