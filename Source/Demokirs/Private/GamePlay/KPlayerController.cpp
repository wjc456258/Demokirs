// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/KPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Gameplay/KPlayerCharacter.h"

void AKPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // ��ȡ��ǿ������ϵͳ
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(DefaultMappingContext, 0);
    }
}

void AKPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        // ���ƶ��¼�
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AKPlayerController::HandleMove);

        // ����Ծ�¼�
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AKPlayerController::HandleJump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AKPlayerController::HandleStopJump);
        
        // ���ӽǿ����¼�
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AKPlayerController::HandleLook);
    }
}

void AKPlayerController::HandleMove(const FInputActionValue& Value)
{
    if (AKPlayerCharacter* PlayerCharacter = Cast<AKPlayerCharacter>(GetPawn()))
    {
        PlayerCharacter->Move(Value);
    }
}

void AKPlayerController::HandleJump()
{
    if (AKPlayerCharacter* PlayerCharacter = Cast<AKPlayerCharacter>(GetPawn()))
    {
        PlayerCharacter->Jump();
    }
}

void AKPlayerController::HandleStopJump()
{
    if (AKPlayerCharacter* PlayerCharacter = Cast<AKPlayerCharacter>(GetPawn()))
    {
        PlayerCharacter->StopJumping();
    }
}

void AKPlayerController::HandleLook(const FInputActionValue& Value)
{
    if (AKPlayerCharacter* PlayerCharacter = Cast<AKPlayerCharacter>(GetPawn()))
    {
        PlayerCharacter->Look(Value);
    }
}