#pragma once

#include "CoreMinimal.h"
//#include "Animation/AnimNodeBase.h"
#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "AnimGraphNode_SkeletalControlBase.h"
#include "AnimNode_ModifyBones.generated.h"

// �Զ��嶯���ڵ���
USTRUCT(BlueprintInternalUseOnly)
struct FAnimNode_ModifyBones : public FAnimNode_SkeletalControlBase
{
    GENERATED_BODY()

public:
    // ���õĹ������飬����ͼ������
    UPROPERTY(EditAnywhere, Category = "Bones")
    TArray<FBoneReference> BonesToModify;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform", meta = (PinShownByDefault))
    FVector TranslationOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform", meta = (PinShownByDefault))
    FRotator RotationOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform", meta = (PinShownByDefault))
    FVector ScaleOffset;

public:
    // ���캯��
    FAnimNode_ModifyBones();

    // ��ʼ����������
    virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;

protected:
    // ������������
    virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;

    // �����Ƿ���Ч
    virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;

  /*  UPROPERTY(EditAnywhere, Category = "Settings")
    TArray<FBoneReference> BonesToModify;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    TArray<FVector> BoneOffsets;

    virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;*/
};

// �Զ��嶯��ͼ�ڵ���
UCLASS(meta = (Keywords = "Modify Bones"))
class UAnimGraphNode_ModifyBones : public UAnimGraphNode_SkeletalControlBase
{
    GENERATED_BODY()

public:
    // �ڵ����
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
    {
        return FText::FromString(TEXT("Modify Bones"));
    }

    // ���ؽڵ�����
    virtual const FAnimNode_SkeletalControlBase* GetNode() const override
    {
        return &Node;
    }

protected:
    // �����ڵ�����
    UPROPERTY(EditAnywhere, Category = "Settings")
    FAnimNode_ModifyBones Node;
};