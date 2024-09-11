// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PC_Space.h"
#include "SpaceShip.h"
#include "Enemy.h"
#include "Sky.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "VG_TestGameModeBase.generated.h"

UCLASS()
class VG_TEST_API AVG_TestGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UUserWidget* MainMenuUI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UUserWidget* GameUI;
	ASky* Sky;
	APC_Space* PC;
	ASpaceShip* Ship;
	AVG_TestGameModeBase();

	void CreepSpawn();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Play", CompactNodeTitle = "Play", Keywords = "Play"), Category = "GM")
		void Play();
	void EndGame();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
