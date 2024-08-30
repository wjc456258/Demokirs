// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "KAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEMOKIRS_API UKAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
    // 构造函数
    UKAnimInstance();

    // 重写的蓝图更新函数，用于更新动画状态
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
    FCriticalSection MyCriticalSection;
protected:
    // 自定义初始化函数
    virtual void NativeInitializeAnimation() override;
	
	
};
