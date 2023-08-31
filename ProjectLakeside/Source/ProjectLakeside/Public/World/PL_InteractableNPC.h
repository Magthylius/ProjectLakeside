// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "World/PL_InteractableActor.h"
#include "PL_InteractableNPC.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLAKESIDE_API APL_InteractableNPC : public APL_InteractableActor
{
	GENERATED_BODY()

public:
	APL_InteractableNPC();
	
	virtual void StartInteraction() override;

protected:
	void StartDialogue();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
};
