// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyRanged.h"
#include "lib.h"
#include "enemy/throwable.h"

AEnemyRanged::AEnemyRanged()
{

}
void AEnemyRanged::BeginPlay()
{
	Super::BeginPlay();

}
void AEnemyRanged::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AEnemyRanged::Attack(AActor* target)
{
	if (!ULib::fValid(target) || !throwableClass)
		return;
	GetWorld()->SpawnActor<AActor>(throwableClass, GetActorLocation(), GetActorRotation());
}