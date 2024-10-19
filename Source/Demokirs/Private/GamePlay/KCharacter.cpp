#include "GamePlay/KCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Rendering/SkeletalMeshRenderData.h"
#include "Rendering/SkeletalMeshLODRenderData.h"
#include "TestSkeletalMeshComponent.h"
#include "ReferenceSkeleton.h"
// Sets default values
AKCharacter::AKCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    //MeshComp = CreateDefaultSubobject<UTestSkeletalMeshComponent>(TEXT("CustomMesh"));
    //MeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AKCharacter::BeginPlay()
{
    Super::BeginPlay();
    //MeshComp->SetComponentTickEnabled(false);
    // ������ɫ�����
    // �����׼�����180��Ŀ�������100
    FTimerHandle UnusedHandle;
    GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AKCharacter::Inittest);
}

void AKCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //InitializeCharacter(100, 180);
    InitializeCharacter(50, 180);
}

void AKCharacter::Inittest()
{
    InitializeCharacter(50, 180);
}
// ��ʼ������
void AKCharacter::InitializeCharacter(float CharacterHeight, float BaseHeight)
{
    // ����1: ��ȡ��ɫ�� SKM ����߱�ֵ
    USkeletalMeshComponent* SkelMeshComp = GetMesh(); // �������Ѿ���һ�� Skeletal Mesh Component
    if (!SkelMeshComp)
    {
        UE_LOG(LogTemp, Error, TEXT("SkeletalMeshComponent is null!"));
        return;
    }

    float HeightRatio = CharacterHeight / BaseHeight;
    SkelMeshComp->PrimaryComponentTick.bCanEverTick = false;
    // ����2: ��ʼ����ɫ������Ϊ���ɼ�
    SkelMeshComp->SetVisibility(false);

    // ��������
    TArray<FVertexInfo> CachedVertexInfo;
    TArray<float> CachedBoneLengths;
    //FVector BoneLocation = SkelMeshComp->GetSkeletalMeshAsset()->GetRefSkeleton().GetRefBonePose()[1].GetLocation();
    //UE_LOG(LogTemp, Error, TEXT("BoneLocation is %s!"), *BoneLocation.ToString());
    FVector BoneLocation1 = SkelMeshComp->GetBoneTransform(1).GetLocation();
    UE_LOG(LogTemp, Error, TEXT("BoneLocation1 is %s!"), *BoneLocation1.ToString());
    //FVector BoneLocation2 = SkelMeshComp->GetComponentTransform(1).GetLocation();
    //UE_LOG(LogTemp, Error, TEXT("SkeletalMeshComponent is null!"));
    // �����������ű���
    //AdjustSkeletalMesh(SkelMeshComp, HeightRatio);
    
    // �洢���ж�����������ꡢ����Ȩ�ء��������ȵ���Ϣ
    //CacheVertexAndBoneInfo(SkelMeshComp, HeightRatio, CachedVertexInfo, CachedBoneLengths);
    int32 LODIndex = 0; // ͨ���� LOD0��Ҳ���Ա������� LOD
    if (SkelMeshComp && SkelMeshComp->GetSkeletalMeshRenderData())
    {
        FSkeletalMeshRenderData* SkelMeshRenderData = SkelMeshComp->GetSkeletalMeshRenderData();
        FSkeletalMeshLODRenderData& LODData = SkelMeshRenderData->LODRenderData[LODIndex];

        for (uint32 i = 0; i < LODData.GetNumVertices(); ++i)
        {
            // ��ȡ�ֲ�����
            FVector LocalPosition = FVector(LODData.StaticVertexBuffers.PositionVertexBuffer.VertexPosition(i));

            // ת��Ϊ����ռ�
            FVector WorldPosition = SkelMeshComp->GetComponentTransform().TransformPosition(LocalPosition * HeightRatio);

            // ��ȡ����Ȩ��
            TArray<float> BoneWeights; // �������Ѿ���ȡ��ÿ������Ĺ���Ȩ��

            // ���涥����Ϣ
            CachedVertexInfo.Add(FVertexInfo{ WorldPosition, BoneWeights });
        }

        // �������������Ϣ
        // ������ͨ��һЩ�����ȡ�˹��������糤�Ȳ���������
        for (int32 BoneIndex = 0; BoneIndex < SkelMeshComp->GetNumBones(); ++BoneIndex)
        {
            // ���ݹ������Ⱥͱ�����������
            float BoneLength = SkelMeshComp->GetBoneTransform(BoneIndex).GetLocation().Size();
            CachedBoneLengths.Add(BoneLength * HeightRatio);
        }
    }
    // ����3: ����ɫ�����Ż�ԭΪ 1.0
    //SkelMeshComp->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));

    // ������Ķ�������ת����ģ�Ϳռ䲢����
    //RestoreVertexInfo(SkelMeshComp, CachedVertexInfo);

    // ����4: ʹ���»���Ĺ������ȣ����� Transform �������������
    //AdjustBoneTransforms(SkelMeshComp, CachedBoneLengths);
    //for (int32 BoneIndex = 0; BoneIndex < SkelMeshComp->GetNumBones(); ++BoneIndex)
    //{
    //    FTransform BoneTransform = SkelMeshComp->GetBoneTransform(BoneIndex);

    //    // ʹ�û���Ĺ������ȵ���ƫ��
    //    FVector AdjustedBonePosition = BoneTransform.GetLocation().GetSafeNormal() * CachedBoneLengths[BoneIndex];

    //    // �����µĹ���λ��
    //    BoneTransform.SetLocation(AdjustedBonePosition);

    //    // ���¹����任
    //    //SkelMeshComp->SetBoneTransformByName(SkelMeshComp->GetBoneName(BoneIndex), BoneTransform, EBoneSpaces::ComponentSpace);
    //    SkelMeshComp->BoneSpaceTransforms[BoneIndex] = BoneTransform;
    //}
    //FReferenceSkeleton& RefSkeleton = GetMesh()->SkeletalMesh->GetRefSkeleton();
    //FReferenceSkeletonModifier RefSkelModifier(RefSkeleton, GetMesh()->SkeletalMesh->GetSkeleton());
    //int32 NumBones = RefSkeleton.GetNum(); // ��ȡ��������

    //for (int32 BoneIndex = 0; BoneIndex < NumBones; ++BoneIndex)
    //{
    //    if (BoneIndex >= 0 && BoneIndex < NumBones)
    //    {
    //        // ����� BoneIndex ����Ч�ģ����Խ��а�ȫ�Ĳ���
    //        FTransform BoneTransform = GetMesh()->SkeletalMesh->GetRefSkeleton().GetRefBonePose()[BoneIndex];
    //        BoneTransform.SetLocation(BoneTransform.GetLocation()*0.4);
    //        // ���й����任�޸�

    //        RefSkelModifier.UpdateRefPoseTransform(BoneIndex, BoneTransform);
    //    }
    //    else
    //    {
    //        // BoneIndex ��Ч���������������Ϣ
    //        UE_LOG(LogTemp, Warning, TEXT("Invalid BoneIndex: %d"), BoneIndex);
    //    }
    //}
    //GetMesh()->SkeletalMesh->PostEditChange();
    //GetMesh()->SkeletalMesh->MarkPackageDirty();
   /* FTransform BoneTransform;
    BoneTransform.SetLocation(FVector(0, 0, 0));
    BoneTransform.SetTranslation(FVector(0, 0, 0));
    SkelMeshComp->GetEditableComponentSpaceTransforms()[1].SetLocation(BoneTransform.GetLocation());
    BoneLocation = SkelMeshComp->GetSkeletalMeshAsset()->GetRefSkeleton().GetRefBonePose()[1].GetLocation();
    UE_LOG(LogTemp, Error, TEXT("BoneLocation is %s!"), *BoneLocation.ToString());
    BoneLocation1 = SkelMeshComp->GetBoneTransform(1).GetLocation();
    UE_LOG(LogTemp, Error, TEXT("BoneLocation1 is %s!"), *BoneLocation1.ToString());*/
    // ����5: ���ֶ����������Ȩ�ع�ϵ����

    // ����6: ��������� SKM ��Ϊ���յ� SKM�����������ݲ���ʾ����
    SkelMeshComp->SetVisibility(true);
}

