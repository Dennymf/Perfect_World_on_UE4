// Fill out your copyright notice in the Description page of Project Settings.


#include "PW_CharacterHealthComponent.h"

void UPW_CharacterHealthComponent::ChangeCurrentHealth(uint32 Value)
{
	Super::ChangeCurrentHealth(Value);
	bIsFight = true;
	FightTimer = 15.0f;
}

bool UPW_CharacterHealthComponent::GetIsFight()
{
	return bIsFight;
}

void UPW_CharacterHealthComponent::SetIsFight(bool Value)
{
	bIsFight = false;
}

float UPW_CharacterHealthComponent::GetFightTimer()
{
	return FightTimer;
;
}

void UPW_CharacterHealthComponent::SetFightTimer(float Value)
{
	FightTimer = Value;
}
