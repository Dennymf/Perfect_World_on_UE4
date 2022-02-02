// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PW_CharacteristicComponent.h"
#include "PW_CharacterHealthComponent.h"
#include "PW_CharacterManaComponent.h"

#include "PW_CharCharacteristicComponent.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFreePointChange, int32, FreePoint);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnXPChange, int32, XP, int32, NeedXP);

UCLASS()
class PERFECT_WORLD_API UPW_CharCharacteristicComponent : public UPW_CharacteristicComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
		class UPW_CharacterHealthComponent* CharHealthComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mana", meta = (AllowPrivateAccess = "true"))
		class UPW_CharacterManaComponent* CharManaComponent;
	uint8 MaxLevel = 105;
	uint32 CurrentXP = 0;
	uint32 NeededXP = 100;

	uint8 RegenerationHP = 5;
	uint8 RegenerationMP = 4;
	uint32 CurrentIntelligence = 5;
	uint32 CurrentAgility = 5;
	uint32 CurrentStrength = 5;
	uint32 CurrentEndurance = 5;
	uint32 FreePoint = 5;

public:
	UPW_CharCharacteristicComponent();

	UPROPERTY(BlueprintAssignable, Category = "Characteristic");
	FOnFreePointChange OnFreePointChange;
	UPROPERTY(BlueprintAssignable, Category = "Characteristic");
	FOnXPChange OnXPChange;

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		void ChangeCurrentXP(float ChangeValue);
	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		void ChangeMaxHP(float Value);
	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		void ChangeMaxMP(float Value);
	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		void ChangePhysDamage(float Value);
	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		void ChangeMagDamage(float Value);

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		int32 GetCurrentXP()
	{
		return CurrentXP;
	}

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		int32 GetNeededXP()
	{
		return NeededXP;
	}

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		int32 GetCurrentIntelligence()
	{
		return CurrentIntelligence;
	}

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		int32 GetCurrentStrength()
	{
		return CurrentStrength;
	}

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		int32 GetCurrentEndurance()
	{
		return CurrentEndurance;
	}

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		int32 GetCurrentAgility()
	{
		return CurrentAgility;
	}

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
	int32 GetFreePoint()
	{
		return FreePoint;
	}

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		UPW_CharacterHealthComponent* GetHealthComponent();

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		UPW_CharacterManaComponent* GetManaComponent();

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		void SetCurrentIntelligence(int32 value);

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		void SetCurrentStrength(int32 value);

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		void SetCurrentEndurance(int32 value);

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		void SetCurrentAgility(int32 value);

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		void SetFreePoint(int32 value);
};
