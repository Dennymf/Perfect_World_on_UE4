// Fill out your copyright notice in the Description page of Project Settings.


#include "PW_CharacteristicComponent.h"

// Sets default values for this component's properties
UPW_CharacteristicComponent::UPW_CharacteristicComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPW_CharacteristicComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPW_CharacteristicComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FName UPW_CharacteristicComponent::GetName()
{
	return Name;
}

int32 UPW_CharacteristicComponent::GetLevel()
{
	return CurrentLevel;
}

int32 UPW_CharacteristicComponent::GetMinDamagePhys()
{
	return MinDamagePhys;
}

int32 UPW_CharacteristicComponent::GetMaxDamagePhys()
{
	return MaxDamagePhys;
}

int32 UPW_CharacteristicComponent::GetMinDamageMagic()
{
	return MinDamageMagic;
}

int32 UPW_CharacteristicComponent::GetMaxDamageMagic()
{
	return MaxDamageMagic;
}

float UPW_CharacteristicComponent::GetSpeed()
{
	return CurrentSpeed;
}

float UPW_CharacteristicComponent::GetAttackSpeed()
{
	return AttackSpeed;

}

void UPW_CharacteristicComponent::SetName(FName Value)
{
	Name = Value;
	OnNameChange.Broadcast(Name);
}


void UPW_CharacteristicComponent::SetCurrentLevel(int32 Value)
{
	CurrentLevel = Value;
	OnLevelChange.Broadcast(CurrentLevel);
}

void UPW_CharacteristicComponent::SetMinPhysDamage(int32 Value)
{
	MinDamagePhys = Value;
	OnPhysMinDamageChange.Broadcast(MinDamagePhys);
}

void UPW_CharacteristicComponent::SetMaxPhysDamage(int32 Value)
{
	MaxDamagePhys = Value;
	OnPhysMaxDamageChange.Broadcast(MaxDamagePhys);
}

void UPW_CharacteristicComponent::SetMinMagicDamage(int32 Value)
{
	MinDamageMagic = Value;
	OnMagicMinDamageChange.Broadcast(MinDamageMagic);
}

void UPW_CharacteristicComponent::SetMaxMagicDamage(int32 Value)
{
	MaxDamageMagic = Value;
	OnMagicMaxDamageChange.Broadcast(MaxDamageMagic);
}

void UPW_CharacteristicComponent::SetSpeed(float Value)
{
	CurrentSpeed = Value;
}

void UPW_CharacteristicComponent::SetAttackSpeed(float Value)
{
	AttackSpeed = Value;
}