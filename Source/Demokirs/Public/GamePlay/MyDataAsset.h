// MyDataAsset.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Animation/AnimSequence.h"
#include "Gameplay/AnimationSequenceScanner.h"
#include "MyDataAsset.generated.h"

/**
 * ����һ���Զ����DataAsset�࣬����������һ��DataAsset����Ͷ�������
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
    // Ƕ�׵�DataAsset����
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
    UMyDataAsset* SubDataAsset;

    // ��������
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
    UAnimSequence* AnimationSequence;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
    UAnimSequence* AnimationSequenceCopy;
};
