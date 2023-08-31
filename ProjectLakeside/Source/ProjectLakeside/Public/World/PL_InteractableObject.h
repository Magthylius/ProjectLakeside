// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PL_InteractableObject.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPL_InteractableObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTLAKESIDE_API IPL_InteractableObject
{
	GENERATED_BODY()

public:
	virtual void StartInteraction();
	virtual void EndInteraction();

protected:
	bool bWasInteracted = false;
};
