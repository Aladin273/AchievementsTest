// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameFramework/SaveGame.h"
#include "ATAchievementsSettings.h"
#include "ATAchievementsSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAchievementComplete, const FAchievementData&, Achievement);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAchievementUpdated, const FAchievementData&, Achievement);

UCLASS()
class ACHIEVEMENTSTEST_API UATAchievementsSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(SaveGame)
	TMap<FName, FAchievementData> AchievementsMap;
};

UCLASS()
class ACHIEVEMENTSTEST_API UATAchievementsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	bool AddAchievementProgress(FName Name, int32 Value);

	UFUNCTION(BlueprintCallable)
	bool SetAchievementProgress(FName Name, int32 Value);

	UFUNCTION(BlueprintCallable)
	bool ResetAchievementProgress(FName Name);

	UFUNCTION(BlueprintCallable)
	bool ResetAllToDefaults();

	UFUNCTION(BlueprintCallable)
	const TMap<FName, FAchievementData>& GetAchievementsData() const { return AchievementsMap; };

public:
	UPROPERTY(BlueprintAssignable)
	FOnAchievementComplete OnAchievementComplete;	

	UPROPERTY(BlueprintAssignable)
	FOnAchievementComplete OnAchievementUpdated;	

private:
	TMap<FName, FAchievementData> AchievementsMap;
};
