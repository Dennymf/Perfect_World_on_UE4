// Copyright Epic Games, Inc. All Rights Reserved.

#include "Perfect_WorldCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Player.h"
#include "Engine/World.h"

//////////////////////////////////////////////////////////////////////////
// APerfect_WorldCharacter

APerfect_WorldCharacter::APerfect_WorldCharacter()
{
	//FEnemyInfo* Info;
	//Info = EnemyTable->FindRow<FEnemyInfo>("Росянка", "", false);
	//Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/Blueprints/Character/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	CursorToWorld->SetVisibility(false);

	CharCharacteristicComponent = CreateDefaultSubobject<UPW_CharCharacteristicComponent>(TEXT("CharacteristicComponent"));

	GetCharacterMovement()->MaxWalkSpeed = CharCharacteristicComponent->GetSpeed();
	GetCharacterMovement()->MinAnalogWalkSpeed = CharCharacteristicComponent->GetSpeed();
	GetCharacterMovement()->AirControl = 1.0f;
}

void APerfect_WorldCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (CursorToWorld->GetVisibleFlag())
	{
		MoveToCursorTick(DeltaSeconds);
	}
	RegenerationTick(DeltaSeconds);
//	LevelUpTick();
	CheckJump();
}

void APerfect_WorldCharacter::MoveToCursorTick(float DeltaSeconds)
{
	if (Controller)
	{
		FHitResult Hit;
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		FRotator rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CursorToWorld->GetRelativeLocation());
		//SetActorRotation(FQuat(FRotator(0.0f, yaw, 0.0f)));
		const FVector Direction = FRotationMatrix(rotator).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, 1.0);
		//SetActorRotation(rotator);
		FVector CharacteLocation = GetActorLocation();
		CharacteLocation.Z = 0.0f;
		FVector CursorLocation = CursorToWorld->GetRelativeLocation();
		CursorLocation.Z = 0.0f;
		UE_LOG(LogTemp, Warning, TEXT("Cursor1: %s"), *CursorLocation.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("Character: %s"), *CharacteLocation.ToString());
		float dist = FVector::Dist(CharacteLocation, CursorLocation);

		if (OldDistToCursor == dist)
		{
			++TickToCursor;
		}
		if (dist <= 5.0f || TickToCursor == 3)
		{
			CursorToWorld->SetVisibility(false);
			AddMovementInput(Direction, 0.0);
			TickToCursor = 0;
		}
		OldDistToCursor = dist;
	}
}
//////////////////////////////////////////////////////////////////////////
// Input

void APerfect_WorldCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APerfect_WorldCharacter::DoJump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &APerfect_WorldCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APerfect_WorldCharacter::MoveRight);
	PlayerInputComponent->BindAction("MoveToCursor", IE_Pressed, this, &APerfect_WorldCharacter::MoveToCursor);
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void APerfect_WorldCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		CursorToWorld->SetVisibility(false);
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		//AddMovementInput(Direction, Value);
		GetCharacterMovement()->AddInputVector(Direction * Value);
	}
}

void APerfect_WorldCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		CursorToWorld->SetVisibility(false);
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void APerfect_WorldCharacter::DoJump()
{
	if (CurrentCountJump < 2)
	{
		bIsJumping = true;
		++CurrentCountJump;
		LaunchCharacter(FVector(0.0, 0.0f, 1000.0f), false, true);
	}
}

void APerfect_WorldCharacter::MoveToCursor()
{
	if (CursorToWorld)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			CursorToWorld->SetRelativeLocation(TraceHitResult.Location);
			CursorToWorld->SetRelativeRotation(TraceHitResult.ImpactNormal.Rotation());
			CursorToWorld->SetVisibility(true);
			//FVector CursorLocation = CursorToWorld->GetRelativeLocation();
			//CursorLocation.Z = 0.0f;
			//UE_LOG(LogTemp, Warning, TEXT("Cursor: %s"), *CursorLocation.ToString());
		}
	}
}

void APerfect_WorldCharacter::CheckJump()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (!GetCharacterMovement()->IsFalling())
		{
			bIsJumping = false;
			CurrentCountJump = 0;
		}
	}
}

void APerfect_WorldCharacter::RegenerationTick(float DeltaSeconds)
{
	if (CharCharacteristicComponent->GetHealthComponent()->GetIsFight())
	{
		float FightTimer = CharCharacteristicComponent->GetHealthComponent()->GetFightTimer();
		if (FightTimer > 0.0f)
		{
			CharCharacteristicComponent->GetHealthComponent()->SetFightTimer(FightTimer - DeltaSeconds);
		}
		else
		{
			CharCharacteristicComponent->GetHealthComponent()->SetIsFight(false);
			CharCharacteristicComponent->GetHealthComponent()->SetFightTimer(0.0f);
		}
	}
	else
	{
		if (Timer > 0.0f)
		{
			Timer -= DeltaSeconds;
		}
		else
		{
			Timer = 1.0f;
			CharCharacteristicComponent->GetHealthComponent()->ChangeCurrentHealth(5);
			CharCharacteristicComponent->GetManaComponent()->ChangeCurrentMana(4);
			//ChangeCurrentXP(25);
		}
	}
}

//void APerfect_WorldCharacter::LevelUpTick()
//{
//	if (CurrentLevel == 105)
//	{
//		CurrentXP = 0;
//	}
//	else if (CurrentXP >= NeededXP)
//	{
//		CurrentXP -= NeededXP;
//		++CurrentLevel;
//		FreePoint += 5;
//		OnLevelChange.Broadcast(CurrentLevel);
//		OnFreePointChange.Broadcast(FreePoint);
//		OnXPChange.Broadcast(CurrentXP, NeededXP);
//	}
//}
