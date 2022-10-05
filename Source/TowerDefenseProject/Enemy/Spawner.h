// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class TOWERDEFENSEPROJECT_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) TSubclassOf<AActor> type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float spawnRate = 5.f;
	FTimerHandle spawnTh;
	void Spawn();
	UFUNCTION(BlueprintCallable)
	void StartTimer()
	{
		GetWorld()->GetTimerManager().SetTimer(spawnTh, this, &ASpawner::Spawn, spawnRate, true, 1.f);
	}
	UFUNCTION(BlueprintCallable)
	void StopTimer()
	{
		GetWorld()->GetTimerManager().ClearTimer(spawnTh);
	}

};
