// Fill out your copyright notice in the Description page of Project Settings.


#include "ATAchievementsSubsystem.h"

#include "Kismet/GameplayStatics.h"

void UATAchievementsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    UATAchievementsSettings* AchievementsSettings = Cast<UATAchievementsSettings>(UATAchievementsSettings::StaticClass()->GetDefaultObject(true));
    
    if (AchievementsSettings)
    {
        if (UGameplayStatics::DoesSaveGameExist(AchievementsSettings->SaveSlotName, 0) && !AchievementsSettings->ResetOnStart)
        {
            auto AchievementsSave = Cast<UATAchievementsSaveGame>(UGameplayStatics::LoadGameFromSlot(AchievementsSettings->SaveSlotName, 0));
            AchievementsMap = AchievementsSave->AchievementsMap;
        }
        else
        {
            for (auto Achievement : AchievementsSettings->AchievementData)
                AchievementsMap.Add({ Achievement.AchievementName, Achievement });
        }
    }
}

void UATAchievementsSubsystem::Deinitialize()
{
    UATAchievementsSettings* AchievementsSettings = Cast<UATAchievementsSettings>(UATAchievementsSettings::StaticClass()->GetDefaultObject(true));

    if (AchievementsSettings)
    {
        auto AchievementsSave = Cast<UATAchievementsSaveGame>(UGameplayStatics::CreateSaveGameObject(UATAchievementsSaveGame::StaticClass()));

        AchievementsSave->AchievementsMap = AchievementsMap;
        UGameplayStatics::SaveGameToSlot(AchievementsSave, AchievementsSettings->SaveSlotName, 0);
    }

    Super::Deinitialize();
}

bool UATAchievementsSubsystem::AddAchievementProgress(FName Name, int32 Value)
{
    if (!AchievementsMap.Contains(Name))
        return false;
    
    return SetAchievementProgress(Name, AchievementsMap[Name].AchievementValue + Value);
}

bool UATAchievementsSubsystem::SetAchievementProgress(FName Name, int32 Value)
{
    if (Value < 0 || !AchievementsMap.Contains(Name))
        return false;

    auto& Achievement = AchievementsMap[Name];

    if (Achievement.AchievementValue == Achievement.AchievementMaxValue)
        return false;

    Achievement.AchievementValue = FMath::Min(Achievement.AchievementMaxValue, Value);
    OnAchievementUpdated.Broadcast(Achievement);

    if (Achievement.AchievementValue == Achievement.AchievementMaxValue)
        OnAchievementComplete.Broadcast(Achievement);

    return true;
}

bool UATAchievementsSubsystem::ResetAchievementProgress(FName Name)
{
    if (!AchievementsMap.Contains(Name))
        return false;

    AchievementsMap[Name].AchievementValue = 0;
    OnAchievementUpdated.Broadcast(AchievementsMap[Name]);

    return true;
}

bool UATAchievementsSubsystem::ResetAllToDefaults()
{
    UATAchievementsSettings* AchievementsSettings = Cast<UATAchievementsSettings>(UATAchievementsSettings::StaticClass()->GetDefaultObject(true));

    if (AchievementsSettings)
    {
        AchievementsMap.Empty();

        for (auto Achievement : AchievementsSettings->AchievementData)
            AchievementsMap.Add({ Achievement.AchievementName, Achievement });

        return true;
    }
    
    return false;
}
