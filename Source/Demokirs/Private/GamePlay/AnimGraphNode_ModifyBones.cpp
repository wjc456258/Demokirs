#include "GamePlay/AnimNode_ModifyBones.h"
#include "AnimationRuntime.h"
#include "Animation/AnimInstanceProxy.h"

// 构造函数
FAnimNode_ModifyBones::FAnimNode_ModifyBones()
{
    // 默认参数初始化
    TranslationOffset = FVector::ZeroVector;
    RotationOffset = FRotator::ZeroRotator;
    ScaleOffset = FVector(1.0f, 1.0f, 1.0f);
}

// 骨骼引用初始化
void FAnimNode_ModifyBones::InitializeBoneReferences(const FBoneContainer& RequiredBones)
{
    for (FBoneReference& BoneRef : BonesToModify)
    {
        BoneRef.Initialize(RequiredBones);
    }
}

// 骨骼控制评估
void FAnimNode_ModifyBones::EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms)
{
    // 遍历需要修改的骨骼列表
    for (const FBoneReference& BoneRef : BonesToModify)
    {
        // 骨骼是否有效
        if (BoneRef.IsValidToEvaluate(Output.AnimInstanceProxy->GetRequiredBones()))
        {
            // 获取骨骼的当前变换
            FCompactPoseBoneIndex CompactBoneIndex(BoneRef.BoneIndex);
            FTransform BoneTransform = Output.Pose.GetComponentSpaceTransform(CompactBoneIndex);

            // 应用平移、旋转、缩放变换
            BoneTransform.AddToTranslation(TranslationOffset);
            BoneTransform.ConcatenateRotation(RotationOffset.Quaternion());
            BoneTransform.SetScale3D(BoneTransform.GetScale3D() * ScaleOffset);

            // 存储修改后的变换
            OutBoneTransforms.Add(FBoneTransform(CompactBoneIndex, BoneTransform));
        }
    }
}

// 骨骼是否有效
bool FAnimNode_ModifyBones::IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones)
{
    return BonesToModify.Num() > 0;
}
//#include "GamePlay/AnimNode_ModifyBones.h"
//#include "Animation/AnimInstanceProxy.h"
//
//void FAnimNode_ModifyBones::EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms)
//{
//    for (int32 i = 0; i < BonesToModify.Num(); ++i)
//    {
//        const FBoneReference& BoneRef = BonesToModify[i];
//        if (BoneRef.IsValidToEvaluate(Output.AnimInstanceProxy->GetRequiredBones()))
//        {
//            FCompactPoseBoneIndex CompactBoneIndex(BoneRef.BoneIndex);
//            FTransform BoneTransform = Output.Pose.GetComponentSpaceTransform(CompactBoneIndex);
//            FVector Offset = BoneOffsets.IsValidIndex(i) ? BoneOffsets[i] : FVector::ZeroVector;
//
//            BoneTransform.AddToTranslation(Offset);
//
//            OutBoneTransforms.Add(FBoneTransform(CompactBoneIndex, BoneTransform));
//        }
//    }
//}