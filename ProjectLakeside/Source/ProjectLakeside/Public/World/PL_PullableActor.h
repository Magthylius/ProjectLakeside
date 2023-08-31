// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PL_PullableObject.h"
#include "GameFramework/Actor.h"
#include "PL_PullableActor.generated.h"

UCLASS()
class PROJECTLAKESIDE_API APL_PullableActor : public AActor, public IPL_PullableObject
{
	GENERATED_BODY()
	
public:	
	APL_PullableActor();

protected:
	virtual void StartPull() override;
	virtual void EndPull() override;

	virtual void Launch(FVector ForceDirection) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
};
