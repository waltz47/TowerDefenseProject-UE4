// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSEPROJECT_API AGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	AGameHUD();
protected:
	virtual void DrawHUD() override;
};
