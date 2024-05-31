// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ATGameModeBase.generated.h"

UENUM(BlueprintType)
enum class EATGameModeState : uint8
{
	WaitingForStart = 0,
	InProgress,
	Pause,
	GameOver
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameModeChangedSignature, EATGameModeState, MatchState);

UCLASS()
class ACHIEVEMENTSTEST_API AATGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AATGameModeBase();

	virtual void StartPlay() override;

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;

	virtual bool ClearPause() override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void GameOver();

public:
	UPROPERTY(BlueprintAssignable)
	FOnGameModeChangedSignature OnGameModeStateChanged;

protected:
	void SetMatchState(EATGameModeState State);
	
	EATGameModeState MatchState = EATGameModeState::WaitingForStart;
};
