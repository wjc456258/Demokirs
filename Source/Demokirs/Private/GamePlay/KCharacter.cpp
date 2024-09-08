// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/KCharacter.h"
#include "Rendering/SkeletalMeshModel.h"
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
    FSkeletalMeshModel* SkeletalMeshModel = GetMesh()->GetSkeletalMeshAsset()->GetImportedModel();
    TArray<FSoftSkinVertex> SoftSkinVertexs;
    SoftSkinVertexs.Empty();
    for (int32 LODIndex = 0; LODIndex < SkeletalMeshModel->LODModels.Num(); LODIndex++)
    {
        FSkeletalMeshLODModel& LODModel = SkeletalMeshModel->LODModels[LODIndex];
        for (int32 SectionIndex = 0; SectionIndex < LODModel.Sections.Num(); SectionIndex++)
        {
            FSkelMeshSection& SkelMeshSection = LODModel.Sections[SectionIndex];
            for (int32 VerticeIndex = 0; VerticeIndex < SkelMeshSection.SoftVertices.Num(); VerticeIndex++)
            {
                GetMesh()->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));
                FSoftSkinVertex SoftSkinVertex = SkelMeshSection.SoftVertices[VerticeIndex];
                UE_LOG(LogTemp, Error, TEXT("SkelMeshSection.SoftVertices[VerticeIndex].Position = %s"), *GetMesh()->GetSkeletalMeshAsset()->GetImportedModel()->LODModels[LODIndex].Sections[SectionIndex].SoftVertices[VerticeIndex].Position.ToString())
                GetMesh()->SetRelativeScale3D(FVector(1, 1, 1));
                SkelMeshSection.SoftVertices[VerticeIndex] = SoftSkinVertex;
                //SoftSkinVertexs.Add(SoftSkinVertex)
                UE_LOG(LogTemp, Error, TEXT("SkelMeshSection.SoftVertices[VerticeIndex].Position = %s"), *GetMesh()->GetSkeletalMeshAsset()->GetImportedModel()->LODModels[LODIndex].Sections[SectionIndex].SoftVertices[VerticeIndex].Position.ToString())
            }
        }
    }
}

// Called every frame
void AKCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
}


