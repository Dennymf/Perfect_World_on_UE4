// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Game/PW_GameInstance.h"
#include "../Character/PW_CharacteristicComponent.h"
#include "../Character/PW_HealthComponent.h"
#include "PW_EnemyBase.generated.h"

UCLASS()
class PERFECT_WORLD_API APW_EnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APW_EnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
		FName InitEnemyName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
		class UPW_CharacteristicComponent* CharacteristicComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
		class UPW_HealthComponent* HealthComponent;

	// 
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void InitCharacteristics(FName EnemyName);
};
