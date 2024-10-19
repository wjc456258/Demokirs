#include "Gameplay/AnimationSequenceScanner.h"
#include "Engine/DataAsset.h"
#include "Animation/AnimSequence.h"
#include "UObject/UObjectIterator.h"
#include "UObject/PropertyPortFlags.h"

void UAnimationSequenceScanner::ScanDataAssetForAnimSequences(UObject* DataAsset)
{
    if (!DataAsset)
    {
        return;
    }

    // 迭代 DataAsset 的所有属性
    for (TFieldIterator<FProperty> PropIt(DataAsset->GetClass()); PropIt; ++PropIt)
    {
        FProperty* Property = *PropIt;

        // 检查是否为对象类型属性
        if (FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
        {
            // 如果是动画序列，直接处理
            if (ObjectProperty->PropertyClass == UAnimSequence::StaticClass())
            {
                UAnimSequence* AnimSequence = Cast<UAnimSequence>(ObjectProperty->GetObjectPropertyValue_InContainer(DataAsset));
                if (AnimSequence)
                {
                    UE_LOG(LogTemp, Log, TEXT("Found AnimSequence: %s in DataAsset: %s"), *AnimSequence->GetName(), *DataAsset->GetName());
                }
            }
            // 如果是嵌套的 DataAsset，递归调用
            else if (ObjectProperty->PropertyClass->IsChildOf(UDataAsset::StaticClass()))
            {
                UObject* NestedDataAsset = ObjectProperty->GetObjectPropertyValue_InContainer(DataAsset);
                if (NestedDataAsset)
                {
                    UE_LOG(LogTemp, Log, TEXT("Found Nested DataAsset: %s"), *NestedDataAsset->GetName());
                    ScanDataAssetForAnimSequences(NestedDataAsset); // 递归扫描嵌套的 DataAsset
                }
            }
        }
        // 检查是否为容器类型 (如 TArray<UAnimSequence*>)
        else if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property))
        {
            if (FObjectProperty* ArrayInnerProperty = CastField<FObjectProperty>(ArrayProperty->Inner))
            {
                if (ArrayInnerProperty->PropertyClass == UAnimSequence::StaticClass())
                {
                    // 获取容器中的元素
                    FScriptArrayHelper ArrayHelper(ArrayProperty, ArrayProperty->ContainerPtrToValuePtr<void>(DataAsset));
                    for (int32 i = 0; i < ArrayHelper.Num(); ++i)
                    {
                        UObject* ArrayElement = ArrayInnerProperty->GetObjectPropertyValue(ArrayHelper.GetRawPtr(i));
                        UAnimSequence* AnimSequence = Cast<UAnimSequence>(ArrayElement);
                        if (AnimSequence)
                        {
                            UE_LOG(LogTemp, Log, TEXT("Found AnimSequence in Array: %s in DataAsset: %s"), *AnimSequence->GetName(), *DataAsset->GetName());
                        }
                    }
                }
            }
        }
        //其他容器类型可以类似处理，比如 TMap 或 TSet
        //这里只是示例，实际处理时要根据具体容器类型调整
    }
}

void UAnimationSequenceScanner::ScanAllDataAssets()
{
    // 遍历项目中所有的 Data Asset
    for (TObjectIterator<UDataAsset> It; It; ++It)
    {
        UDataAsset* DataAsset = *It;
        if (DataAsset)
        {
            ScanDataAssetForAnimSequences(DataAsset);
        }
    }
}