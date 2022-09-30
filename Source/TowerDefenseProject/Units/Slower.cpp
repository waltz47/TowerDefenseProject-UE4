// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/Slower.h"

ASlower::ASlower()
{
	PrimaryActorTick.bCanEverTick = true;

	m_unitStats.health = m_unitStats.maxHealth = 200.f;
}
void ASlower::BeginPlay()
{
	Super::BeginPlay();

}
void ASlower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}