// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PL_PullableObject.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPL_PullableObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTLAKESIDE_API IPL_PullableObject
{
	GENERATED_BODY()

public:
	virtual void StartPull() = 0;
	virtual void EndPull() = 0;

	virtual void Launch(FVector Direction) = 0;
};
