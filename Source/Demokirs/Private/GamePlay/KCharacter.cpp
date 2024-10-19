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
    // 调整角色的身高
    // 假设基准身高是180，目标身高是100
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
// 初始化函数
void AKCharacter::InitializeCharacter(float CharacterHeight, float BaseHeight)
{
    // 步骤1: 获取角色的 SKM 和身高比值
    USkeletalMeshComponent* SkelMeshComp = GetMesh(); // 假设你已经有一个 Skeletal Mesh Component
    if (!SkelMeshComp)
    {
        UE_LOG(LogTemp, Error, TEXT("SkeletalMeshComponent is null!"));
        return;
    }

    float HeightRatio = CharacterHeight / BaseHeight;
    SkelMeshComp->PrimaryComponentTick.bCanEverTick = false;
    // 步骤2: 初始化角色并设置为不可见
    SkelMeshComp->SetVisibility(false);

    // 缓存数组
    TArray<FVertexInfo> CachedVertexInfo;
    TArray<float> CachedBoneLengths;
    //FVector BoneLocation = SkelMeshComp->GetSkeletalMeshAsset()->GetRefSkeleton().GetRefBonePose()[1].GetLocation();
    //UE_LOG(LogTemp, Error, TEXT("BoneLocation is %s!"), *BoneLocation.ToString());
    FVector BoneLocation1 = SkelMeshComp->GetBoneTransform(1).GetLocation();
    UE_LOG(LogTemp, Error, TEXT("BoneLocation1 is %s!"), *BoneLocation1.ToString());
    //FVector BoneLocation2 = SkelMeshComp->GetComponentTransform(1).GetLocation();
    //UE_LOG(LogTemp, Error, TEXT("SkeletalMeshComponent is null!"));
    // 调整骨骼缩放比例
    //AdjustSkeletalMesh(SkelMeshComp, HeightRatio);
    
    // 存储所有顶点的世界坐标、骨骼权重、骨骼长度等信息
    //CacheVertexAndBoneInfo(SkelMeshComp, HeightRatio, CachedVertexInfo, CachedBoneLengths);
    int32 LODIndex = 0; // 通常是 LOD0，也可以遍历所有 LOD
    if (SkelMeshComp && SkelMeshComp->GetSkeletalMeshRenderData())
    {
        FSkeletalMeshRenderData* SkelMeshRenderData = SkelMeshComp->GetSkeletalMeshRenderData();
        FSkeletalMeshLODRenderData& LODData = SkelMeshRenderData->LODRenderData[LODIndex];

        for (uint32 i = 0; i < LODData.GetNumVertices(); ++i)
        {
            // 获取局部顶点
            FVector LocalPosition = FVector(LODData.StaticVertexBuffers.PositionVertexBuffer.VertexPosition(i));

            // 转换为世界空间
            FVector WorldPosition = SkelMeshComp->GetComponentTransform().TransformPosition(LocalPosition * HeightRatio);

            // 获取骨骼权重
            TArray<float> BoneWeights; // 假设你已经获取了每个顶点的骨骼权重

            // 缓存顶点信息
            CachedVertexInfo.Add(FVertexInfo{ WorldPosition, BoneWeights });
        }

        // 缓存骨骼长度信息
        // 假设你通过一些计算获取了骨骼的世界长度并缓存它们
        for (int32 BoneIndex = 0; BoneIndex < SkelMeshComp->GetNumBones(); ++BoneIndex)
        {
            // 根据骨骼长度和比例缓存数据
            float BoneLength = SkelMeshComp->GetBoneTransform(BoneIndex).GetLocation().Size();
            CachedBoneLengths.Add(BoneLength * HeightRatio);
        }
    }
    // 步骤3: 将角色的缩放还原为 1.0
    //SkelMeshComp->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));

    // 将缓存的顶点数据转换回模型空间并覆盖
    //RestoreVertexInfo(SkelMeshComp, CachedVertexInfo);

    // 步骤4: 使用新缓存的骨骼长度，调整 Transform 并重设骨骼长度
    //AdjustBoneTransforms(SkelMeshComp, CachedBoneLengths);
    //for (int32 BoneIndex = 0; BoneIndex < SkelMeshComp->GetNumBones(); ++BoneIndex)
    //{
    //    FTransform BoneTransform = SkelMeshComp->GetBoneTransform(BoneIndex);

    //    // 使用缓存的骨骼长度调整偏移
    //    FVector AdjustedBonePosition = BoneTransform.GetLocation().GetSafeNormal() * CachedBoneLengths[BoneIndex];

    //    // 设置新的骨骼位置
    //    BoneTransform.SetLocation(AdjustedBonePosition);

    //    // 更新骨骼变换
    //    //SkelMeshComp->SetBoneTransformByName(SkelMeshComp->GetBoneName(BoneIndex), BoneTransform, EBoneSpaces::ComponentSpace);
    //    SkelMeshComp->BoneSpaceTransforms[BoneIndex] = BoneTransform;
    //}
    //FReferenceSkeleton& RefSkeleton = GetMesh()->SkeletalMesh->GetRefSkeleton();
    //FReferenceSkeletonModifier RefSkelModifier(RefSkeleton, GetMesh()->SkeletalMesh->GetSkeleton());
    //int32 NumBones = RefSkeleton.GetNum(); // 获取骨骼总数

    //for (int32 BoneIndex = 0; BoneIndex < NumBones; ++BoneIndex)
    //{
    //    if (BoneIndex >= 0 && BoneIndex < NumBones)
    //    {
    //        // 这里的 BoneIndex 是有效的，可以进行安全的操作
    //        FTransform BoneTransform = GetMesh()->SkeletalMesh->GetRefSkeleton().GetRefBonePose()[BoneIndex];
    //        BoneTransform.SetLocation(BoneTransform.GetLocation()*0.4);
    //        // 进行骨骼变换修改

    //        RefSkelModifier.UpdateRefPoseTransform(BoneIndex, BoneTransform);
    //    }
    //    else
    //    {
    //        // BoneIndex 无效，输出警告或错误信息
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
    // 步骤5: 保持顶点与骨骼的权重关系不变

    // 步骤6: 将调整后的 SKM 作为最终的 SKM，清理缓存数据并显示出来
    SkelMeshComp->SetVisibility(true);
}

