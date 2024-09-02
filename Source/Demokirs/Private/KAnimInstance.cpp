// Fill out your copyright notice in the Description page of Project Settings.


#include "KAnimInstance.h"
#include "GamePlay/KCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
UKAnimInstance::UKAnimInstance()
{
    
}

void UKAnimInstance::NativeInitializeAnimation()
{
    // ��ͨ���ڶ���ʵ����ʼ��ʱ����
    Super::NativeInitializeAnimation();

    // ��������������κγ�ʼ������
}

void UKAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    FScopeLock Lock(&MyCriticalSection);
    // ���¶���״̬���������ɫ�Ƿ�����Ծ
    //AKCharacter* OwningCharacter = Cast<AKCharacter>(TryGetPawnOwner());
    //if (OwningCharacter)
    //{
    //    USkeletalMeshComponent* SkeletalMeshComponent = OwningCharacter->GetMesh();
    //    if (SkeletalMeshComponent)
    //    {
    //        USkeletalMesh* SkeletalMesh = SkeletalMeshComponent->SkeletalMesh;
    //        if (SkeletalMesh && SkeletalMesh->GetSkeleton())
    //        {
    //            FReferenceSkeleton& RefSkeleton = SkeletalMesh->GetRefSkeleton();
    //            FReferenceSkeletonModifier RefSkelModifier(RefSkeleton, SkeletalMesh->GetSkeleton());
    //            int32 NumBones = RefSkeleton.GetNum(); // ��ȡ��������

    //            for (int32 BoneIndex = 0; BoneIndex < NumBones; ++BoneIndex)
    //            {
    //                if (BoneIndex >= 0 && BoneIndex < NumBones)
    //                {
    //                    // ����� BoneIndex ����Ч�ģ����Խ��а�ȫ�Ĳ���
    //                    FTransform BoneTransform = RefSkeleton.GetRefBonePose()[BoneIndex];
    //                    BoneTransform.SetLocation(BoneTransform.GetLocation() * 0.4);
    //                    // ���й����任�޸�

    //                    RefSkelModifier.UpdateRefPoseTransform(BoneIndex, BoneTransform);
    //                }
    //                else
    //                {
    //                    // BoneIndex ��Ч���������������Ϣ
    //                    UE_LOG(LogTemp, Warning, TEXT("Invalid BoneIndex: %d"), BoneIndex);
    //                }
    //            }
    //            SkeletalMesh->PostEditChange();
    //            SkeletalMesh->MarkPackageDirty();
    //        }
    //    }
    //}
}


