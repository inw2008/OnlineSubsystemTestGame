// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxMoveActor.h"


ABoxMoveActor::ABoxMoveActor()
{
    PrimaryActorTick.bCanEverTick = true;
    StoppedDistance = 3.0f;
}

void ABoxMoveActor::BeginPlay()
{
    Super::BeginPlay();
    
    if (HasAuthority())
    {
        SetReplicates(true);
        SetReplicateMovement(true);
    }
}


void ABoxMoveActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if (HasAuthority())
    {
        MoveBox(DeltaTime);
    }
}

void ABoxMoveActor::MoveBox(float DeltaSeconds)
{
    if (Points.Num() > 0 && Points.IsValidIndex(CurrentMovingPoint))
    {
        FVector GetCurrentLocation = GetActorLocation();
        FVector NextCurrentLocation = Points[CurrentMovingPoint]->GetActorLocation();
        FVector Direction = (NextCurrentLocation - GetCurrentLocation).GetSafeNormal();
        
        float Distance = FVector::Distance(GetCurrentLocation, NextCurrentLocation);

        if (Distance > StoppedDistance)
        {
            FVector VectorVelocity = Direction  * DeltaSeconds * MovingVelocity;
            FVector NewPosition = VectorVelocity + GetCurrentLocation;
            SetActorLocation(NewPosition);
        }
        else
        {
            CurrentMovingPoint += 1;
            
            if (CurrentMovingPoint == Points.Num())
            {
                CurrentMovingPoint = 0;
            }
        }
    }
}
