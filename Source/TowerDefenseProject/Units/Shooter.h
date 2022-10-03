// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/UnitBase.h"
#include "Shooter.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSEPROJECT_API AShooter : public AUnitBase
{
	GENERATED_BODY()

public:
	AShooter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere) class UStaticMeshComponent* turretMesh = nullptr;

	UPROPERTY() AActor* targetActor = nullptr;
	float m_lastAttackTime = -100.f;

	AActor* GetTarget() { return targetActor; }
	void SetTarget(AActor* newTarget) { targetActor = newTarget; }
	bool ValidTarget(AActor* actor);
	AActor* FindNewTarget();
	virtual void Fire();
};
