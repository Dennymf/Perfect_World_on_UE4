// Fill out your copyright notice in the Description page of Project Settings.


#include "PW_ManaComponent.h"

// Sets default values for this component's properties
UPW_ManaComponent::UPW_ManaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPW_ManaComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPW_ManaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int32 UPW_ManaComponent::GetCurrentMana()
{
	return CurrentMP;
}

int32 UPW_ManaComponent::GetMaxMana()
{
	return MaxMP;
}

void UPW_ManaComponent::SetCurrentMana(int32 Value)
{
	CurrentMP = Value;
	OnMPChange.Broadcast(CurrentMP, MaxMP);
}

void UPW_ManaComponent::SetMaxMana(int32 Value)
{
	MaxMP = Value;
	OnMPChange.Broadcast(CurrentMP, MaxMP);
}

void UPW_ManaComponent::ChangeCurrentMana(int32 Value)
{
	CurrentMP = std::max(0, std::min(static_cast<int32>(CurrentMP) + Value, static_cast<int32>(MaxMP)));
	OnMPChange.Broadcast(CurrentMP, MaxMP);
}

