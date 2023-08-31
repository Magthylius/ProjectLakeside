// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PL_PullableActor.h"

/* --- PUBLIC --- */

APL_PullableActor::APL_PullableActor()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Body Static Mesh");
	StaticMeshComponent->SetMobility(EComponentMobility::Movable);
	StaticMeshComponent->SetEnableGravity(true);
	StaticMeshComponent->SetSimulatePhysics(true);
	RootComponent = StaticMeshComponent;
	
	PrimaryActorTick.bCanEverTick = true;
}

/* --- PROTECTED --- */

void APL_PullableActor::StartPull()
{
	StaticMeshComponent->SetEnableGravity(false);
	StaticMeshComponent->SetSimulatePhysics(false);
}

void APL_PullableActor::EndPull()
{
	StaticMeshComponent->SetEnableGravity(true);
	StaticMeshComponent->SetSimulatePhysics(true);
}

void APL_PullableActor::Launch(const FVector ForceDirection)
{
	StaticMeshComponent->SetPhysicsLinearVelocity(ForceDirection);
}

