// Fill out your copyright notice in the Description page of Project Settings.


#include "OSGameInstance.h"
#include "OnlineSubsystem.h"


const static FName ServerSession = TEXT("Maluma Game");

void UOSGameInstance::Init()
{
    IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get();
    if (SubSystem)
    {
        UE_LOG(LogTemp, Warning, TEXT("->>>> Sub sytems choose (%s)"), *SubSystem->GetSubsystemName().ToString());
        SessionInterface = SubSystem->GetSessionInterface();
        if (SessionInterface.IsValid())
        {
            SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UOSGameInstance::OnStartingHost);
            SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UOSGameInstance::OnDestroySession);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Not found Online found "));
    }
}


void UOSGameInstance::Host()
{
    if (SessionInterface.IsValid())
    {
        FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(ServerSession);
        
        if (ExistingSession)
        {
            SessionInterface->DestroySession(ServerSession);
        }
        
        else
        {
            CreateSession();
        }
    }
}


void UOSGameInstance::Join(FString IP)
{
    FString Message = FString::Printf( TEXT( ">>>IP %s" ), *IP );
    GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, Message);
    
    if (APlayerController *PlayerController = GetFirstLocalPlayerController())
    {
        PlayerController->ClientTravel(IP, ETravelType::TRAVEL_Absolute);
    }
}


void UOSGameInstance::CreateSession()
{
    if (SessionInterface.IsValid())
    {
        FOnlineSessionSettings OnlineSessionSettings;
        SessionInterface->CreateSession(0, ServerSession, OnlineSessionSettings);
    }
}

void UOSGameInstance::OnStartingHost(FName SessionName, bool Success)
{
    if (Success)
    {
        GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, TEXT(">>Server Side"));
        
        if (UWorld *World = GetWorld())
        {
            //TODO: Change to tsubclass
            World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
        }
    }
}


void UOSGameInstance::OnDestroySession(FName SessionName, bool Success)
{
    if (Success)
    {
        CreateSession();
    }
}
