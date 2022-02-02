// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PW_CharacteristicComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelChange, int32, Level);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhysMinDamageChange, int32, MinPhysDamage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhysMaxDamageChange, int32, MaxPhysDamage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMagicMinDamageChange, int32, MinMagicDamage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMagicMaxDamageChange, int32, MaxMagicDamage);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PERFECT_WORLD_API UPW_CharacteristicComponent : public UActorComponent
{
	GENERATED_BODY()
	
	uint8 CurrentLevel = 1;
	uint32 MinDamagePhys = 1;
	uint32 MaxDamagePhys = 1;
	uint32 MinDamageMagic = 1;
	uint32 MaxDamageMagic = 1;

	float CurrentSpeed = 500.0f;
	float AttackSpeed = 1.0f;

public:	
	// Sets default values for this component's properties
	UPW_CharacteristicComponent();

	UPROPERTY(BlueprintAssignable, Category = "Characteristic");
	FOnLevelChange OnLevelChange;
	UPROPERTY(BlueprintAssignable, Category = "Characteristic")
	FOnPhysMinDamageChange OnPhysMinDamageChange;
	UPROPERTY(BlueprintAssignable, Category = "Characteristic")
	FOnPhysMaxDamageChange OnPhysMaxDamageChange;
	UPROPERTY(BlueprintAssignable, Category = "Characteristic")
	FOnMagicMinDamageChange OnMagicMinDamageChange;
	UPROPERTY(BlueprintAssignable, Category = "Characteristic")
	FOnMagicMaxDamageChange OnMagicMaxDamageChange;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		virtual int32 GetLevel();

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
	virtual int32 GetMinDamagePhys();

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		virtual int32 GetMaxDamagePhys();

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		virtual int32 GetMinDamageMagic();

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		virtual int32 GetMaxDamageMagic();

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		virtual float GetSpeed();

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		virtual float GetAttackSpeed();

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		virtual void SetCurrentLevel(int32 Value);

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		virtual void SetMinPhysDamage(int32 Value);

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		virtual void SetMaxPhysDamage(int32 Value);

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		virtual void SetMinMagicDamage(int32 Value);

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		virtual void SetMaxMagicDamage(int32 Value);

	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		virtual void SetSpeed(float Value);
	UFUNCTION(BlueprintCallable, Category = "Characteristic")
		virtual void SetAttackSpeed(float Value);
};
