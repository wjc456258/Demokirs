#include "GamePlay/AnimNode_ModifyBones.h"
#include "AnimationRuntime.h"
#include "Animation/AnimInstanceProxy.h"

// ���캯��
FAnimNode_ModifyBones::FAnimNode_ModifyBones()
{
    // Ĭ�ϲ�����ʼ��
    TranslationOffset = FVector::ZeroVector;
    RotationOffset = FRotator::ZeroRotator;
    ScaleOffset = FVector(1.0f, 1.0f, 1.0f);
}

// �������ó�ʼ��
void FAnimNode_ModifyBones::InitializeBoneReferences(const FBoneContainer& RequiredBones)
{
    for (FBoneReference& BoneRef : BonesToModify)
    {
        BoneRef.Initialize(RequiredBones);
    }
}

// ������������
void FAnimNode_ModifyBones::EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms)
{
    // ������Ҫ�޸ĵĹ����б�
    for (const FBoneReference& BoneRef : BonesToModify)
    {
        // �����Ƿ���Ч
        if (BoneRef.IsValidToEvaluate(Output.AnimInstanceProxy->GetRequiredBones()))
        {
            // ��ȡ�����ĵ�ǰ�任
            FCompactPoseBoneIndex CompactBoneIndex(BoneRef.BoneIndex);
            FTransform BoneTransform = Output.Pose.GetComponentSpaceTransform(CompactBoneIndex);

            // Ӧ��ƽ�ơ���ת�����ű任
            BoneTransform.AddToTranslation(TranslationOffset);
            BoneTransform.ConcatenateRotation(RotationOffset.Quaternion());
            BoneTransform.SetScale3D(BoneTransform.GetScale3D() * ScaleOffset);

            // �洢�޸ĺ�ı任
            OutBoneTransforms.Add(FBoneTransform(CompactBoneIndex, BoneTransform));
        }
    }
}

// �����Ƿ���Ч
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