void AKCharacter::AdjustSkeletalMesh(USkeletalMeshComponent* SkelMeshComp, float HeightRatio)
{
    // 假设这里调整骨骼长度等操作
    SkelMeshComp->SetWorldScale3D(FVector(HeightRatio, HeightRatio, HeightRatio));

    // 可扩展逻辑，根据需求增加变换
}

void AKCharacter::CacheVertexAndBoneInfo(USkeletalMeshComponent* SkelMeshComp, float HeightRatio, TArray<FVertexInfo>& CachedVertexInfo, TArray<float>& CachedBoneLengths)
{
    // 迭代每个 LOD 的顶点，获取并转换为世界坐标
    int32 LODIndex = 0; // 通常是 LOD0，也可以遍历所有 LOD
    if (SkelMeshComp && SkelMeshComp->GetSkeletalMeshRenderData())
    {
        FSkeletalMeshRenderData* SkelMeshRenderData = SkelMeshComp->GetSkeletalMeshRenderData();
        FSkeletalMeshLODRenderData& LODData = SkelMeshRenderData->LODRenderData[LODIndex];

        for (uint32 i = 0; i < LODData.GetNumVertices(); ++i)
        {
            // 获取局部顶点
            FVector LocalPosition = FVector(LODData.StaticVertexBuffers.PositionVertexBuffer.VertexPosition(i));

            // 转换为世界空间
            FVector WorldPosition = SkelMeshComp->GetComponentTransform().TransformPosition(LocalPosition * HeightRatio);

            // 获取骨骼权重
            TArray<float> BoneWeights; // 假设你已经获取了每个顶点的骨骼权重

            // 缓存顶点信息
            CachedVertexInfo.Add(FVertexInfo{ WorldPosition, BoneWeights });
        }

        // 缓存骨骼长度信息
        // 假设你通过一些计算获取了骨骼的世界长度并缓存它们
        for (int32 BoneIndex = 0; BoneIndex < SkelMeshComp->GetNumBones(); ++BoneIndex)
        {
            // 根据骨骼长度和比例缓存数据
            float BoneLength = SkelMeshComp->GetBoneTransform(BoneIndex).GetLocation().Size();
            CachedBoneLengths.Add(BoneLength * HeightRatio);
        }
    }
}

