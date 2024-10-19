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

    // ���� DataAsset ����������
    for (TFieldIterator<FProperty> PropIt(DataAsset->GetClass()); PropIt; ++PropIt)
    {
        FProperty* Property = *PropIt;

        // ����Ƿ�Ϊ������������
        if (FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
        {
            // ����Ƕ������У�ֱ�Ӵ���
            if (ObjectProperty->PropertyClass == UAnimSequence::StaticClass())
            {
                UAnimSequence* AnimSequence = Cast<UAnimSequence>(ObjectProperty->GetObjectPropertyValue_InContainer(DataAsset));
                if (AnimSequence)
                {
                    UE_LOG(LogTemp, Log, TEXT("Found AnimSequence: %s in DataAsset: %s"), *AnimSequence->GetName(), *DataAsset->GetName());
                }
            }
            // �����Ƕ�׵� DataAsset���ݹ����
            else if (ObjectProperty->PropertyClass->IsChildOf(UDataAsset::StaticClass()))
            {
                UObject* NestedDataAsset = ObjectProperty->GetObjectPropertyValue_InContainer(DataAsset);
                if (NestedDataAsset)
                {
                    UE_LOG(LogTemp, Log, TEXT("Found Nested DataAsset: %s"), *NestedDataAsset->GetName());
                    ScanDataAssetForAnimSequences(NestedDataAsset); // �ݹ�ɨ��Ƕ�׵� DataAsset
                }
            }
        }
        // ����Ƿ�Ϊ�������� (�� TArray<UAnimSequence*>)
        else if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property))
        {
            if (FObjectProperty* ArrayInnerProperty = CastField<FObjectProperty>(ArrayProperty->Inner))
            {
                if (ArrayInnerProperty->PropertyClass == UAnimSequence::StaticClass())
                {
                    // ��ȡ�����е�Ԫ��
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
        //�����������Ϳ������ƴ������� TMap �� TSet
        //����ֻ��ʾ����ʵ�ʴ���ʱҪ���ݾ����������͵���
    }
}

void UAnimationSequenceScanner::ScanAllDataAssets()
{
    // ������Ŀ�����е� Data Asset
    for (TObjectIterator<UDataAsset> It; It; ++It)
    {
        UDataAsset* DataAsset = *It;
        if (DataAsset)
        {
            ScanDataAssetForAnimSequences(DataAsset);
        }
    }
}