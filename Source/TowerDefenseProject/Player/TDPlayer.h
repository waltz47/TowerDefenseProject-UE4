// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDPlayer.generated.h"

UCLASS()
class TOWERDEFENSEPROJECT_API ATDPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATDPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleAnywhere) class USpringArmComponent* SpringArm = nullptr;
	UPROPERTY(VisibleAnywhere) class UCameraComponent* Camera = nullptr;

	UPROPERTY(EditAnywhere, Category = "Player Stats") float health = 0.f;
	UPROPERTY(EditAnywhere, Category = "Player Stats") float maxHealth = 100.f;
	UPROPERTY(EditAnywhere, Category = "Player Stats") int32 gold = 10;
	UPROPERTY(EditAnywhere, Category = "Game Properties") float respawnTime = 3.f;
	UPROPERTY(EditAnywhere, Category = "Game Properties") float unitPlacementRange = 4000.f;


	UPROPERTY() class AUnitBase* m_placingUnit = nullptr;
	bool m_placeable = 0;

	void LookUp(float value);
	void LookRight(float value);
	void MoveForward(float value);
	void MoveRight(float value);
	void LeftMouseEval();
	void RightMouseEval();
	virtual float TakeDamage(float dmg, struct FDamageEvent const &dmgEvent, AController* Damageinstigator, AActor* causer) override;
	void Respawn();
};
