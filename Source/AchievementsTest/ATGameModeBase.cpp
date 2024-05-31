// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGameModeBase.h"
#include "Player/ATPaperCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameModeBase, All, All)

AATGameModeBase::AATGameModeBase()
{
    DefaultPawnClass = AATPaperCharacter::StaticClass();
}

void AATGameModeBase::StartPlay()
{
    Super::StartPlay();

    SetMatchState(EATGameModeState::InProgress);
}

void AATGameModeBase::GameOver()
{
    SetMatchState(EATGameModeState::GameOver);
}

bool AATGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate /*= FCanUnpause()*/)
{
    bool bPauseSet = Super::SetPause(PC, CanUnpauseDelegate);

    if (bPauseSet)
        SetMatchState(EATGameModeState::Pause);

    return bPauseSet;
}

bool AATGameModeBase::ClearPause()
{
    bool bPauseCleared = Super::ClearPause();

    if (bPauseCleared)
        SetMatchState(EATGameModeState::InProgress);

    return bPauseCleared;
}

void AATGameModeBase::SetMatchState(EATGameModeState State)
{
    if (MatchState != State)
    {
        MatchState = State;
        OnGameModeStateChanged.Broadcast(MatchState);
    }
}