void AKCharacter::AdjustSkeletalMesh(USkeletalMeshComponent* SkelMeshComp, float HeightRatio)
{
    // ������������������ȵȲ���
    SkelMeshComp->SetWorldScale3D(FVector(HeightRatio, HeightRatio, HeightRatio));

    // ����չ�߼��������������ӱ任
}

void AKCharacter::CacheVertexAndBoneInfo(USkeletalMeshComponent* SkelMeshComp, float HeightRatio, TArray<FVertexInfo>& CachedVertexInfo, TArray<float>& CachedBoneLengths)
{
    // ����ÿ�� LOD �Ķ��㣬��ȡ��ת��Ϊ��������
    int32 LODIndex = 0; // ͨ���� LOD0��Ҳ���Ա������� LOD
    if (SkelMeshComp && SkelMeshComp->GetSkeletalMeshRenderData())
    {
        FSkeletalMeshRenderData* SkelMeshRenderData = SkelMeshComp->GetSkeletalMeshRenderData();
        FSkeletalMeshLODRenderData& LODData = SkelMeshRenderData->LODRenderData[LODIndex];

        for (uint32 i = 0; i < LODData.GetNumVertices(); ++i)
        {
            // ��ȡ�ֲ�����
            FVector LocalPosition = FVector(LODData.StaticVertexBuffers.PositionVertexBuffer.VertexPosition(i));

            // ת��Ϊ����ռ�
            FVector WorldPosition = SkelMeshComp->GetComponentTransform().TransformPosition(LocalPosition * HeightRatio);

            // ��ȡ����Ȩ��
            TArray<float> BoneWeights; // �������Ѿ���ȡ��ÿ������Ĺ���Ȩ��

            // ���涥����Ϣ
            CachedVertexInfo.Add(FVertexInfo{ WorldPosition, BoneWeights });
        }

        // �������������Ϣ
        // ������ͨ��һЩ�����ȡ�˹��������糤�Ȳ���������
        for (int32 BoneIndex = 0; BoneIndex < SkelMeshComp->GetNumBones(); ++BoneIndex)
        {
            // ���ݹ������Ⱥͱ�����������
            float BoneLength = SkelMeshComp->GetBoneTransform(BoneIndex).GetLocation().Size();
            CachedBoneLengths.Add(BoneLength * HeightRatio);
        }
    }
}

