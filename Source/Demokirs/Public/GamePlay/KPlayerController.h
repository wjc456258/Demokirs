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
    // 输入映射上下文，用于定义输入与动作之间的映射关系
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputMappingContext* DefaultMappingContext;

    // 移动输入动作
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* MoveAction;

    // 跳跃输入动作
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* JumpAction;

    // 视角控制输入动作
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* LookAction;

    // 处理移动输入
    void HandleMove(const FInputActionValue& Value);

    // 处理跳跃开始输入
    void HandleJump();

    // 处理跳跃停止输入
    void HandleStopJump();

    // 处理视角控制输入
    void HandleLook(const FInputActionValue& Value);
};
