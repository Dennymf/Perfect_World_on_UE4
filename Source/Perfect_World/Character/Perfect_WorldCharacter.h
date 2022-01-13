// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../FuncLibrary/Types.h"
#include "Perfect_WorldCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHPChange, int32, CurHP, int32, MaxHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMPChange, int32, CurMP, int32, MaxMP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelChange, int32, Level);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFreePointChange, int32, FreePoint);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnXPChange, int32, XP, int32, NeedXP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPhysdamageChange, int32, MinPhysDamage, int32, MaxPhysDamage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMagdamageChange, int32, MinMagDamage, int32, MaxMagDamage);

UCLASS(config=Game)
class APerfect_WorldCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

	class UWidget* statsWidget;

	float OldDistToCursor;
	int8 TickToCursor;

	ECharacterSpiritualCultivation Cultivation = ECharacterSpiritualCultivation::SpiritualAdept;
	uint8 CurrentLevel = 1;
	uint8 MaxLevel = 105;
	uint32 CurrentXP = 0;
	uint32 NeededXP = 100;
	uint32 MinDamagePhys = 1;
	uint32 MaxDamagePhys = 1;
	uint32 MinDamageMagic = 1;
	uint32 MaxDamageMagic = 1;

	uint32 CurrentHP = 1;
	uint32 MaxHP = 100;
	uint32 CurrentMP = 1;
	uint32 MaxMP = 100;
	uint8 RegenerationHP = 5;
	uint8 RegenerationMP = 4;

	float Timer = 1.0f;
	uint32 CurrentIntelligence = 5;
	uint32 CurrentAgility = 5;
	uint32 CurrentStrength = 5;
	uint32 CurrentEndurance = 5;
	uint32 FreePoint = 5;
	float CurrentSpeed = 500.0f;
	float AttackSpeed = 1.0f;

	bool bIsFight = false;
	float FightTimer = 0.0f;

public:
	UPROPERTY(BlueprintAssignable, Category = "Stats");
	FOnHPChange OnHPChange;
	UPROPERTY(BlueprintAssignable, Category = "Stats");
	FOnMPChange OnMPChange;
	UPROPERTY(BlueprintAssignable, Category = "Stats");
	FOnLevelChange OnLevelChange;
	UPROPERTY(BlueprintAssignable, Category = "Stats");
	FOnFreePointChange OnFreePointChange;
	UPROPERTY(BlueprintAssignable, Category = "Stats");
	FOnXPChange OnXPChange;
	UPROPERTY(BlueprintAssignable, Category = "Stats");
	FOnPhysdamageChange OnPhysdamageChange;
	UPROPERTY(BlueprintAssignable, Category = "Stats");
	FOnMagdamageChange OnMagdamageChange;

	APerfect_WorldCharacter();
	virtual void Tick(float DeltaSeconds) override;

	void MoveToCursorTick(float DeltaSeconds);

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void MoveToCursor();

	void RegenerationTick(float DeltaSeconds);

	void LevelUpTick();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }
	UFUNCTION(BlueprintCallable)
	ECharacterSpiritualCultivation getStatus() { return Cultivation; }
	UFUNCTION(BlueprintCallable)
	void ChangeCurrentHealth(float ChangeValue);
	UFUNCTION(BlueprintCallable)
	void ChangeCurrentXP(float ChangeValue);
	UFUNCTION(BlueprintCallable)
	void ChangeMaxHP(float Value);
	UFUNCTION(BlueprintCallable)
	void ChangeMaxMP(float Value);
	UFUNCTION(BlueprintCallable)
	void ChangePhysDamage(float Value);
	UFUNCTION(BlueprintCallable)
	void ChangeMagDamage(float Value);

	UFUNCTION(BlueprintCallable)
	int32 GetHP()
	{
		return CurrentHP;
	}

	UFUNCTION(BlueprintCallable)
	int32 GetMP()
	{
		return CurrentMP;
	}

	UFUNCTION(BlueprintCallable)
	int32 GetMaxHP()
	{
		return MaxHP;
	}

	UFUNCTION(BlueprintCallable)
	int32 GetMaxMP()
	{
		return MaxMP;
	}

	UFUNCTION(BlueprintCallable)
	int32 GetLevel()
	{
		return CurrentLevel;
	}
	
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentXP()
	{
		return CurrentXP;
	}

	UFUNCTION(BlueprintCallable)
	int32 GetNeededXP()
	{
		return NeededXP;
	}

	UFUNCTION(BlueprintCallable)
	int32 GetMinDamagePhys()
	{
		return MinDamagePhys;
	}

	UFUNCTION(BlueprintCallable)
	int32 GetMaxDamagePhys()
	{
		return MaxDamagePhys;
	}

	UFUNCTION(BlueprintCallable)
	int32 GetMinDamageMagic()
	{
		return MinDamageMagic;
	}

	UFUNCTION(BlueprintCallable)
	int32 GetMaxDamageMagic()
	{
		return MaxDamageMagic;
	}

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentIntelligence()
	{
		return CurrentIntelligence;
	}

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentStrength()
	{
		return CurrentStrength;
	}

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentEndurance()
	{
		return CurrentEndurance;
	}

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentAgility()
	{
		return CurrentAgility;
	}

	UFUNCTION(BlueprintCallable)
	int32 GetFreePoint()
	{
		return FreePoint;
	}

	UFUNCTION(BlueprintCallable)
		void SetCurrentIntelligence(int32 value);

	UFUNCTION(BlueprintCallable)
		void SetCurrentStrength(int32 value);

	UFUNCTION(BlueprintCallable)
		void SetCurrentEndurance(int32 value);

	UFUNCTION(BlueprintCallable)
		void SetCurrentAgility(int32 value);

	UFUNCTION(BlueprintCallable)
		void SetFreePoint(int32 value);
};