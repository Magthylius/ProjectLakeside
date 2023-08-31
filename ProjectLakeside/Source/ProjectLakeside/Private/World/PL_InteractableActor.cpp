// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PL_InteractableActor.h"

APL_InteractableActor::APL_InteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APL_InteractableActor::StartInteraction()
{
	IPL_InteractableObject::StartInteraction();

	if (GEngine) GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Cyan, "Started interaction with " + GetName());
}

void APL_InteractableActor::EndInteraction()
{
	IPL_InteractableObject::EndInteraction();

	if (GEngine) GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Cyan, "Ended interaction with " + GetName());
}

