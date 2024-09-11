// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "UObject/ConstructorHelpers.h"
#include "SpaceShip.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	const ConstructorHelpers::FObjectFinder<UStaticMesh> m_staticMesh(TEXT("StaticMesh'/Game/Mesh/Asteroid.Asteroid'"));
	Asteroid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Asteroid"));
	Asteroid->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	Asteroid->SetStaticMesh(m_staticMesh.Object);
	Asteroid->BodyInstance.SetCollisionProfileName("BlockAll");
	Asteroid->SetNotifyRigidBodyCollision(true);
	Asteroid->OnComponentHit.AddDynamic(this, &AEnemy::OnHit);
	RootComponent = Asteroid;
	RandRotate = FRotator(FMath::RandRange(-1, 1), FMath::RandRange(-1, 1), FMath::RandRange(-1, 1));
	this->SetActorTickInterval(0.01f);
}

void AEnemy::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != NULL && OtherActor != this && OtherComp != NULL && OtherActor->IsA(ASpaceShip::StaticClass()))
	{
		UGameplayStatics::ApplyDamage(OtherActor, 1, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, UDamageType::StaticClass());
	}
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	switch (EnemyType)
	{
	case EEnemyType::ET_Small:
		Health = 1;
		ScorePrice = 10;
		bCanShares = false;
		Price = 2;
		SetActorScale3D(FVector(1, 1, 1));
		break;
	case EEnemyType::ET_Medium:
		Health = 2;
		ScorePrice = 50;
		bCanShares = false;
		Price = 4;
		SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));
		break;
	case EEnemyType::ET_Big:
		Health = 3;
		ScorePrice = 100;
		bCanShares = true;
		Price = 6;
		SetActorScale3D(FVector(2, 2, 2));
		break;
	default:
		break;
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorWorldRotation(RandRotate);
	AddActorWorldOffset(FVector(-Speed, 0.0f, 0.0f), true);
	if (GetActorLocation().X < -4000) Destroy();
}


float AEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;
	if (Health <= 0) AEnemy::Death((APC_Space*)EventInstigator);

	Super::TakeDamage(DamageAmount, DamageEvent,  EventInstigator, DamageCauser);
	return 1;
}

void AEnemy::Death(APC_Space* PC)
{
	if (Health > 0) return;
	if (bCanShares)
	{
		for (int i = 0; i < FMath::RandRange(1, 3); i++)
		{
			FVector RandLoc = GetActorLocation() + FVector(FMath::RandRange(-100, 100), FMath::RandRange(-100, 100), 0.0f);
			RandLoc.Y = FMath::Clamp(RandLoc.Y, -180.0f, 1580.0f);
			FTransform SpawnTransform = FTransform(RandLoc);
			AEnemy* En = (AEnemy*)UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), AEnemy::StaticClass(), SpawnTransform);
			En->EnemyType = EEnemyType::ET_Small;
			En->Speed = FMath::Clamp((float)(PC->Score / 100), 5.0f, 20.0f);
			En->FinishSpawning(SpawnTransform);
		}
	}
	PC->Score += ScorePrice;
	PC->Coins += Price;
	PC->Destroyed++;
	Destroy();
}