void AKCharacter::RestoreVertexInfo(USkeletalMeshComponent* SkelMeshComp, const TArray<FVertexInfo>& CachedVertexInfo)
{
    // �����㻺�������ж����λ�ú͹�������

    // ����ÿ�� LOD ���������ö���λ��
    int32 LODIndex = 0;
    if (SkelMeshComp && SkelMeshComp->GetSkeletalMeshRenderData())
    {
        FSkeletalMeshRenderData* SkelMeshRenderData = SkelMeshComp->GetSkeletalMeshRenderData();
        FSkeletalMeshLODRenderData& LODData = SkelMeshRenderData->LODRenderData[LODIndex];

        for (uint32 i = 0; i < LODData.GetNumVertices(); ++i)
        {
            // ���½���������ת��Ϊģ�Ϳռ�����
            FVector NewLocalPosition = SkelMeshComp->GetComponentTransform().InverseTransformPosition(CachedVertexInfo[i].WorldPosition);

            // �������ö���λ��Ϊ�µ�ģ�Ϳռ�����
            LODData.StaticVertexBuffers.PositionVertexBuffer.VertexPosition(i) = FVector3f(NewLocalPosition);
        }
    }
}

void AKCharacter::AdjustBoneTransforms(USkeletalMeshComponent* SkelMeshComp, const TArray<float>& CachedBoneLengths)
{
    // ��ÿ������Ӧ�û���ĳ�����Ϣ������λ��ƫ�Ƶ���������������
    for (int32 BoneIndex = 0; BoneIndex < SkelMeshComp->GetNumBones(); ++BoneIndex)
    {
        FTransform BoneTransform = SkelMeshComp->GetBoneTransform(BoneIndex);

        // ʹ�û���Ĺ������ȵ���ƫ��
        FVector AdjustedBonePosition = BoneTransform.GetLocation().GetSafeNormal() * CachedBoneLengths[BoneIndex];

        // �����µĹ���λ��
        BoneTransform.SetLocation(AdjustedBonePosition);

        // ���¹����任
        //SkelMeshComp->SetBoneTransformByName(SkelMeshComp->GetBoneName(BoneIndex), BoneTransform, EBoneSpaces::ComponentSpace);
        SkelMeshComp->BoneSpaceTransforms[BoneIndex] = BoneTransform;
    }
}

