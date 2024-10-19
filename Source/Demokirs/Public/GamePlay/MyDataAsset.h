// MyDataAsset.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Animation/AnimSequence.h"
#include "Gameplay/AnimationSequenceScanner.h"
#include "MyDataAsset.generated.h"

/**
 * 这是一个自定义的DataAsset类，它包含了另一个DataAsset子类和动画序列
 */
UCLASS(BlueprintType)
class DEMOKIRS_API UMyDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    UFUNCTION(CallInEditor, Category = "Data")
    void GenerateCurve()
    {
        UAnimationSequenceScanner::ScanDataAssetForAnimSequences(this);
    }
    // 嵌套的DataAsset子类
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
    UMyDataAsset* SubDataAsset;

    // 动画序列
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
    UAnimSequence* AnimationSequence;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
    UAnimSequence* AnimationSequenceCopy;
};
