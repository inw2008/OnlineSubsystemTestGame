// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OSGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class OSTESTING_API UOSGameInstance : public UGameInstance
{
	GENERATED_BODY()
    

public:
    virtual void Init();
	
    UFUNCTION(BlueprintCallable)
    void Host();
       
    UFUNCTION(BlueprintCallable)
    void Join(FString IP);
    
    void OnStartingHost(FName SessionName, bool Success);
    void OnDestroySession(FName SessionName, bool Success);
    
private:
    void CreateSession();
    
    IOnlineSessionPtr SessionInterface;
    
    
};
