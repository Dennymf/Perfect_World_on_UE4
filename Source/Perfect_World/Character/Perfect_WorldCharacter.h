// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../FuncLibrary/Types.h"
#include "../Game/PW_GameInstance.h"
#include "Engine/DataTable.h"
#include "PW_CharCharacteristicComponent.h"

#include "Perfect_WorldCharacter.generated.h"

UCLASS(config = Game)
class APerfect_WorldCharacter : public ACharacter
{
	GENERATED_BODY()

		/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Cursor, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
		class UPW_CharCharacteristicComponent* CharCharacteristicComponent;

	class UWidget* statsWidget;

	float OldDistToCursor;
	int8 TickToCursor;

	ECharacterSpiritualCultivation Cultivation = ECharacterSpiritualCultivation::SpiritualAdept;

	float Timer = 1.0f;

	bool bIsJumping = false;
	int8 CurrentCountJump = 0;

public:
	APerfect_WorldCharacter();
	virtual void Tick(float DeltaSeconds) override;

	void MoveToCursorTick(float DeltaSeconds);

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void DoJump();

	void MoveToCursor();

	void CheckJump();

	void RegenerationTick(float DeltaSeconds);

	//void LevelUpTick();

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
};