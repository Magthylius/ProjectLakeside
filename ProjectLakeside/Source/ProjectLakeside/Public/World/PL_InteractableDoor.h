// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "World/PL_InteractableActor.h"
#include "PL_InteractableDoor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLAKESIDE_API APL_InteractableDoor : public APL_InteractableActor
{
	GENERATED_BODY()

public:
	APL_InteractableDoor();

	virtual void StartInteraction() override;

protected:
	virtual void Tick(float DeltaSeconds) override;
	
	void ToggleDoorOpening();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<USceneComponent> SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> DoorStaticMesh;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Runtime Data", meta = (AllowPrivateAccess))
	bool bIsOpened = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess))
	FRotator ClosedDoorRotation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess))
	FRotator OpenedDoorRotation;
	
	FRotator TargetRotation;
};
