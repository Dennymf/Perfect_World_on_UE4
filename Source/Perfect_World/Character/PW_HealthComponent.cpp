// Fill out your copyright notice in the Description page of Project Settings.


#include "PW_HealthComponent.h"

// Sets default values for this component's properties
UPW_HealthComponent::UPW_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPW_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPW_HealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int32 UPW_HealthComponent::GetCurrentHealth()
{
	return CurrentHP;
}

int32 UPW_HealthComponent::GetCurrentMaxHealth()
{

	return MaxHP;
}

void UPW_HealthComponent::SetCurrentHealth(int32 Value)
{
	CurrentHP = Value;
	OnHPChange.Broadcast(CurrentHP, MaxHP);
}

void UPW_HealthComponent::SetCurrentMaxHealth(int32 Value)
{
	MaxHP = Value;
	OnHPChange.Broadcast(CurrentHP, MaxHP);
}

void UPW_HealthComponent::ChangeCurrentHealth(int32 Value)
{
	CurrentHP = std::max(0, std::min(static_cast<int32>(CurrentHP) + Value, static_cast<int32>(MaxHP)));
	OnHPChange.Broadcast(CurrentHP, MaxHP);
	if (Value < 0)
	{
		DeadEvent();
	}
}

void UPW_HealthComponent::DeadEvent_Implementation()
{
	//BP
}

