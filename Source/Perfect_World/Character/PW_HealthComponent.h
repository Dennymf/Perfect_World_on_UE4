// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PW_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHPChange, int32, CurHP, int32, MaxHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDead);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PERFECT_WORLD_API UPW_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPW_HealthComponent();

	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintReadWrite, Category = "Health")
		FOnHPChange OnHPChange;
	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintReadWrite, Category = "Health")
		FOnDead OnDead;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	uint32 CurrentHP = 1;
	uint32 MaxHP = 100;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	int32 GetCurrentHealth();
	UFUNCTION(BlueprintCallable, Category = "Health")
		int32 GetCurrentMaxHealth();
	UFUNCTION(BlueprintCallable, Category = "Health")
		void SetCurrentHealth(uint32 Value);
	UFUNCTION(BlueprintCallable, Category = "Health")
		void SetCurrentMaxHealth(uint32 Value);
	UFUNCTION(BlueprintCallable, Category = "Health")
		virtual void ChangeCurrentHealth(uint32 Value);
	UFUNCTION(BlueprintNativeEvent)
		void DeadEvent();
};
