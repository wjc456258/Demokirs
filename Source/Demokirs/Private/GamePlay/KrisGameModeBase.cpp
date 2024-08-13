// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/KrisGameModeBase.h"

#include "UObject/ConstructorHelpers.h"
#include "GameFramework/HUD.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/SpectatorPawn.h"
#include "GameFramework/Character.h"

AKrisGameModeBase::AKrisGameModeBase()
{
    // 查找并加载HUD蓝图类
    static ConstructorHelpers::FClassFinder<AHUD> BlueprintHUD(TEXT("/Game/Blueprints/BP_HUD"));
    if (BlueprintHUD.Succeeded())
    {
        HUDClass = BlueprintHUD.Class;
    }

    // 查找并加载PlayerController蓝图类
    static ConstructorHelpers::FClassFinder<APlayerController> BlueprintPlayerController(TEXT("/Game/Blueprints/BP_PlayerController"));
    if (BlueprintPlayerController.Succeeded())
    {
        PlayerControllerClass = BlueprintPlayerController.Class;
    }

    // 查找并加载PlayerState蓝图类
    static ConstructorHelpers::FClassFinder<APlayerState> BlueprintPlayerState(TEXT("/Game/Blueprints/BP_PlayerState"));
    if (BlueprintPlayerState.Succeeded())
    {
        PlayerStateClass = BlueprintPlayerState.Class;
    }

    // 查找并加载GameState蓝图类
    static ConstructorHelpers::FClassFinder<AGameStateBase> BlueprintGameState(TEXT("/Game/Blueprints/BP_GameState"));
    if (BlueprintGameState.Succeeded())
    {
        GameStateClass = BlueprintGameState.Class;
    }

    // 查找并加载Spectator蓝图类
    static ConstructorHelpers::FClassFinder<ASpectatorPawn> BlueprintSpectator(TEXT("/Game/Blueprints/BP_SpectatorPawn"));
    if (BlueprintSpectator.Succeeded())
    {
        SpectatorClass = BlueprintSpectator.Class;
    }

    // 查找并加载Character蓝图类
    static ConstructorHelpers::FClassFinder<ACharacter> BlueprintCharacter(TEXT("/Script/Engine.Blueprint'/Game/GameAnimInstance/Blueprints/NewBlueprint.NewBlueprint_C'"));
    if (BlueprintCharacter.Succeeded())
    {
        DefaultPawnClass = BlueprintCharacter.Class;
    }
}

void AKrisGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    /*if (HUDClass != nullptr)
    {
        HUDClass = HUDClass;
    }

    if (PlayerControllerClass != nullptr)
    {
        PlayerControllerClass = PlayerControllerClass;
    }

    if (PlayerStateClass != nullptr)
    {
        PlayerStateClass = PlayerStateClass;
    }

    if (GameStateClass != nullptr)
    {
        GameStateClass = GameStateClass;
    }

    if (SpectatorClass != nullptr)
    {
        SpectatorClass = SpectatorClass;
    }

    if (CharacterClass != nullptr)
    {
        DefaultPawnClass = CharacterClass;
    }*/
}