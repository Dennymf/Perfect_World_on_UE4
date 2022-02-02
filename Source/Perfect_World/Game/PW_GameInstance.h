// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "../FuncLibrary/Types.h"
#include "Engine/DataTable.h"
#include "PW_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PERFECT_WORLD_API UPW_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Table")
		UDataTable* EnemyTable = nullptr;
	UFUNCTION(BlueprintCallable)
		bool GetEnemyInfoByName(FName NameEnemy, FEnemyInfo& OutInfo);
};
