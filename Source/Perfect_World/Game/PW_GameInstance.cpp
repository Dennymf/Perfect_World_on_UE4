// Fill out your copyright notice in the Description page of Project Settings.


#include "PW_GameInstance.h"

bool UPW_GameInstance::GetEnemyInfoByName(FName NameEnemy, FEnemyInfo& OutInfo)
{
	bool bIsFind = false;
	FEnemyInfo* EnemyInfoRow;

	if (EnemyTable)
	{
		EnemyInfoRow = EnemyTable->FindRow<FEnemyInfo>(NameEnemy, "", false);
		if (EnemyInfoRow)
		{
			bIsFind = true;
			OutInfo = *EnemyInfoRow;
		}
	}
	return bIsFind;
}