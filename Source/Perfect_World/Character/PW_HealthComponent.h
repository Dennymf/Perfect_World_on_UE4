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

	UPROPERTY(BlueprintAssignable, Category = "Health")
		FOnHPChange OnHPChange;
	UPROPERTY(BlueprintAssignable, Category = "Health")
		FOnDead OnDead;

	uint32 CurrentHP = 1;
	uint32 MaxHP = 100;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	int32 GetCurrentHealth();
	UFUNCTION(BlueprintCallable, Category = "Health")
		int32 GetMaxHealth();
	UFUNCTION(BlueprintCallable, Category = "Health")
		void SetCurrentHealth(int32 Value);
	UFUNCTION(BlueprintCallable, Category = "Health")
		void SetMaxHealth(int32 Value);
	UFUNCTION(BlueprintCallable, Category = "Health")
		virtual void ChangeCurrentHealth(int32 Value);
	UFUNCTION(BlueprintNativeEvent)
		void DeadEvent();
};
