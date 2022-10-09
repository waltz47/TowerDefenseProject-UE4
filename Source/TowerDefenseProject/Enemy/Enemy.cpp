// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"
#include "gameframework/springarmcomponent.h"
#include "camera/cameracomponent.h"
#include "lib.h"
#include "navigationsystem.h"
#include "aicontroller.h"
#include "AI/NavigationSystemBase.h"
#include "navigationpath.h"
#include "engine/world.h"
#include "gameframework/charactermovementcomponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	cameraBoom->SetupAttachment(GetMesh());

	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	camera->SetupAttachment(cameraBoom);

	health = maxHealth;

	if (GetCharacterMovement()) GetCharacterMovement()->MaxWalkSpeed = maxWalkSpeed;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	ULib::SetActorTeam(this, false);
	//FTimerHandle sth;
	//GetWorld()->GetTimerManager().SetTimer(sth, this, &AEnemy::Search, 2.f, true, 1.f);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);}

void AEnemy::Search()
{
	//INV
	if (ULib::fValid(target)) return;
	UNavigationSystemV1* NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	if (NavArea == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Null NavArea"));
		return;
	}
	TArray<AActor*> p = ULib::GetNearbyActors(GetWorld(), GetActorLocation(), 1000.f, 1);
	for (AActor* actor : p)
	{
		if (!ULib::fValid(actor))
		{
			continue;
		}
		UNavigationPath* path = NavArea->FindPathToLocationSynchronously(this, GetActorLocation(), actor->GetActorLocation(),
			actor);
		float maxCost = 2e9;
		if (path && path->IsValid())
		{
			float cost = path->GetPathLength();
			if (cost < maxCost)
			{
				maxCost = cost;
				target = actor;
			}
		}
	}
	if (ULib::fValid(target))
	{
		RF_Blueprint();
	}
}
float AEnemy::TakeDamage(float dmg, struct FDamageEvent const &dmgEvent, AController* Damageinstigator, AActor* causer)
{
	dmg = Super::TakeDamage(dmg, dmgEvent, Damageinstigator, causer);
	health -= (dmg / (dmg + armor + 1));
	if (health <= 0.f)
	{
		ULib::fDestroy(GetWorld(), this);
	}
	return dmg;
}
void AEnemy::ApplyEffectSlow(float factor, float duration)
{
	if (GetWorld()->GetTimerManager().IsTimerActive(slowTimerHandle) == false)
	{
		GetCharacterMovement()->MaxWalkSpeed /= factor;
	}
	GetWorld()->GetTimerManager().SetTimer(slowTimerHandle, this, &AEnemy::UndoEffectSlow, duration, false);
}
void AEnemy::UndoEffectSlow()
{
	GetCharacterMovement()->MaxWalkSpeed = maxWalkSpeed;
}