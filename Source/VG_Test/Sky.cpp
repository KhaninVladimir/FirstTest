// Fill out your copyright notice in the Description page of Project Settings.

#include "Sky.h"
#include "UObject/ConstructorHelpers.h"

FTimerHandle MoveTimerHandle;
// Sets default values
ASky::ASky()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	const ConstructorHelpers::FObjectFinder<UStaticMesh> m_staticMesh(TEXT("StaticMesh'/Game/Mesh/Background.Background'"));
	Space = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Space"));
	Space->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	Space->SetStaticMesh(m_staticMesh.Object);
	Space->SetRelativeLocation(FVector(3040, 0, 0));
	Space->SetRelativeScale3D(FVector(8, 8, 8));

	Space1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Space1"));
	Space1->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	Space1->SetStaticMesh(m_staticMesh.Object);
	Space1->SetRelativeLocation(FVector(0, 0, 0));
	Space1->SetRelativeScale3D(FVector(8, 8, 8));
}


void ASky::MoveBackground(bool Move)
{
	if (Move)
		GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle, this, &ASky::MoveTimer, 0.01f, true);
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(MoveTimerHandle);
		Space->SetRelativeLocation(FVector(3040.0f, 0.0f, 0.0f));
		Space1->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
}

void ASky::MoveTimer()
{
	Space->AddRelativeLocation(FVector(Speed, 0, 0));
	Space1->AddRelativeLocation(FVector(Speed, 0, 0));
	if (Space->GetRelativeLocation().X < MaxOffset)
	{
		Space->SetRelativeLocation(FVector(3040.0f, 0.0f, 0.0f));
	}
	if (Space1->GetRelativeLocation().X < MaxOffset)
	{
		Space1->SetRelativeLocation(FVector(3040.0f, 0.0f, 0.0f));
	}
}

// Called when the game starts or when spawned
void ASky::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASky::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

