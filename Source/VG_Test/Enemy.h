// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "PC_Space.h"
#include "Enemy.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EEnemyType : uint8
{
	ET_Small 	UMETA(DisplayName = "Small"),
	ET_Medium 	UMETA(DisplayName = "Medium"),
	ET_Big		UMETA(DisplayName = "Big")
};

UCLASS()
class VG_TEST_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	bool bCanShares = false;
	int32 Health = 1;
	int32 Speed = 5;
	
	EEnemyType EnemyType;

	UStaticMeshComponent* Asteroid;
	USceneComponent* Root;
	FVector Size = FVector(1, 1, 1);
	int32 Price = 1;
	int32 ScorePrice = 1;
	FRotator RandRotate;
	

	AEnemy();
	void Death(APC_Space* PC);
	
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
