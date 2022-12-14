// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class AThrowable;

UCLASS()
class TOWERDEFENSEPROJECT_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*UPROPERTY(VisibleAnywhere) class USpringArmComponent* cameraBoom = nullptr;
	UPROPERTY(VisibleAnywhere) class UCameraComponent* camera = nullptr;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats") float health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats") float maxHealth = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats") float damage = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats") float armor = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats") float maxWalkSpeed = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TSubclassOf<AThrowable> throwableClass;
	
	virtual float TakeDamage(float dmg, struct FDamageEvent const &dmgEvent, AController* Damageinstigator, AActor* causer) override;
	UFUNCTION(BlueprintCallable)	virtual void Attack(AActor* target);

	FTimerHandle slowTimerHandle;
	void ApplyEffectSlow(float factor, float duration);
	void UndoEffectSlow();
};
