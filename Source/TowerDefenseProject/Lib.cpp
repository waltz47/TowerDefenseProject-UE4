// Fill out your copyright notice in the Description page of Project Settings.


#include "Lib.h"
#include "engine/world.h"
#include "containers/array.h"
#include "kismet/gameplaystatics.h"
#include "kismet/kismetmathlibrary.h"
#include "engine/world.h"

#define AI_TEAM "t_ai"
#define PLAYER_TEAM "t_player"

bool ULib::fValid(const UObject* actor)
{
	if (!actor) {
		return false;
	}
	if (!actor->IsValidLowLevel())
	{
		return false;
	}
	if (actor->IsPendingKill())
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
void ULib::SetActorTeam(AActor* actor, bool playerTeam)
{
	if (!fValid(actor))
	{
		return;
	}
	if (playerTeam)
	{
		actor->Tags.Add(PLAYER_TEAM);
		actor->Tags.Remove(AI_TEAM);
	}
	else
	{
		actor->Tags.Remove(PLAYER_TEAM);
		actor->Tags.Add(AI_TEAM);
	}
}
TArray<AActor*> ULib::GetNearbyActors(UWorld* world, const FVector& origin, float radius, bool playerTeam)
{
	if (world == nullptr)
	{
		return {};
	}
	TArray<AActor*> ret;
	UGameplayStatics::GetAllActorsWithTag(world, playerTeam ? PLAYER_TEAM : AI_TEAM, ret);
	TArray<AActor*> gv;
	for (AActor* actor : ret)
	{
		if (!fValid(actor)) continue;
		float dst = (actor->GetActorLocation() - origin).Size();
		if (dst <= radius)
		{
			gv.Add(actor);
		}
	}
	return gv; 
}
bool ULib::IsPlayerTeam(AActor* actor)
{
	if (!fValid(actor)) return false;
	return actor->ActorHasTag(PLAYER_TEAM);
}