void GetVertexBoneWeights(const USkinnedMeshComponent* SkinnedMeshComponent, TArray<FVector>& OutVertexPositions, TArray<TArray<FVector2D>>& OutVertexBoneWeights)
{
    
}



//// ��������������ɫ��Mesh�߶�
//void AKCharacter::AdjustCharacterMeshHeight(USkeletalMeshComponent* SkelMeshComp, float CharacterHeight, float BaseHeight)
//{
//    if (!SkelMeshComp || !SkelMeshComp->GetSkeletalMeshAsset())
//    {
//        UE_LOG(LogTemp, Error, TEXT("Invalid SkeletalMeshComponent or SkeletalMeshAsset"));
//        return;
//    }
//
//    // Step 1: �������ű���
//    float ScaleFactor = CharacterHeight / BaseHeight;
//
//    // Step 2: ��ʼ�������ò��ɼ�������SKM
//    SkelMeshComp->SetWorldScale3D(FVector(ScaleFactor));
//    TArray<FVector> OriginalVertexPositions;
//    CacheOriginalVertexPositions(SkelMeshComp, OriginalVertexPositions);
//
//    // Step 3: ����ÿ����������λ�ã��洢���й����ĳ��Ⱥ�ƫ��
//    //TArray<FVector> ScaledBonePositions;
//    TArray<FTransform> BoneOffsets;
//    CacheBoneTransforms(SkelMeshComp, ScaleFactor, BoneOffsets);
//
//    // Step 4: ��ԭScale�����趥���������ƫ��
//    SkelMeshComp->SetWorldScale3D(FVector(1.0f));
//    AdjustBonePositions(SkelMeshComp, BoneOffsets);
//    AdjustVertexPositionsWithBoneWeights(SkelMeshComp, OriginalVertexPositions);
//
//    // Step 5: ������ʾ��ɫ
//    SkelMeshComp->MarkRenderStateDirty();
//    SkelMeshComp->SetVisibility(true);
//}
//
//// ����������ԭʼ����λ��
//void AKCharacter::CacheOriginalVertexPositions(USkeletalMeshComponent* SkelMeshComp, TArray<FVector>& OutOriginalVertexPositions)
//{
//    //USkeletalMesh* MeshAsset = SkelMeshComp->GetSkeletalMeshAsset();
//    //if (!MeshAsset) return;
//
//    //const FSkeletalMeshModel* Model = MeshAsset->GetImportedModel();
//    //if (!Model) return;
//    //FTransform ComponentTransform = SkelMeshComp->GetComponentTransform();
//
//    //// ���� LOD 0 ���ж��㣬ת������������
//    //FSkeletalMeshRenderData* RenderData = SkelMeshComp->GetSkeletalMeshRenderData();
//    //if (RenderData && RenderData->LODRenderData.Num() > 0)
//    //{
//    //    FSkeletalMeshLODRenderData& LODData = RenderData->LODRenderData[0];
//    //    const FPositionVertexBuffer& VertexBuffer = LODData.StaticVertexBuffers.PositionVertexBuffer;
//
//    //    for (uint32 i = 0; i < VertexBuffer.GetNumVertices(); i++)
//    //    {
//    //        FVector LocalPos = VertexBuffer.VertexPosition(i);
//    //        FVector WorldPos = ComponentTransform.TransformPosition(LocalPos);
//    //        CachedWorldVertices.Add(WorldPos);
//    //    }
//
//    //    // Step 5: �洢��������
//    //    // ��ȡ��Ƥ���ݣ����������Ӧ�Ĺ���Ȩ��
//    //    for (int32 SectionIndex = 0; SectionIndex < LODData.RenderSections.Num(); SectionIndex++)
//    //    {
//    //        const FSkelMeshRenderSection& Section = LODData.RenderSections[SectionIndex];
//    //        const FMultiSizeIndexContainer& IndexContainer = Section.IndexBuffer;
//    //        for (int32 VertexIndex = 0; VertexIndex < Section.NumVertices; VertexIndex++)
//    //        {
//    //            // �洢����������Ȩ�� (�򻯴���)
//    //            for (int32 InfluenceIndex = 0; InfluenceIndex < MAX_TOTAL_INFLUENCES; InfluenceIndex++)
//    //            {
//    //                int32 BoneIndex = Section.BoneMap[InfluenceIndex];
//    //                BoneIndices.Add(BoneIndex);
//    //                BoneWeights.Add(Section.BoneWeights[VertexIndex].InfluenceWeights[InfluenceIndex] / 255.0f);
//    //            }
//    //        }
//    //    }
//    //}
//
//
//
//
//
//
//    if (!SkelMeshComp || !SkelMeshComp->SkeletalMesh)
//    {
//        return;
//    }
//
//    // ��ȡ�������Ⱦ����
//    FSkeletalMeshRenderData* RenderData = SkelMeshComp->GetSkeletalMeshRenderData();
//    if (!RenderData || RenderData->LODRenderData.Num() == 0)
//    {
//        return;
//    }
//
//    // ���� LOD 0 ������
//    FSkeletalMeshLODRenderData& LODData = RenderData->LODRenderData[0];
//
//    // ��ȡ���㻺�����͹�����ƤȨ�ػ�����
//    const FPositionVertexBuffer& VertexBuffer = LODData.StaticVertexBuffers.PositionVertexBuffer;
//    const FSkinWeightVertexBuffer& SkinWeightBuffer = LODData.SkinWeightVertexBuffer;
//
//    // ��ȡ����任
//    FTransform ComponentToWorld = SkelMeshComp->GetComponentTransform();
//
//    // �������ж���
//    for (uint32 VertexIndex = 0; VertexIndex < VertexBuffer.GetNumVertices(); VertexIndex++)
//    {
//        FVector SkinnedVertexPosition = FVector::ZeroVector;
//
//        // ��ȡ��ǰ�����λ�ã��ֲ��ռ䣩
//        FVector LocalVertexPos = FVector(VertexBuffer.VertexPosition(VertexIndex));
//
//        // ��ȡÿ�������Ӱ�������Ϣ��Ȩ��
//        FSkinWeightInfo SkinWeightInfo = SkinWeightBuffer.GetVertexSkinWeights(VertexIndex);
//
//        // ����ÿ������Ĺ���Ӱ�죨ͨ���� 4 �����Ȩ�أ�
//        for (int32 InfluenceIndex = 0; InfluenceIndex < MAX_TOTAL_INFLUENCES; InfluenceIndex++)
//        {
//            // ��ȡ���������Ͷ�Ӧ��Ȩ��
//            int32 BoneIndex = SkinWeightInfo.InfluenceBones[InfluenceIndex];
//            float Weight = SkinWeightInfo.InfluenceWeights[InfluenceIndex] / 255.0f;
//
//            // ��ȡ�����任����
//            FTransform BoneTransform = SkelMeshComp->GetBoneTransform(BoneIndex);
//
//            // Ӧ�ù����任����Ȩ
//            SkinnedVertexPosition += BoneTransform.TransformPosition(LocalVertexPos) * Weight;
//        }
//
//        // ����Ƥ��Ķ���λ��ת��������ռ�
//        FVector WorldVertexPos = ComponentToWorld.TransformPosition(SkinnedVertexPosition);
//
//        // ��ת��������綥���������
//        OutOriginalVertexPositions.Add(WorldVertexPos);
//    }
//    /*for (const FSkeletalMeshLODModel* LODModel : Model->LODModels)
//    {
//        for (const FSkelMeshSection& Section : LODModel.Sections)
//        {
//            for (const FSoftSkinVertex& Vertex : Section.SoftVertices)
//            {
//                OutOriginalVertexPositions.Add(Vertex.Position);
//            }
//        }
//    }*/
//}
//
//// �������������Transform��ƫ��
//void AKCharacter::CacheBoneTransforms(USkeletalMeshComponent* SkelMeshComp, float ScaleFactor, TArray<FTransform>& OutBoneOffsets)
//{
//    int32 NumBones = SkelMeshComp->GetNumBones();
//    for (int32 BoneIndex = 0; BoneIndex < NumBones; ++BoneIndex)
//    {
//        FTransform BoneTransform = SkelMeshComp->BoneSpaceTransforms[BoneIndex];
//        FVector ScaledLocation = BoneTransform.GetLocation() * ScaleFactor;
//        BoneTransform.SetLocation(ScaledLocation);
//        OutBoneOffsets.Add(BoneTransform);
//    }
//}
//
//// ��������������λ��
//void AKCharacter::AdjustBonePositions(USkeletalMeshComponent* SkelMeshComp, const TArray<FTransform>& BoneOffsets)
//{
//    int32 NumBones = SkelMeshComp->GetNumBones();
//    for (int32 BoneIndex = 0; BoneIndex < NumBones; ++BoneIndex)
//    {
//        SkelMeshComp->BoneSpaceTransforms[BoneIndex] = BoneOffsets[BoneIndex];
//    }
//}
//
//// ���������ݹ���Ȩ�ص�������λ��
//void AKCharacter::AdjustVertexPositionsWithBoneWeights(USkeletalMeshComponent* SkelMeshComp, const TArray<FVector>& OriginalVertexPositions)
//{
//    USkeletalMesh* MeshAsset = SkelMeshComp->GetSkeletalMeshAsset();
//    if (!MeshAsset) return;
//
//    FSkeletalMeshModel* Model = MeshAsset->GetImportedModel();
//    if (!Model) return;
//
//    int32 VertexIndex = 0;
//    //for (FSkeletalMeshLODModel& LODModel : Model->LODModels)
//    //{
//    //    for (FSkelMeshSection& Section : LODModel.Sections)
//    //    {
//    //        for (FSoftSkinVertex& Vertex : Section.SoftVertices)
//    //        {
//    //            if (VertexIndex < OriginalVertexPositions.Num())
//    //            {
//    //                FVector NewPosition = FVector::ZeroVector;
//
//    //                // ʹ�ö���Ȩ�������¼�����λ��
//    //                for (int32 InfluenceIndex = 0; InfluenceIndex < MAX_TOTAL_INFLUENCES; ++InfluenceIndex)
//    //                {
//    //                    int32 BoneIndex = Vertex.InfluenceBones[InfluenceIndex];
//    //                    float BoneWeight = Vertex.InfluenceWeights[InfluenceIndex] / 255.0f;
//
//    //                    if (BoneIndex >= 0 && BoneIndex < SkelMeshComp->GetNumBones())
//    //                    {
//    //                        const FTransform& BoneTransform = SkelMeshComp->BoneSpaceTransforms[BoneIndex];
//    //                        FVector TransformedPosition = BoneTransform.TransformPosition(OriginalVertexPositions[VertexIndex]);
//    //                        NewPosition += TransformedPosition * BoneWeight;
//    //                    }
//    //                }
//
//    //                // ���¶���λ��
//    //                Vertex.Position = NewPosition;
//    //                VertexIndex++;
//    //            }
//    //        }
//    //    }
//    //}
//
//    // ˢ������
//    SkelMeshComp->MarkRenderStateDirty();
//}