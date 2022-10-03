// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/Shooter.h"
#include "lib.h"
#include "drawdebughelpers.h"

#define TURRET_ROTATION_SPEED 0.2f
#define TURRET_LOOK_AT_TOLERANCE 15.f

AShooter::AShooter()
{
	PrimaryActorTick.bCanEverTick = true;

	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>("Turret Mesh");
	turretMesh->SetupAttachment(baseMesh);
}

void AShooter::BeginPlay()
{
	Super::BeginPlay();

}
void AShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetState() == UNIT_NONE || GetState() == UNIT_PLACING)
	{
		return;
	}
	
	switch (GetState())
	{
		case UNIT_NONE:
			break;
		case UNIT_IDLE:
		{
			SetTarget(FindNewTarget());
			SetState(UNIT_AIMING);
			break;
		}
		case UNIT_AIMING:
		{
			if (!ULib::fValid(GetTarget()))
			{
				SetState(UNIT_IDLE);
				break;
			}
			FRotator currTurretRot = turretMesh->GetComponentRotation();
			FRotator lookAtTarget = (GetTarget()->GetActorLocation() - turretMesh->GetComponentLocation()).Rotation();
			FRotator lerpedRot = FMath::Lerp(turretMesh->GetComponentRotation(), lookAtTarget, TURRET_ROTATION_SPEED);
			turretMesh->SetWorldRotation(lerpedRot);
			if (turretMesh->GetComponentRotation().Equals(lookAtTarget, TURRET_LOOK_AT_TOLERANCE))
			{
				SetState(UNIT_ATTACKING);
			}
			//Rotate Turret
			break;
		}
		case UNIT_ATTACKING:
		{
			
			if (m_gameTime - m_lastAttackTime >= m_unitStats.attackRate)
			{
				Fire();
			}
			SetState(UNIT_AIMING);
			break;
		}
		default:
			break;
	}
}
bool AShooter::ValidTarget(AActor* actor)
{
	if (!ULib::fValid(actor)) return false;
	float distToTarget = (GetActorLocation() - actor->GetActorLocation()).Size();
	return distToTarget <= m_unitStats.attackRange;
}
AActor* AShooter::FindNewTarget()
{
	TArray<AActor*> prospect = ULib::GetNearbyActors(GetWorld(), GetActorLocation(), m_unitStats.attackRange, ULib::IsPlayerTeam(this));
	float currentFarthest = 2e9;
	AActor* prospectActor = nullptr;	
	for (AActor* actor : prospect)
	{
		if (!ULib::fValid(actor))
		{
			continue;
		}
		float distToTarget = (GetActorLocation() - actor->GetActorLocation()).Size();
		if (distToTarget < currentFarthest)
		{
			currentFarthest = distToTarget;
			prospectActor = actor;
		}
	}
	return prospectActor;
}
void AShooter::Fire()
{
	if (!ULib::fValid(GetTarget()))
	{
		SetState(UNIT_IDLE);
		UE_LOG(LogTemp, Warning, TEXT("Invalid target in single frame"));
		return;
	}
	DrawDebugLine(GetWorld(),
		GetActorLocation(),
		GetTarget()->GetActorLocation(),
		FColor::Red,
		false,
		0.2f
	);
	m_lastAttackTime = m_gameTime;
}