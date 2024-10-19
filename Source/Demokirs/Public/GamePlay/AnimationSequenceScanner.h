#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AnimationSequenceScanner.generated.h"

UCLASS()
class DEMOKIRS_API UAnimationSequenceScanner : public UObject
{
    GENERATED_BODY()

public:
    static void ScanAllDataAssets();
    static void ScanDataAssetForAnimSequences(UObject* DataAsset);
};