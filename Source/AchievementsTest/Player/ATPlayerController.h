// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ATPlayerController.generated.h"

class UATAchievementsTableWidget;
enum class EATGameModeState : uint8;

/**
 * 
 */
UCLASS()
class ACHIEVEMENTSTEST_API AATPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AATPlayerController();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> AchievementsTableWidgetCass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> AchievementsPopupWidgetCass;

protected:
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

protected:
	UFUNCTION()
	virtual void OnGameModeStateChanged(EATGameModeState State);

	UFUNCTION()
	virtual void OnAchievementComplete(const FAchievementData& Achievement);

	UFUNCTION()
	virtual void OnAchievementUpdated(const FAchievementData& Achievement);

private:
	UFUNCTION()
	void OnPauseGame();
	
	UFUNCTION()
	void OnAchievementsTable();
	
	UFUNCTION()
	void OnAchievementsReset();

	UPROPERTY()
	UATAchievementsTableWidget* AchievementsTableWidget;
};
