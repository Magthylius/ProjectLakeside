// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PL_InteractableObject.h"

void IPL_InteractableObject::StartInteraction()
{
	bWasInteracted = true;
}

void IPL_InteractableObject::EndInteraction()
{
	bWasInteracted = false;
}
