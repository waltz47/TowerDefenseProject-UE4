// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnitBase.generated.h"

USTRUCT(BlueprintType)
struct FUnitStats
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float health = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float maxHealth = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float damage = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float attackRate = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float attackRange = 1500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float slowFactor = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float slowDuration = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float gold = 10.f;

};

UENUM()
enum UnitState
{
	UNIT_NONE,
	UNIT_IDLE,
	UNIT_PLACING,
	UNIT_AIMING,
	UNIT_ATTACKING
};

UCLASS()
class TOWERDEFENSEPROJECT_API AUnitBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnitBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere) class USceneComponent* rootScene = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) class USkeletalMeshComponent* baseMesh = nullptr;

	UPROPERTY() class  ATDPlayer* m_tdPlayer = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FUnitStats m_unitStats;
	UnitState m_unitState = UNIT_IDLE;
	float m_gameTime = 0.f;

	virtual float TakeDamage(float dmg, struct FDamageEvent const &dmgEvent, AController* Damageinstigator, AActor* causer) override;
	virtual void DestroyUnit();
	UnitState GetState() { return m_unitState;  }
	void SetState(UnitState eState) { m_unitState = eState; }
	virtual void PlaceUnit();

};
