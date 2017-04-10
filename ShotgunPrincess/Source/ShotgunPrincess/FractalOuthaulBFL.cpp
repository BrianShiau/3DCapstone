// Fill out your copyright notice in the Description page of Project Settings.

#include "ShotgunPrincess.h"
#include "FractalOuthaulBFL.h"
#include "Kismet/KismetMathLibrary.h"

FRotator UFractalOuthaulBFL::RotationToHit(AActor* firer, AActor* target, float bulletVelocity)
{
    // firer's location
    FVector Q = firer->GetActorLocation();
    // target's location
    FVector P = target->GetActorLocation();
    // target's velocity
    FVector Vel = target->GetVelocity();

    float t1 = 0.0f;
    float t2 = 0.0f;
    float t = 0.0f;

    float a = FVector::DotProduct(Vel, Vel) - bulletVelocity * bulletVelocity;
    float b = 2.0f * FVector::DotProduct(Q - P, Vel);
    float c = (Q - P).SizeSquared();

    float sqrt = UKismetMathLibrary::Sqrt(b * b - 4 * a * c);

    if (a == 0.0f)
    {
        t = 0.0f;
    }
    else
    {
        t1 = (b + sqrt) / (2.0f * a);
        t2 = (b - sqrt) / (2.0f * a);

        t = (t1 > t2 && t2 > 0.0f) ? t2 : t1;
    }

    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Velocity %f %f Time %f"), Vel[0], Vel[1], t));

    return UKismetMathLibrary::FindLookAtRotation(Q, P - t * Vel);
}

FRotator UFractalOuthaulBFL::RotationToHitFromVector(FVector fireLocation, FVector targetLocation, FVector targetVelocity, float bulletVelocity)
{
    FVector Q = fireLocation;
    FVector P = targetLocation;
    FVector Vel = targetVelocity;

    float t1 = 0.0f;
    float t2 = 0.0f;
    float t = 0.0f;

    float a = FVector::DotProduct(Vel, Vel) - bulletVelocity * bulletVelocity;
    float b = 2.0f * FVector::DotProduct(Q - P, Vel);
    float c = (Q - P).SizeSquared();

    float sqrt = UKismetMathLibrary::Sqrt(b * b - 4 * a * c);

    if (a == 0.0f)
    {
        t = 0.0f;
    }
    else
    {
        t1 = (b + sqrt) / (2.0f * a);
        t2 = (b - sqrt) / (2.0f * a);

        t = (t1 > t2 && t2 > 0.0f) ? t2 : t1;
    }

    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Velocity %f %f Time %f"), Vel[0], Vel[1], t));

    return UKismetMathLibrary::FindLookAtRotation(Q, P - t * Vel);
}

bool UFractalOuthaulBFL::IsBetween(float input, float min, float max)
{
    return input >= min && input <= max;
}

bool UFractalOuthaulBFL::IsBetweenInt(int input, int min, int max)
{
    return input >= min && input <= max;
}
