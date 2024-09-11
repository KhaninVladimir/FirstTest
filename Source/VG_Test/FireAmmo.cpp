// Fill out your copyright notice in the Description page of Project Settings.

#include "FireAmmo.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/GameFramework/DamageType.h"
#include "Enemy.h"

// Sets default values
AFireAmmo::AFireAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	SphereCol = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCol"));
	//SphereCol->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SphereCol->SetSphereRadius(32.f);
	SphereCol->BodyInstance.SetCollisionProfileName("Projectile");
	SphereCol->OnComponentHit.AddDynamic(this, &AFireAmmo::OnHit);
	RootComponent = SphereCol;

	// Create mesh component for the projectile sphere
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/Effects/P_LazerIceAttack.P_LazerIceAttack'"));
	Form = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EnginePS"));
	Form->SetTemplate(PS.Object);
	Form->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->InitialSpeed = 1000.f;
	ProjectileMovement->MaxSpeed = 1000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	InitialLifeSpan = 10.0f;

}

// Called when the game starts or when spawned
void AFireAmmo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFireAmmo::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	
	if (OtherActor != NULL && OtherActor != this && OtherComp != NULL && OtherActor->IsA(AEnemy::StaticClass()))
	{
		UGameplayStatics::ApplyDamage(OtherActor, 1, UGameplayStatics::GetPlayerController(GetWorld() , 0), this, UDamageType::StaticClass());
		//UE_LOG(LogTemp, Warning, TEXT("TakeDmg: %f"), A);
		Destroy();
		//OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
	}

	
}

