// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PW_ManaComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMPChange, int32, CurMP, int32, MaxMP);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PERFECT_WORLD_API UPW_ManaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPW_ManaComponent();

	UPROPERTY(BlueprintAssignable, Category = "Mana");
	FOnMPChange OnMPChange;

	uint32 CurrentMP = 1;
	uint32 MaxMP = 100;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Mana")
		int32 GetCurrentMana();
	UFUNCTION(BlueprintCallable, Category = "Mana")
		int32 GetMaxMana();
	UFUNCTION(BlueprintCallable, Category = "Mana")
		void SetCurrentMana(int32 Value);
	UFUNCTION(BlueprintCallable, Category = "Mana")
		void SetMaxMana(int32 Value);
	UFUNCTION(BlueprintCallable, Category = "Mana")
		virtual void ChangeCurrentMana(int32 Value);
};