void AKCharacter::RestoreVertexInfo(USkeletalMeshComponent* SkelMeshComp, const TArray<FVertexInfo>& CachedVertexInfo)
{
    // 假设你缓存了所有顶点的位置和骨骼数据

    // 遍历每个 LOD 并重新设置顶点位置
    int32 LODIndex = 0;
    if (SkelMeshComp && SkelMeshComp->GetSkeletalMeshRenderData())
    {
        FSkeletalMeshRenderData* SkelMeshRenderData = SkelMeshComp->GetSkeletalMeshRenderData();
        FSkeletalMeshLODRenderData& LODData = SkelMeshRenderData->LODRenderData[LODIndex];

        for (uint32 i = 0; i < LODData.GetNumVertices(); ++i)
        {
            // 重新将世界坐标转换为模型空间坐标
            FVector NewLocalPosition = SkelMeshComp->GetComponentTransform().InverseTransformPosition(CachedVertexInfo[i].WorldPosition);

            // 重新设置顶点位置为新的模型空间坐标
            LODData.StaticVertexBuffers.PositionVertexBuffer.VertexPosition(i) = FVector3f(NewLocalPosition);
        }
    }
}

void AKCharacter::AdjustBoneTransforms(USkeletalMeshComponent* SkelMeshComp, const TArray<float>& CachedBoneLengths)
{
    // 对每个骨骼应用缓存的长度信息，进行位置偏移调整，而不是缩放
    for (int32 BoneIndex = 0; BoneIndex < SkelMeshComp->GetNumBones(); ++BoneIndex)
    {
        FTransform BoneTransform = SkelMeshComp->GetBoneTransform(BoneIndex);

        // 使用缓存的骨骼长度调整偏移
        FVector AdjustedBonePosition = BoneTransform.GetLocation().GetSafeNormal() * CachedBoneLengths[BoneIndex];

        // 设置新的骨骼位置
        BoneTransform.SetLocation(AdjustedBonePosition);

        // 更新骨骼变换
        //SkelMeshComp->SetBoneTransformByName(SkelMeshComp->GetBoneName(BoneIndex), BoneTransform, EBoneSpaces::ComponentSpace);
        SkelMeshComp->BoneSpaceTransforms[BoneIndex] = BoneTransform;
    }
}

void GetVertexBoneWeights(const USkinnedMeshComponent* SkinnedMeshComponent, TArray<FVector>& OutVertexPositions, TArray<TArray<FVector2D>>& OutVertexBoneWeights)
{
    
}



