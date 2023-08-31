// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PL_InteractableObject.h"
#include "GameFramework/Actor.h"
#include "PL_InteractableActor.generated.h"

UCLASS(Abstract)
class PROJECTLAKESIDE_API APL_InteractableActor : public AActor, public IPL_InteractableObject
{
	GENERATED_BODY()
	
public:	
	APL_InteractableActor();

	virtual void StartInteraction() override;
	virtual void EndInteraction() override;
};
