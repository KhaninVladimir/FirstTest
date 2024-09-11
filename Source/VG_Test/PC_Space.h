// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_Space.generated.h"

/**
 * 
 */
UCLASS()
class VG_TEST_API APC_Space : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
		int32 Coins;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
		int32 Score;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
		int32 Destroyed;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
