// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "Types.generated.h"

UENUM(BlueprintType)
enum class ECharacterSpiritualCultivation : uint8
{
	SpiritualAdept UMETA(DisplayName = "Spiritual Adept"),
	AwareOfPrinciple UMETA(DisplayName = "Aware Of Principle"),
	AwareOfHarmony UMETA(DisplayName = "Aware Of Harmony"),
	AwareOfDiscord UMETA(DisplayName = "Aware Of Discord"),
	AwareOfCoalescence UMETA(DisplayName = "Aware Of Coalescence"),
	Transcendent UMETA(DisplayName = "Transcendent"),
	EnlightenedOne UMETA(DisplayName = "EnlightenedOne"),
	AwareOfVacuity UMETA(DisplayName = "Aware Of Vacuity"),
	AwareOfTheMyriad UMETA(DisplayName = "Aware of the Myriad", value = 11),
	MasterOfHarmony UMETA(DisplayName = "Master of Harmony"),
	CelestialSage UMETA(DisplayName = "Celestial Sage"),
	AwareOfTheVoid UMETA(DisplayName = "Aware of the Void", value = 21),
	MasterOfDiscord UMETA(DisplayName = "Master of Discord"),
	CelestialDemon UMETA(DisplayName = "Celestial Demon"),
};

UENUM(BlueprintType)
enum class ECharacterRace : uint8
{
	Human UMETA(DisplayName = "Human"),
	Elf UMETA(DisplayName = "Elf"),
	Untamed UMETA(DisplayName = "Untamed")
};

USTRUCT(BlueprintType)
struct FEnemyInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristic")
		int32 MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristic")
		int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristic")
		int32 MaxPhysDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristic")
		int32 MinPhysDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristic")
		int32 MaxMagicDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristic")
		int32 MinMagicDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristic")
		float CurrentSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristic")
		float AttackSpeed;
};

UCLASS()
class PERFECT_WORLD_API UTypes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};
