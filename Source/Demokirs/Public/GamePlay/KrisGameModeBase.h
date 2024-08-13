// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KrisGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DEMOKIRS_API AKrisGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
    AKrisGameModeBase();

protected:
    virtual void BeginPlay() override;

private:
    TSubclassOf<class AHUD> HUDClass;
    TSubclassOf<class APlayerController> PlayerControllerClass;
    TSubclassOf<class APlayerState> PlayerStateClass;
    TSubclassOf<class AGameStateBase> GameStateClass;
    TSubclassOf<class ASpectatorPawn> SpectatorClass;
    TSubclassOf<class ACharacter> CharacterClass;
};
