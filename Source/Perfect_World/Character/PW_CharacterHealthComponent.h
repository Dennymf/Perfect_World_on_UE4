// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PW_HealthComponent.h"

#include "PW_CharacterHealthComponent.generated.h"

/**
 * 
 */
UCLASS()
class PERFECT_WORLD_API UPW_CharacterHealthComponent : public UPW_HealthComponent
{
	GENERATED_BODY()
	
protected:
	bool bIsFight = false;
	float FightTimer = 0.0f;

public:
	void ChangeCurrentHealth(int32 Value) override;
	bool GetIsFight();
	void SetIsFight(bool Value);
	float GetFightTimer();
	void SetFightTimer(float Value);
};
