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
    // ���캯��
    UKAnimInstance();

    // ��д����ͼ���º��������ڸ��¶���״̬
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
    FCriticalSection MyCriticalSection;
protected:
    // �Զ����ʼ������
    virtual void NativeInitializeAnimation() override;
	
	
};