//// 主函数：调整角色的Mesh高度
//void AKCharacter::AdjustCharacterMeshHeight(USkeletalMeshComponent* SkelMeshComp, float CharacterHeight, float BaseHeight)
//{
//    if (!SkelMeshComp || !SkelMeshComp->GetSkeletalMeshAsset())
//    {
//        UE_LOG(LogTemp, Error, TEXT("Invalid SkeletalMeshComponent or SkeletalMeshAsset"));
//        return;
//    }
//
//    // Step 1: 计算缩放比例
//    float ScaleFactor = CharacterHeight / BaseHeight;
//
//    // Step 2: 初始化并设置不可见，缩放SKM
//    SkelMeshComp->SetWorldScale3D(FVector(ScaleFactor));
//    TArray<FVector> OriginalVertexPositions;
//    CacheOriginalVertexPositions(SkelMeshComp, OriginalVertexPositions);
//
//    // Step 3: 计算每个骨骼的新位置，存储所有骨骼的长度和偏移
//    //TArray<FVector> ScaledBonePositions;
//    TArray<FTransform> BoneOffsets;
//    CacheBoneTransforms(SkelMeshComp, ScaleFactor, BoneOffsets);
//
//    // Step 4: 还原Scale并重设顶点与骨骼的偏移
//    SkelMeshComp->SetWorldScale3D(FVector(1.0f));
//    AdjustBonePositions(SkelMeshComp, BoneOffsets);
//    AdjustVertexPositionsWithBoneWeights(SkelMeshComp, OriginalVertexPositions);
//
//    // Step 5: 清理并显示角色
//    SkelMeshComp->MarkRenderStateDirty();
//    SkelMeshComp->SetVisibility(true);
//}
//
//// 函数：缓存原始顶点位置
//void AKCharacter::CacheOriginalVertexPositions(USkeletalMeshComponent* SkelMeshComp, TArray<FVector>& OutOriginalVertexPositions)
//{
//    //USkeletalMesh* MeshAsset = SkelMeshComp->GetSkeletalMeshAsset();
//    //if (!MeshAsset) return;
//
//    //const FSkeletalMeshModel* Model = MeshAsset->GetImportedModel();
//    //if (!Model) return;
//    //FTransform ComponentTransform = SkelMeshComp->GetComponentTransform();
//
//    //// 遍历 LOD 0 所有顶点，转换到世界坐标
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
//    //    // Step 5: 存储骨骼数据
//    //    // 获取蒙皮数据，包括顶点对应的骨骼权重
//    //    for (int32 SectionIndex = 0; SectionIndex < LODData.RenderSections.Num(); SectionIndex++)
//    //    {
//    //        const FSkelMeshRenderSection& Section = LODData.RenderSections[SectionIndex];
//    //        const FMultiSizeIndexContainer& IndexContainer = Section.IndexBuffer;
//    //        for (int32 VertexIndex = 0; VertexIndex < Section.NumVertices; VertexIndex++)
//    //        {
//    //            // 存储骨骼索引和权重 (简化处理)
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
//    // 获取网格的渲染数据
//    FSkeletalMeshRenderData* RenderData = SkelMeshComp->GetSkeletalMeshRenderData();
//    if (!RenderData || RenderData->LODRenderData.Num() == 0)
//    {
//        return;
//    }
//
//    // 处理 LOD 0 的数据
//    FSkeletalMeshLODRenderData& LODData = RenderData->LODRenderData[0];
//
//    // 获取顶点缓冲区和骨骼蒙皮权重缓冲区
//    const FPositionVertexBuffer& VertexBuffer = LODData.StaticVertexBuffers.PositionVertexBuffer;
//    const FSkinWeightVertexBuffer& SkinWeightBuffer = LODData.SkinWeightVertexBuffer;
//
//    // 获取世界变换
//    FTransform ComponentToWorld = SkelMeshComp->GetComponentTransform();
//
//    // 遍历所有顶点
//    for (uint32 VertexIndex = 0; VertexIndex < VertexBuffer.GetNumVertices(); VertexIndex++)
//    {
//        FVector SkinnedVertexPosition = FVector::ZeroVector;
//
//        // 获取当前顶点的位置（局部空间）
//        FVector LocalVertexPos = FVector(VertexBuffer.VertexPosition(VertexIndex));
//
//        // 获取每个顶点的影响骨骼信息和权重
//        FSkinWeightInfo SkinWeightInfo = SkinWeightBuffer.GetVertexSkinWeights(VertexIndex);
//
//        // 遍历每个顶点的骨骼影响（通常有 4 个最大权重）
//        for (int32 InfluenceIndex = 0; InfluenceIndex < MAX_TOTAL_INFLUENCES; InfluenceIndex++)
//        {
//            // 获取骨骼索引和对应的权重
//            int32 BoneIndex = SkinWeightInfo.InfluenceBones[InfluenceIndex];
//            float Weight = SkinWeightInfo.InfluenceWeights[InfluenceIndex] / 255.0f;
//
//            // 获取骨骼变换矩阵
//            FTransform BoneTransform = SkelMeshComp->GetBoneTransform(BoneIndex);
//
//            // 应用骨骼变换并加权
//            SkinnedVertexPosition += BoneTransform.TransformPosition(LocalVertexPos) * Weight;
//        }
//
//        // 将蒙皮后的顶点位置转换到世界空间
//        FVector WorldVertexPos = ComponentToWorld.TransformPosition(SkinnedVertexPosition);
//
//        // 将转换后的世界顶点存入数组
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
//// 函数：缓存骨骼Transform与偏移
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
//// 函数：调整骨骼位置
//void AKCharacter::AdjustBonePositions(USkeletalMeshComponent* SkelMeshComp, const TArray<FTransform>& BoneOffsets)
//{
//    int32 NumBones = SkelMeshComp->GetNumBones();
//    for (int32 BoneIndex = 0; BoneIndex < NumBones; ++BoneIndex)
//    {
//        SkelMeshComp->BoneSpaceTransforms[BoneIndex] = BoneOffsets[BoneIndex];
//    }
//}
//
//// 函数：根据骨骼权重调整顶点位置
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
//    //                // 使用顶点权重来重新计算新位置
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
//    //                // 更新顶点位置
//    //                Vertex.Position = NewPosition;
//    //                VertexIndex++;
//    //            }
//    //        }
//    //    }
//    //}
//
//    // 刷新网格
//    SkelMeshComp->MarkRenderStateDirty();
//}