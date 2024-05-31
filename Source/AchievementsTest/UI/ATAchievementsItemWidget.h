// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Subsystems/ATAchievementsSubsystem.h"
#include "ATAchievementsItemWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class ACHIEVEMENTSTEST_API UATAchievementsItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetAchievementData(const FAchievementData& Achievement);

protected:
	UPROPERTY(meta = (BindWidget))
	UImage* I_Icon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* T_Name;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* T_Progress;
};
