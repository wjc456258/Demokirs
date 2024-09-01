// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "KAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEMOKIRS_API UKAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
    void CacheVertexAndBoneData(USkeletalMeshComponent* SkeletalMeshComponent);
    void RestoreScaleAndApplyVertexData(USkeletalMeshComponent* SkeletalMeshComponent);
    void UpdateBoneLengths(USkeletalMeshComponent* SkeletalMeshComponent);
    void GetMeshVertexData(USkeletalMesh* SkeletalMesh);
    void SetMeshVertexData(USkeletalMesh* SkeletalMesh);
    void ScaleMeshVertices(USkeletalMesh* SkeletalMesh);
    void InitScaleData();
    // 存储顶点数据和骨骼数据
    TArray<TArray<FVector>> CachedWorldVertices;
    TArray<TArray<float>> CachedBoneWeights;
    TArray<float> CachedBoneLengths;

    bool bDataCached = false;
    float ScaleFactor = 1.0f;
	
};
