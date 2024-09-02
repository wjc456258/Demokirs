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
    // 这通常在动画实例初始化时调用
    Super::NativeInitializeAnimation();

    // 你可以在这里做任何初始化工作
}

void UKAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    FScopeLock Lock(&MyCriticalSection);
    // 更新动画状态，例如检查角色是否在跳跃
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
    //            int32 NumBones = RefSkeleton.GetNum(); // 获取骨骼总数

    //            for (int32 BoneIndex = 0; BoneIndex < NumBones; ++BoneIndex)
    //            {
    //                if (BoneIndex >= 0 && BoneIndex < NumBones)
    //                {
    //                    // 这里的 BoneIndex 是有效的，可以进行安全的操作
    //                    FTransform BoneTransform = RefSkeleton.GetRefBonePose()[BoneIndex];
    //                    BoneTransform.SetLocation(BoneTransform.GetLocation() * 0.4);
    //                    // 进行骨骼变换修改

    //                    RefSkelModifier.UpdateRefPoseTransform(BoneIndex, BoneTransform);
    //                }
    //                else
    //                {
    //                    // BoneIndex 无效，输出警告或错误信息
    //                    UE_LOG(LogTemp, Warning, TEXT("Invalid BoneIndex: %d"), BoneIndex);
    //                }
    //            }
    //            SkeletalMesh->PostEditChange();
    //            SkeletalMesh->MarkPackageDirty();
    //        }
    //    }
    //}
}


