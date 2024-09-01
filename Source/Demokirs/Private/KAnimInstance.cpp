// Fill out your copyright notice in the Description page of Project Settings.


#include "KAnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/Skeleton.h"
#include "Rendering/SkeletalMeshRenderData.h"
#include "Rendering/SkeletalMeshModel.h"

void UKAnimInstance::NativeInitializeAnimation()
{
    //InitScaleData();
    Super::NativeInitializeAnimation();
    
    //GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UKAnimInstance::InitScaleData);

}

void UKAnimInstance::InitScaleData()
{
    if (USkeletalMeshComponent* SkeletalMeshComponent = GetOwningComponent())
    {
        // 假设已经获得角色的缩放比率
        float CharacterHeight = 100.0f; // 从角色配置中获取
        float BaseHeight = 180.0f; // 基准身高
        ScaleFactor = CharacterHeight / BaseHeight;

        // 缓存顶点和骨骼数据
        CacheVertexAndBoneData(SkeletalMeshComponent);
        bDataCached = true;
        //ScaleMeshVertices(SkeletalMeshComponent->GetSkeletalMeshAsset());
    }
}

void UKAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    //Super::NativeUpdateAnimation(DeltaSeconds);
    if (bDataCached && GetOwningComponent())
    {
        // 更新骨骼长度
        //UpdateBoneLengths(GetOwningComponent());
        // 恢复缩放并重新应用顶点数据
        //CacheVertexAndBoneData(GetOwningComponent());
        //RestoreScaleAndApplyVertexData(GetOwningComponent());
        
    }
}

void UKAnimInstance::CacheVertexAndBoneData(USkeletalMeshComponent* SkeletalMeshComponent)
{
    // 缩放角色
    //SkeletalMeshComponent->SetWorldScale3D(FVector(ScaleFactor));
    FSkeletalMeshModel* SkeletalMeshModel = SkeletalMeshComponent->GetSkeletalMeshAsset()->GetImportedModel();
    for (int32 LODIndex = 0; LODIndex < SkeletalMeshModel->LODModels.Num(); LODIndex++)
    {
        FSkeletalMeshLODModel& LODModel = SkeletalMeshModel->LODModels[LODIndex]; 
        for (int32 SectionIndex = 0; SectionIndex < LODModel.Sections.Num(); SectionIndex++)
        {
            FSkelMeshSection& SkelMeshSection = LODModel.Sections[SectionIndex];
            for (int32 VerticeIndex = 0; VerticeIndex < SkelMeshSection.SoftVertices.Num(); VerticeIndex++)
            {
                SkelMeshSection.SoftVertices[VerticeIndex].Position = FVector3f(0, 0, 0);
                UE_LOG(LogTemp,Error,TEXT("SkelMeshSection.SoftVertices[VerticeIndex].Position = %s"), *SkelMeshSection.SoftVertices[VerticeIndex].Position.ToString())
            }
        }
    }
    // 重新应用顶点数据
    //SkeletalMeshComponent->GetSkeletalMeshAsset()->PostEditChange();
    //
    //int32 LodNum = SkeletalMeshComponent->GetSkeletalMeshAsset()->GetResourceForRendering()->LODRenderData.Num();
    //for (int32 LodIndex = 0; LodIndex < LodNum; LodIndex++)
    //{
    //    // 获取LOD0的Mesh数据
    //    FSkeletalMeshRenderData* SkeletalMeshResource = SkeletalMeshComponent->GetSkeletalMeshAsset()->GetResourceForRendering();
    //    FSkeletalMeshLODRenderData& LODRenderData = SkeletalMeshResource->LODRenderData[LodIndex];

    //    // 遍历所有顶点
    //    TArray<FVector> CachedWorldVertice;
    //    for (uint32 VertexIndex = 0; VertexIndex < LODRenderData.GetNumVertices() && VertexIndex < (uint32)SkeletalMeshComponent->GetComponentSpaceTransforms().Num(); ++VertexIndex)
    //    {
    //        // 获取顶点的局部坐标，并转换为世界坐标
    //        
    //        FVector LocalVertexPosition = FVector(LODRenderData.StaticVertexBuffers.PositionVertexBuffer.VertexPosition(VertexIndex));
    //        FVector WorldVertexPosition = SkeletalMeshComponent->GetComponentSpaceTransforms()[VertexIndex].TransformPosition(LocalVertexPosition);
    //        CachedWorldVertice.Add(WorldVertexPosition);

    //        // 获取顶点的骨骼权重
    //        TArray<float> BoneWeights;
    //        for (int32 InfluenceIndex = 0; InfluenceIndex < MAX_TOTAL_INFLUENCES; ++InfluenceIndex)
    //        {
    //            float Weight = LODRenderData.SkinWeightVertexBuffer.GetBoneWeight(VertexIndex, InfluenceIndex);
    //            BoneWeights.Add(Weight);
    //        }
    //        CachedBoneWeights.Add(BoneWeights);
    //    }
    //    CachedWorldVertices.Add(CachedWorldVertice);
    //}

    //// 缓存所有骨骼的长度
    //int32 NumBones = SkeletalMeshComponent->GetNumBones();
    //for (int32 BoneIndex = 0; BoneIndex < NumBones; ++BoneIndex)
    //{
    //    FTransform BoneTransform = SkeletalMeshComponent->GetBoneTransform(BoneIndex);
    //    //FTransform BoneTransform = SkeletalMeshComponent->GetBoneSpaceTransforms()[BoneIndex];
    //    float BoneLength = (BoneTransform.GetTranslation() * ScaleFactor).Size();
    //    CachedBoneLengths.Add(BoneLength);
    //}
    //// 恢复缩放
    //SkeletalMeshComponent->SetWorldScale3D(FVector(1.0f));
     // 通知引擎更新骨骼变换
   
    //SkeletalMeshComponent->MarkRenderTransformDirty();
    //SkeletalMeshComponent->MarkRenderStateDirty();
    //SkeletalMeshComponent->MarkRenderDynamicDataDirty();
    //SkeletalMeshComponent->PostEditChange();
    
}

