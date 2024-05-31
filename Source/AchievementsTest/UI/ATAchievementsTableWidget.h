// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ATAchievementsTableWidget.generated.h"

class UVerticalBox;

UCLASS()
class ACHIEVEMENTSTEST_API UATAchievementsTableWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Refresh();

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VB_ItemBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> AchievementsItemWidgetClass;

protected:
	virtual void NativeOnInitialized() override;
};
