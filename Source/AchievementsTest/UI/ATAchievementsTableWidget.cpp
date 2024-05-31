// Fill out your copyright notice in the Description page of Project Settings.

#include "ATAchievementsTableWidget.h"

#include "Components/VerticalBox.h"
#include "ATAchievementsItemWidget.h"
#include "../Subsystems/ATAchievementsSubsystem.h"

void UATAchievementsTableWidget::Refresh()
{
    if (GetWorld() && VB_ItemBox)
    {
        VB_ItemBox->ClearChildren();

        const auto Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UATAchievementsSubsystem>();

        if (Subsystem)
        {
            for (auto& [Name, Data] : Subsystem->GetAchievementsData())
            {
                const auto AchievementsItemWidget = CreateWidget<UATAchievementsItemWidget>(GetWorld(), AchievementsItemWidgetClass);
                if (!AchievementsItemWidget) continue;
            
                AchievementsItemWidget->SetAchievementData(Data);
            
                VB_ItemBox->AddChild(AchievementsItemWidget);
            }
        }
    }
}

void UATAchievementsTableWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    Refresh();
}
