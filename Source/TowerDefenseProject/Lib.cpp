// Fill out your copyright notice in the Description page of Project Settings.


#include "Lib.h"
#include "engine/world.h"
#include "containers/array.h"

bool ULib::fValid(AActor* actor)
{
	if (actor == nullptr) {
		return false;
	}
	if (!actor->IsValidLowLevel())
	{
		return false;
	}
	return true;
}
void ULib::fDestroy(const UObject* WorldContextObject, AActor* actor)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (World == nullptr) return;
	if (fValid(actor) == false)
	{
		return;
	}
	actor->K2_DestroyActor();
	GEngine->ForceGarbageCollection();
	//World->ForceGarbageCollection(true);
}
bool ULib::GroundSlopeCheck(const UObject* WorldContextObject, const FVector& location, int radius, float tolerance)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (World == nullptr) return false;
	TArray<FVector> checkPoints;
	int32 dx[] = { 1, 1, 1, 0, 0, 0, -1, -1, -1 };
	int32 dy[] = { 0, 1, -1, 0, 1, -1, 0, -1, 1 };
	for (int32 x = 0; x < 8; x++) {
		int X = location.X + dx[x] * radius;
		int Y = location.Y + dy[x] * radius;
		FVector chk = location;
		chk.X = X;
		chk.Y = Y;
		chk.Z -= tolerance;
		checkPoints.Add(chk);
	}
	TArray<float> groundPoints;
	for (FVector f : checkPoints) {
		FVector from = f;
		from.Z += 2 * tolerance;
		FHitResult hit;
		World->LineTraceSingleByChannel(
			hit,
			from,
			f,
			ECollisionChannel::ECC_WorldStatic

		);
		if (!hit.bBlockingHit) return false;
		groundPoints.Add(hit.Location.Z);
	}
	for (float x : groundPoints) {
		for (float y : groundPoints) {
			if (abs(x - y) > tolerance) {
				return false;
			}
		}
	}
	return true;
}