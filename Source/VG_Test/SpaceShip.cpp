// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShip.h"
#include "UObject/ConstructorHelpers.h"
#include "FireAmmo.h"
#include "VG_TestGameModeBase.h"
FTimerHandle ShotTimerHandle;

// Sets default values
ASpaceShip::ASpaceShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	const ConstructorHelpers::FObjectFinder<UStaticMesh> m_staticMesh(TEXT("StaticMesh'/Game/Mesh/SpaceShip.SpaceShip'"));
	Ship = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpaceShip"));
	Ship->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	Ship->SetStaticMesh(m_staticMesh.Object);
	Ship->BodyInstance.SetCollisionProfileName("BlockAll");

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/Effects/P_Sparks.P_Sparks'"));
	EnginePS = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EnginePS"));
	EnginePS->SetupAttachment(Ship);
	EnginePS->SetTemplate(PS.Object);
	EnginePS->SetRelativeLocation(FVector(0.0f, 70.0f, 0.0f));
	EnginePS->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
}



// Called when the game starts or when spawned
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ASpaceShip::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{

	AVG_TestGameModeBase* GM = (AVG_TestGameModeBase*)GetWorld()->GetAuthGameMode();
	GM->EndGame();
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return 1;
}

// Called to bind functionality to input
void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASpaceShip::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ASpaceShip::StopFire);
	PlayerInputComponent->BindAxis("Move", this, &ASpaceShip::Move);
}

void ASpaceShip::Move(float Value)
{
	if (bGame)
		AddActorWorldOffset(FVector(0.0f, Speed*Value, 0.0f), true);
}

void ASpaceShip::Fire()
{
	if (!bFire && bGame)
	{
		ASpaceShip::Shoot();
		bFire = true;
		GetWorld()->GetTimerManager().SetTimer(ShotTimerHandle, this, &ASpaceShip::Shoot, FireRate, true);
	}
	

}

void ASpaceShip::StopFire()
{
	if (bFire)
	{
		bFire = false;
		GetWorld()->GetTimerManager().ClearTimer(ShotTimerHandle);
	}

}

void ASpaceShip::Shoot()
{
	FTransform SpawnTransform = Ship->GetSocketTransform("ShootPoint");
	GetWorld()->SpawnActor<AFireAmmo>(AFireAmmo::StaticClass(), SpawnTransform);
}