void UKAnimInstance::RestoreScaleAndApplyVertexData(USkeletalMeshComponent* SkeletalMeshComponent)
{
    int32 LodNum = SkeletalMeshComponent->GetSkeletalMeshAsset()->GetResourceForRendering()->LODRenderData.Num();
    for (int32 LodIndex = 0; LodIndex < LodNum; LodIndex++)
    {
        // 获取LOD0的Mesh数据
        FSkeletalMeshLODRenderData& LODRenderData = SkeletalMeshComponent->GetSkeletalMeshAsset()->GetResourceForRendering()->LODRenderData[LodIndex];
        //SkeletalMeshComponent->GetSkinnedVertexPosition()
        //SkeletalMeshComponent->setvertexpositio
        for (uint32 VertexIndex = 0; VertexIndex < LODRenderData.GetNumVertices() && VertexIndex < (uint32)SkeletalMeshComponent->GetComponentSpaceTransforms().Num(); ++VertexIndex)
        {
            // 将世界坐标转换回局部坐标
            FVector LocalVertexPosition = SkeletalMeshComponent->GetComponentSpaceTransforms()[VertexIndex].InverseTransformPosition(CachedWorldVertices[LodIndex][VertexIndex]);

            // 更新顶点位置
            LODRenderData.StaticVertexBuffers.PositionVertexBuffer.VertexPosition(VertexIndex) = FVector3f(FVector(0,0,0));
        }
    }
}

void UKAnimInstance::UpdateBoneLengths(USkeletalMeshComponent* SkeletalMeshComponent)
{
    int32 NumBones = SkeletalMeshComponent->GetNumBones();
    for (int32 BoneIndex = 0; BoneIndex < NumBones; ++BoneIndex)
    {
        FTransform BoneTransform = SkeletalMeshComponent->GetBoneTransform(BoneIndex);

        // 使用新的骨骼长度更新位置
        FVector NewBonePosition = BoneTransform.GetLocation().GetSafeNormal() * CachedBoneLengths[BoneIndex];
        BoneTransform.SetTranslation(NewBonePosition);
        // 更新骨骼变换
        //SkeletalMeshComponent->GetBoneSpaceTransforms()[BoneIndex] = BoneTransform;
        SkeletalMeshComponent->GetEditableComponentSpaceTransforms()[BoneIndex] = BoneTransform;
    }

    // 通知引擎更新骨骼变换
    SkeletalMeshComponent->MarkRenderTransformDirty();
    SkeletalMeshComponent->MarkRenderStateDirty();
    SkeletalMeshComponent->MarkRenderDynamicDataDirty();
    SkeletalMeshComponent->PostEditChange();
    //SkeletalMeshComponent
}

void UKAnimInstance::GetMeshVertexData(USkeletalMesh* SkeletalMesh)
{
    if (!SkeletalMesh) return;
    
    // 获取第一个LOD的网格数据
    const FSkeletalMeshRenderData* SkeletalMeshResource = SkeletalMesh->GetResourceForRendering();
    if (!SkeletalMeshResource || SkeletalMeshResource->LODRenderData.Num() == 0) return;

    const FSkeletalMeshLODRenderData& LODData = SkeletalMeshResource->LODRenderData[0];
    const FPositionVertexBuffer& PositionVertexBuffer = LODData.StaticVertexBuffers.PositionVertexBuffer;

    CachedWorldVertices[0].SetNum(PositionVertexBuffer.GetNumVertices());
    for (uint32 i = 0; i < PositionVertexBuffer.GetNumVertices(); ++i)
    {
        CachedWorldVertices[0][i] = FVector(PositionVertexBuffer.VertexPosition(i));
    }
}

// 设置顶点数据
void UKAnimInstance::SetMeshVertexData(USkeletalMesh* SkeletalMesh)
{
    if (!SkeletalMesh) return;

    // 获取第一个LOD的网格数据
    FSkeletalMeshRenderData* SkeletalMeshResource = SkeletalMesh->GetResourceForRendering();
    if (!SkeletalMeshResource || SkeletalMeshResource->LODRenderData.Num() == 0) return;

    FSkeletalMeshLODRenderData& LODData = SkeletalMeshResource->LODRenderData[0];
    FPositionVertexBuffer& PositionVertexBuffer = LODData.StaticVertexBuffers.PositionVertexBuffer;

    check(CachedWorldVertices[0].Num() == PositionVertexBuffer.GetNumVertices());

    for (uint32 i = 0; i < PositionVertexBuffer.GetNumVertices(); ++i)
    {
        PositionVertexBuffer.VertexPosition(i) = FVector3f(0,0,0);
    }

}

// 缩放顶点
void UKAnimInstance::ScaleMeshVertices(USkeletalMesh* SkeletalMeshdata)
{
    if (!SkeletalMeshdata) return;

    GetMeshVertexData(SkeletalMeshdata);
    //// 修改顶点数据
    //TArray<FVector> ScaledVertices;
    //ScaledVertices.SetNum(OriginalVertices.Num());
    //for (int32 i = 0; i < OriginalVertices.Num(); ++i)
    //{
    //    ScaledVertices[i] = OriginalVertices[i] * ScaleFactor;
    //}

    // 设置修改后的顶点数据
    SetMeshVertexData(SkeletalMeshdata);

    // 刷新Mesh
    SkeletalMeshdata->PostEditChange();
}