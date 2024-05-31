// Fill out your copyright notice in the Description page of Project Settings.

#include "ATAchievementsItemWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"

void UATAchievementsItemWidget::SetAchievementData(const FAchievementData& Achievement)
{
    if (!I_Icon) return;
    I_Icon->SetBrushFromTexture(Achievement.AchievementThumbnail.LoadSynchronous());

    if (!T_Name) return;
    T_Name->SetText(FText::FromName(Achievement.AchievementDisplayName));

    if (!T_Progress) return;
    T_Progress->SetText(FText::FromString(FString::Printf(TEXT("%i / %i"), Achievement.AchievementValue, Achievement.AchievementMaxValue)));
}
