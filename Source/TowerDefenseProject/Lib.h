// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Lib.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSEPROJECT_API ULib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static bool fValid(AActor* actor);
	static void fDestroy(const UObject* WorldContextObject, AActor* actor);
	static bool GroundSlopeCheck(const UObject* WorldContextObject, const FVector& location, int radius = 100.f, float tolerance = 50.f);
	UFUNCTION(BlueprintCallable) static void SetActorTeam(AActor* actor, bool player);
	static TArray<AActor*> GetNearbyActors(UWorld* world, const FVector& origin, float radius, bool playerTeam);
	static bool IsPlayerTeam(AActor* actor);
};
