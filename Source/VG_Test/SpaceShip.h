// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SpaceShip.generated.h"

UCLASS()
class VG_TEST_API ASpaceShip : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FireRate = 0.5f;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Ship;
	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* EnginePS;
	USceneComponent* Root;
	bool bGame;
	bool bFire = true;
	// Sets default values for this pawn's properties
	ASpaceShip();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Shoot();
	void Fire();
	void StopFire();
	void Move(float Val);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
