// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Throwable.generated.h"

UCLASS()
class TOWERDEFENSEPROJECT_API AThrowable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThrowable();

private:
	UPROPERTY() AActor* target = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bActive = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) class USceneComponent* rootScene;
	UFUNCTION() void SetHoming(AActor* actor) { target = actor;  }
	UFUNCTION() void SetActive() { bActive = 1; }

};
