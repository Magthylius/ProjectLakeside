// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PL_InteractableObject.h"
#include "GameFramework/Actor.h"
#include "PL_InteractableButton.generated.h"

UCLASS()
class PROJECTLAKESIDE_API APL_InteractableButton : public AActor, public IPL_InteractableObject
{
	GENERATED_BODY()
	
public:	
	APL_InteractableButton();

protected:
	virtual void StartInteraction() override;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
};
