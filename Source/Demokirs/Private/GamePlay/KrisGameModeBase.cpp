// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/KrisGameModeBase.h"

#include "UObject/ConstructorHelpers.h"
#include "GameFramework/HUD.h"
#include "GamePlay/KPlayerController.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/SpectatorPawn.h"
#include "GameFramework/Character.h"

AKrisGameModeBase::AKrisGameModeBase()
{
    //// ���Ҳ�����HUD��ͼ��
    //static ConstructorHelpers::FClassFinder<AHUD> BlueprintHUD(TEXT("/Script/Engine.Blueprint'/Game/Kirs/Gameplay/BP_HUD.BP_HUD_C'"));
    //if (BlueprintHUD.Succeeded())
    //{
    //    HUDClass = BlueprintHUD.Class;
    //}

    //// ���Ҳ�����PlayerController��ͼ��
    //static ConstructorHelpers::FClassFinder<AKPlayerController> BlueprintPlayerController(TEXT("/Script/Engine.Blueprint'/Game/Kirs/Gameplay/BP_KPlayerController.BP_KPlayerController_C'"));
    //if (BlueprintPlayerController.Succeeded())
    //{
    //    PlayerControllerClass = BlueprintPlayerController.Class;
    //}

    ///*TSubclassOf<APawn> BlueprintPlayerController;
    //BlueprintPlayerController = StaticLoadClass(APlayerController::StaticClass(), nullptr, TEXT("/Script/Engine.Blueprint'/Game/Kirs/Gameplay/BP_KPlayerController.BP_KPlayerController_C"));
    //if (BlueprintPlayerController)
    //{
    //    PlayerControllerClass = BlueprintPlayerController;
    //}*/

    //// ���Ҳ�����PlayerState��ͼ��
    //static ConstructorHelpers::FClassFinder<APlayerState> BlueprintPlayerState(TEXT("/Game/Blueprints/BP_PlayerState"));
    //if (BlueprintPlayerState.Succeeded())
    //{
    //    PlayerStateClass = BlueprintPlayerState.Class;
    //}

    //// ���Ҳ�����GameState��ͼ��
    //static ConstructorHelpers::FClassFinder<AGameStateBase> BlueprintGameState(TEXT("/Game/Blueprints/BP_GameState"));
    //if (BlueprintGameState.Succeeded())
    //{
    //    GameStateClass = BlueprintGameState.Class;
    //}

    //// ���Ҳ�����Spectator��ͼ��
    //static ConstructorHelpers::FClassFinder<ASpectatorPawn> BlueprintSpectator(TEXT("/Game/Blueprints/BP_SpectatorPawn"));
    //if (BlueprintSpectator.Succeeded())
    //{
    //    SpectatorClass = BlueprintSpectator.Class;
    //}
    HUDClass = AHUD::StaticClass();
    PlayerControllerClass = AKPlayerController::StaticClass();
    PlayerStateClass = APlayerState::StaticClass();
    GameStateClass = AGameStateBase::StaticClass();
    SpectatorClass = ASpectatorPawn::StaticClass();
    // ���Ҳ�����Character��ͼ��
    static ConstructorHelpers::FClassFinder<ACharacter> BlueprintCharacter(TEXT("/Script/Engine.Blueprint'/Game/Kirs/Gameplay/BP_PlayerCharacter.BP_PlayerCharacter_C'"));
    if (BlueprintCharacter.Succeeded())
    {
        DefaultPawnClass = BlueprintCharacter.Class;
    }
}

void AKrisGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    if (HUDClass != nullptr)
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
    }
}