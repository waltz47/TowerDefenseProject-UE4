// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/Slower.h"
#include "lib.h"
#include "gameframework/character.h"
#include "gameframework/charactermovementcomponent.h"
#include "enemy/enemy.h"

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
void ASlower::Fire()
{
	Super::Fire();
	if (!ULib::fValid(GetTarget())) return;
	AEnemy* character = Cast<AEnemy>(GetTarget());
	if (!ULib::fValid(character)) return;
	if (m_unitStats.slowFactor > 0.f)
	{
		character->ApplyEffectSlow(m_unitStats.slowFactor, m_unitStats.slowDuration);
	}
}