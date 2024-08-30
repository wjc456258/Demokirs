// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KCharacter.generated.h"

// 用于存储顶点信息的结构体
struct FVertexInfo
{
	FVector WorldPosition;
	TArray<float> BoneWeights;
};

UCLASS()
class DEMOKIRS_API AKCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Inittest();

	void InitializeCharacter(float CharacterHeight, float BaseHeight);

	void AdjustSkeletalMesh(USkeletalMeshComponent* SkelMeshComp, float HeightRatio);

	void CacheVertexAndBoneInfo(USkeletalMeshComponent* SkelMeshComp, float HeightRatio, TArray<FVertexInfo>& CachedVertexInfo, TArray<float>& CachedBoneLengths);

	void RestoreVertexInfo(USkeletalMeshComponent* SkelMeshComp, const TArray<FVertexInfo>& CachedVertexInfo);

	void AdjustBoneTransforms(USkeletalMeshComponent* SkelMeshComp, const TArray<float>& CachedBoneLengths);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UTestSkeletalMeshComponent* MeshComp;
	

};
