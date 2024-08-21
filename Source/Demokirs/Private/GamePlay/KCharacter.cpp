// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/KCharacter.h"

// Sets default values
AKCharacter::AKCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AKCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetMesh()->SetPredictedLODLevel(6);
	int32 forcelod = GetMesh()->GetForcedLOD();
	int32 lod = GetMesh()->GetPredictedLODLevel();
	UE_LOG(LogTemp, Display, TEXT("lod    %d"), lod);
	UE_LOG(LogTemp, Display, TEXT("forcelod    %d"), forcelod);
}


