// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ATAchievementsSettings.generated.h"

USTRUCT(BlueprintType)
struct FAchievementData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	FName AchievementName = NAME_None;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	FName AchievementDisplayName = NAME_None;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
	TSoftObjectPtr<UTexture2D> AchievementThumbnail;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", meta = (ClampMin = 0))
	int32 AchievementValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Achievements", meta = (ClampMin = 1))
	int32 AchievementMaxValue;
};

UCLASS(Config=Game, defaultconfig, meta = (DisplayName="Achievements"))
class ACHIEVEMENTSTEST_API UATAchievementsSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UATAchievementsSettings() {};

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	FString SaveSlotName = "AchievementsSaveSlot";

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	TArray<FAchievementData> AchievementData;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	bool ResetOnStart = false;
};
