// Fill out your copyright notice in the Description page of Project Settings.


#include "PW_EnemyBase.h"

// Sets default values
APW_EnemyBase::APW_EnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UPW_HealthComponent>(TEXT("HealthComponent"));
	CharacteristicComponent = CreateDefaultSubobject<UPW_CharacteristicComponent>(TEXT("CharacteristicComponent"));

}

// Called when the game starts or when spawned
void APW_EnemyBase::BeginPlay()
{
	Super::BeginPlay();
	InitCharacteristics(InitEnemyName);
}

// Called every frame
void APW_EnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APW_EnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APW_EnemyBase::InitCharacteristics(FName EnemyName)
{
	UPW_GameInstance* myGI = Cast<UPW_GameInstance>(GetWorld()->GetGameInstance());
	FEnemyInfo EnemyInfo;
	if (myGI)
	{
		if (myGI->GetEnemyInfoByName(EnemyName, EnemyInfo))
		{
			CharacteristicComponent->SetCurrentLevel(EnemyInfo.Level);
			CharacteristicComponent->SetMinPhysDamage(EnemyInfo.MinPhysDamage);
			CharacteristicComponent->SetMaxPhysDamage(EnemyInfo.MaxPhysDamage);
			CharacteristicComponent->SetMinMagicDamage(EnemyInfo.MinMagicDamage);
			CharacteristicComponent->SetMaxMagicDamage(EnemyInfo.MaxMagicDamage);
			CharacteristicComponent->SetSpeed(EnemyInfo.CurrentSpeed);
			CharacteristicComponent->SetAttackSpeed(EnemyInfo.AttackSpeed);
			HealthComponent->SetMaxHealth(EnemyInfo.MaxHP);
			HealthComponent->SetCurrentHealth(EnemyInfo.MaxHP);
		}
	}
}

