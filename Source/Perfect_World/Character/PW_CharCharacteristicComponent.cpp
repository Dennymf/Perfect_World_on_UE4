// Fill out your copyright notice in the Description page of Project Settings.


#include "PW_CharCharacteristicComponent.h"

UPW_CharCharacteristicComponent::UPW_CharCharacteristicComponent()
{
	CharHealthComponent = CreateDefaultSubobject<UPW_CharacterHealthComponent>(TEXT("HealthComponent"));
	CharManaComponent = CreateDefaultSubobject<UPW_CharacterManaComponent>(TEXT("ManaComponent"));
}

void UPW_CharCharacteristicComponent::ChangeCurrentXP(float ChangeValue)
{
	CurrentXP += ChangeValue;
	OnXPChange.Broadcast(CurrentXP, NeededXP);
}

void UPW_CharCharacteristicComponent::ChangeMaxHP(float Value)
{
	uint32 MaxHP = CharHealthComponent->GetMaxHealth();
	CharHealthComponent->SetMaxHealth(MaxHP + (Value * 20));
}

void UPW_CharCharacteristicComponent::ChangeMaxMP(float Value)
{
	uint32 MaxMP = CharManaComponent->GetMaxMana();
	CharManaComponent->SetMaxMana(MaxMP + (Value * 20));
}

void UPW_CharCharacteristicComponent::ChangePhysDamage(float Value)
{
	uint32 MinDamage = GetMinDamagePhys();
	uint32 MaxDamage = GetMaxDamagePhys();
	SetMinPhysDamage(MinDamage + Value);
	SetMaxPhysDamage(MaxDamage + Value);
}

void UPW_CharCharacteristicComponent::ChangeMagDamage(float Value)
{
	uint32 MinDamage = GetMinDamageMagic();
	uint32 MaxDamage = GetMaxDamageMagic();
	SetMinMagicDamage(MinDamage + Value);
	SetMaxMagicDamage(MaxDamage + Value);
}

UPW_CharacterHealthComponent* UPW_CharCharacteristicComponent::GetHealthComponent()
{
	return CharHealthComponent;
}

UPW_CharacterManaComponent* UPW_CharCharacteristicComponent::GetManaComponent()
{
	return CharManaComponent;
}

void UPW_CharCharacteristicComponent::SetCurrentIntelligence(int32 value)
{
	ChangeMaxMP(value - CurrentIntelligence);
	ChangeMagDamage(value - CurrentIntelligence);
	CurrentIntelligence = value;
}

void UPW_CharCharacteristicComponent::SetCurrentStrength(int32 value)
{
	ChangePhysDamage(value - CurrentStrength);
	CurrentStrength = value;
}

void UPW_CharCharacteristicComponent::SetCurrentEndurance(int32 value)
{
	ChangeMaxHP(value - CurrentEndurance);
	CurrentEndurance = value;
}

void UPW_CharCharacteristicComponent::SetCurrentAgility(int32 value)
{
	ChangePhysDamage(value - CurrentAgility);
	CurrentAgility = value;
}

void UPW_CharCharacteristicComponent::SetFreePoint(int32 value)
{
	FreePoint = value;
	OnFreePointChange.Broadcast(FreePoint);
}