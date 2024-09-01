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
        // �����Ѿ���ý�ɫ�����ű���
        float CharacterHeight = 100.0f; // �ӽ�ɫ�����л�ȡ
        float BaseHeight = 180.0f; // ��׼���
        ScaleFactor = CharacterHeight / BaseHeight;

        // ���涥��͹�������
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
        // ���¹�������
        //UpdateBoneLengths(GetOwningComponent());
        // �ָ����Ų�����Ӧ�ö�������
        //CacheVertexAndBoneData(GetOwningComponent());
        //RestoreScaleAndApplyVertexData(GetOwningComponent());
        
    }
}

void UKAnimInstance::CacheVertexAndBoneData(USkeletalMeshComponent* SkeletalMeshComponent)
{
    // ���Ž�ɫ
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
    // ����Ӧ�ö�������
    //SkeletalMeshComponent->GetSkeletalMeshAsset()->PostEditChange();
    //
    //int32 LodNum = SkeletalMeshComponent->GetSkeletalMeshAsset()->GetResourceForRendering()->LODRenderData.Num();
    //for (int32 LodIndex = 0; LodIndex < LodNum; LodIndex++)
    //{
    //    // ��ȡLOD0��Mesh����
    //    FSkeletalMeshRenderData* SkeletalMeshResource = SkeletalMeshComponent->GetSkeletalMeshAsset()->GetResourceForRendering();
    //    FSkeletalMeshLODRenderData& LODRenderData = SkeletalMeshResource->LODRenderData[LodIndex];

    //    // �������ж���
    //    TArray<FVector> CachedWorldVertice;
    //    for (uint32 VertexIndex = 0; VertexIndex < LODRenderData.GetNumVertices() && VertexIndex < (uint32)SkeletalMeshComponent->GetComponentSpaceTransforms().Num(); ++VertexIndex)
    //    {
    //        // ��ȡ����ľֲ����꣬��ת��Ϊ��������
    //        
    //        FVector LocalVertexPosition = FVector(LODRenderData.StaticVertexBuffers.PositionVertexBuffer.VertexPosition(VertexIndex));
    //        FVector WorldVertexPosition = SkeletalMeshComponent->GetComponentSpaceTransforms()[VertexIndex].TransformPosition(LocalVertexPosition);
    //        CachedWorldVertice.Add(WorldVertexPosition);

    //        // ��ȡ����Ĺ���Ȩ��
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

    //// �������й����ĳ���
    //int32 NumBones = SkeletalMeshComponent->GetNumBones();
    //for (int32 BoneIndex = 0; BoneIndex < NumBones; ++BoneIndex)
    //{
    //    FTransform BoneTransform = SkeletalMeshComponent->GetBoneTransform(BoneIndex);
    //    //FTransform BoneTransform = SkeletalMeshComponent->GetBoneSpaceTransforms()[BoneIndex];
    //    float BoneLength = (BoneTransform.GetTranslation() * ScaleFactor).Size();
    //    CachedBoneLengths.Add(BoneLength);
    //}
    //// �ָ�����
    //SkeletalMeshComponent->SetWorldScale3D(FVector(1.0f));
     // ֪ͨ������¹����任
   
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
        // ��ȡLOD0��Mesh����
        FSkeletalMeshLODRenderData& LODRenderData = SkeletalMeshComponent->GetSkeletalMeshAsset()->GetResourceForRendering()->LODRenderData[LodIndex];
        //SkeletalMeshComponent->GetSkinnedVertexPosition()
        //SkeletalMeshComponent->setvertexpositio
        for (uint32 VertexIndex = 0; VertexIndex < LODRenderData.GetNumVertices() && VertexIndex < (uint32)SkeletalMeshComponent->GetComponentSpaceTransforms().Num(); ++VertexIndex)
        {
            // ����������ת���ؾֲ�����
            FVector LocalVertexPosition = SkeletalMeshComponent->GetComponentSpaceTransforms()[VertexIndex].InverseTransformPosition(CachedWorldVertices[LodIndex][VertexIndex]);

            // ���¶���λ��
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

        // ʹ���µĹ������ȸ���λ��
        FVector NewBonePosition = BoneTransform.GetLocation().GetSafeNormal() * CachedBoneLengths[BoneIndex];
        BoneTransform.SetTranslation(NewBonePosition);
        // ���¹����任
        //SkeletalMeshComponent->GetBoneSpaceTransforms()[BoneIndex] = BoneTransform;
        SkeletalMeshComponent->GetEditableComponentSpaceTransforms()[BoneIndex] = BoneTransform;
    }

    // ֪ͨ������¹����任
    SkeletalMeshComponent->MarkRenderTransformDirty();
    SkeletalMeshComponent->MarkRenderStateDirty();
    SkeletalMeshComponent->MarkRenderDynamicDataDirty();
    SkeletalMeshComponent->PostEditChange();
    //SkeletalMeshComponent
}

void UKAnimInstance::GetMeshVertexData(USkeletalMesh* SkeletalMesh)
{
    if (!SkeletalMesh) return;
    
    // ��ȡ��һ��LOD����������
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

// ���ö�������
void UKAnimInstance::SetMeshVertexData(USkeletalMesh* SkeletalMesh)
{
    if (!SkeletalMesh) return;

    // ��ȡ��һ��LOD����������
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

// ���Ŷ���
void UKAnimInstance::ScaleMeshVertices(USkeletalMesh* SkeletalMeshdata)
{
    if (!SkeletalMeshdata) return;

    GetMeshVertexData(SkeletalMeshdata);
    //// �޸Ķ�������
    //TArray<FVector> ScaledVertices;
    //ScaledVertices.SetNum(OriginalVertices.Num());
    //for (int32 i = 0; i < OriginalVertices.Num(); ++i)
    //{
    //    ScaledVertices[i] = OriginalVertices[i] * ScaleFactor;
    //}

    // �����޸ĺ�Ķ�������
    SetMeshVertexData(SkeletalMeshdata);

    // ˢ��Mesh
    SkeletalMeshdata->PostEditChange();
}