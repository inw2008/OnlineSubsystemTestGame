// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TargetPoint.h"
#include "BoxMoveActor.generated.h"

UCLASS()
class OSTESTING_API ABoxMoveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ABoxMoveActor();
    virtual void Tick(float DeltaTime) override;
    
    UPROPERTY(EditAnywhere)
    TArray<ATargetPoint*> Points;
    
    UPROPERTY(EditAnywhere)
    float MovingVelocity;
    
    UPROPERTY(EditAnywhere)
    float StoppedDistance;

protected:

    
	virtual void BeginPlay() override;

private:
    
    void MoveBox(float DeltaSeconds);
    
    UPROPERTY()
    int CurrentMovingPoint;
};
