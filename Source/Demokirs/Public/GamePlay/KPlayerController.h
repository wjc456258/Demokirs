// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KPlayerController.generated.h"

/**
 * 
 */

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
UCLASS()
class DEMOKIRS_API AKPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
    virtual void BeginPlay() override;

public:
    virtual void SetupInputComponent() override;

private:
    // ����ӳ�������ģ����ڶ��������붯��֮���ӳ���ϵ
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputMappingContext* DefaultMappingContext;

    // �ƶ����붯��
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* MoveAction;

    // ��Ծ���붯��
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* JumpAction;

    // �ӽǿ������붯��
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* LookAction;

    // �����ƶ�����
    void HandleMove(const FInputActionValue& Value);

    // ������Ծ��ʼ����
    void HandleJump();

    // ������Ծֹͣ����
    void HandleStopJump();

    // �����ӽǿ�������
    void HandleLook(const FInputActionValue& Value);
};
