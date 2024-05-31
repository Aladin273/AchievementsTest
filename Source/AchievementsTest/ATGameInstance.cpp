// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGameInstance.h"
#include "ATGameUserSettings.h"

void UATGameInstance::OnStart()
{
    const auto GameUserSettings = UATGameUserSettings::GetATGameUserSettings();

    if (GameUserSettings)
    {
        GameUserSettings->LoadSettings();

        if (GameUserSettings->GetInitLaunch())
        {
            GameUserSettings->SetOverallScalabilityLevel(3);
            GameUserSettings->SetMusicVolume(0.5f);
            GameUserSettings->SetSFXVolume(0.5f);
            GameUserSettings->SetInitLaunch(false);
        }

        GameUserSettings->SetMusicSoundClass(MusicSoundClass);
        GameUserSettings->SetSFXSoundClass(SFXSoundClass);

        GameUserSettings->ApplySettings(true);
    }
}
