// Fill out your copyright notice in the Description page of Project Settings.

#include "VG_TestGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectIterator.h"
FTimerHandle CreepTimerHandle;

AVG_TestGameModeBase::AVG_TestGameModeBase()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("Class'/Script/VG_Test.SpaceShip'"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	PlayerControllerClass = APC_Space::StaticClass();
}

void AVG_TestGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Ship = (ASpaceShip*)UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	PC = (APC_Space*)UGameplayStatics::GetPlayerController(GetWorld(), 0);
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASky::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
		Sky = (ASky*)FoundActors[0];
}

void AVG_TestGameModeBase::Play()
{
	PC->Score = 0;
	PC->Coins = 0;
	PC->Destroyed = 0;
	Sky->MoveBackground(true);
	Ship->bGame = true;
	GetWorld()->GetTimerManager().SetTimer(CreepTimerHandle, this, &AVG_TestGameModeBase::CreepSpawn, 1.0f, true);
}

void AVG_TestGameModeBase::CreepSpawn()
{
	FTransform SpawnTransform = FTransform(FVector(FMath::RandRange(-1100.0f, -1160.0f), FMath::RandRange(0.0f, 1300.0f), 320));
	AEnemy* En = (AEnemy*)UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), AEnemy::StaticClass(), SpawnTransform);
	En->Speed = FMath::Clamp((float)(PC->Score / 100), 5.0f, 20.0f);
	En->EnemyType = static_cast<EEnemyType>(FMath::RandRange(0, 2));
	En->FinishSpawning(SpawnTransform);

}

void AVG_TestGameModeBase::EndGame()
{
	GetWorld()->GetTimerManager().ClearTimer(CreepTimerHandle);
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), FoundActors);
	for (AActor* Actor : FoundActors)
	{
		Actor->Destroy();
	}
	GameUI->SetVisibility(ESlateVisibility::Hidden);
	MainMenuUI->SetVisibility(ESlateVisibility::Visible);
	Sky->MoveBackground(false);
	PC->bShowMouseCursor = true;
	Ship->bGame = false;
	Ship->SetActorRotation(FRotator(0, 90, 0));
	Ship->SetActorLocation(FVector(-2670.000000, 670.000000, 320.000000));
}