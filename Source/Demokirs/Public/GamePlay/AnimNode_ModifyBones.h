#pragma once

#include "CoreMinimal.h"
//#include "Animation/AnimNodeBase.h"
#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "AnimGraphNode_SkeletalControlBase.h"
#include "AnimNode_ModifyBones.generated.h"

// 自定义动画节点类
USTRUCT(BlueprintInternalUseOnly)
struct FAnimNode_ModifyBones : public FAnimNode_SkeletalControlBase
{
    GENERATED_BODY()

public:
    // 配置的骨骼数组，供蓝图中设置
    UPROPERTY(EditAnywhere, Category = "Bones")
    TArray<FBoneReference> BonesToModify;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform", meta = (PinShownByDefault))
    FVector TranslationOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform", meta = (PinShownByDefault))
    FRotator RotationOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform", meta = (PinShownByDefault))
    FVector ScaleOffset;

public:
    // 构造函数
    FAnimNode_ModifyBones();

    // 初始化骨骼引用
    virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;

protected:
    // 骨骼控制评估
    virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;

    // 骨骼是否有效
    virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;

  /*  UPROPERTY(EditAnywhere, Category = "Settings")
    TArray<FBoneReference> BonesToModify;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    TArray<FVector> BoneOffsets;

    virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;*/
};

// 自定义动画图节点类
UCLASS(meta = (Keywords = "Modify Bones"))
class UAnimGraphNode_ModifyBones : public UAnimGraphNode_SkeletalControlBase
{
    GENERATED_BODY()

public:
    // 节点标题
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
    {
        return FText::FromString(TEXT("Modify Bones"));
    }

    // 返回节点数据
    virtual const FAnimNode_SkeletalControlBase* GetNode() const override
    {
        return &Node;
    }

protected:
    // 动画节点数据
    UPROPERTY(EditAnywhere, Category = "Settings")
    FAnimNode_ModifyBones Node;
};