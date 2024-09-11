// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Sky.generated.h"

UCLASS()
class VG_TEST_API ASky : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxOffset = -2040.0f;
	float Speed = -5.0f;

	UStaticMeshComponent* Space;
	UStaticMeshComponent* Space1;
	USceneComponent* Root;
	ASky();

	void MoveBackground(bool Move);
	void MoveTimer();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
