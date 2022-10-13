// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "EnemyRanged.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSEPROJECT_API AEnemyRanged : public AEnemy
{
	GENERATED_BODY()

public:
	AEnemyRanged();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Attack(AActor* target) override;
};
