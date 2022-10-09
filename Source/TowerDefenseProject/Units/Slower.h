// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/UnitBase.h"
#include "units/shooter.h"
#include "Slower.generated.h"

UCLASS()
class TOWERDEFENSEPROJECT_API ASlower : public AShooter
{
	GENERATED_BODY()

public:
	ASlower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Fire() override;

	
};
