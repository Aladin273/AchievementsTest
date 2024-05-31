// Fill out your copyright notice in the Description page of Project Settings.


#include "ATPlayerController.h"


#include "../ATGameModeBase.h"
#include "../UI/ATAchievementsTableWidget.h"
#include "../UI/ATAchievementsItemWidget.h"

#include "../Subsystems/ATAchievementsSubsystem.h"

AATPlayerController::AATPlayerController()
{

}

void AATPlayerController::BeginPlay()
{
    if (GetWorld())
    {
        AchievementsTableWidget = CreateWidget<UATAchievementsTableWidget>(GetWorld(), AchievementsTableWidgetCass);

        if (AchievementsTableWidget)
        {
            AchievementsTableWidget->AddToViewport();
            AchievementsTableWidget->SetVisibility(ESlateVisibility::Hidden);
        }

        const auto GameMode = Cast<AATGameModeBase>(GetWorld()->GetAuthGameMode());
        const auto Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UATAchievementsSubsystem>();

        if (GameMode)
            GameMode->OnGameModeStateChanged.AddDynamic(this, &AATPlayerController::OnGameModeStateChanged);

        if (Subsystem)
        {
            Subsystem->OnAchievementComplete.AddDynamic(this, &AATPlayerController::OnAchievementComplete);
            Subsystem->OnAchievementUpdated.AddDynamic(this, &AATPlayerController::OnAchievementUpdated);
        }
    }
}

void AATPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (InputComponent)
    {
        InputComponent->BindAction("PauseGame", IE_Pressed, this, &AATPlayerController::OnPauseGame);
        InputComponent->BindAction("AchievementsTable", IE_Pressed, this, &AATPlayerController::OnAchievementsTable);
        InputComponent->BindAction("AchievementsReset", IE_Pressed, this, &AATPlayerController::OnAchievementsReset);
    }
}

void AATPlayerController::OnGameModeStateChanged(EATGameModeState State)
{
    if (State == EATGameModeState::InProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}

void AATPlayerController::OnAchievementComplete(const FAchievementData& Achievement)
{
    const auto AchievementsPopupWidget = CreateWidget<UATAchievementsItemWidget>(GetWorld(), AchievementsPopupWidgetCass);

    if (AchievementsPopupWidget)
    {
        AchievementsPopupWidget->AddToViewport();
        AchievementsPopupWidget->SetAchievementData(Achievement);
    }
}

void AATPlayerController::OnAchievementUpdated(const FAchievementData& Achievement)
{
    if (AchievementsTableWidget)
    {
        AchievementsTableWidget->Refresh();
    }
}

void AATPlayerController::OnPauseGame()
{
    if (GetWorld() && GetWorld()->GetAuthGameMode())
    {
        GetWorld()->GetAuthGameMode()->SetPause(this);
    }
}

void AATPlayerController::OnAchievementsTable()
{
    if (AchievementsTableWidget)
    {
        if (AchievementsTableWidget->GetVisibility() == ESlateVisibility::Hidden)
        {
            AchievementsTableWidget->Refresh();
            AchievementsTableWidget->SetVisibility(ESlateVisibility::Visible);
            
            SetInputMode(FInputModeGameAndUI());
            bShowMouseCursor = true;
        }
        else
        {
            AchievementsTableWidget->SetVisibility(ESlateVisibility::Hidden);

            SetInputMode(FInputModeGameOnly());
            bShowMouseCursor = false;
        }
    }
}

void AATPlayerController::OnAchievementsReset()
{
    const auto Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UATAchievementsSubsystem>();

    if (Subsystem)
    {
        Subsystem->ResetAllToDefaults();
    }

    if (AchievementsTableWidget)
    {
        AchievementsTableWidget->Refresh();
    }
}
