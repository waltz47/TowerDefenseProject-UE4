// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/UnitBase.h"
#include "lib.h"
#include "components/scenecomponent.h"
#include "components/staticmeshcomponent.h"
#include "kismet/gameplaystatics.h"
#include "player/tdplayer.h"
#include "kismet/kismetmathlibrary.h"

// Sets default values
AUnitBase::AUnitBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootScene = CreateDefaultSubobject<USceneComponent>("Root Scene");
	SetRootComponent(rootScene);

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	baseMesh->SetupAttachment(RootComponent);

	m_unitStats.health = m_unitStats.maxHealth;
	m_unitState = UNIT_PLACING;
}

// Called when the game starts or when spawned
void AUnitBase::BeginPlay()
{
	Super::BeginPlay();
	ULib::SetActorTeam(this, true);
	m_tdPlayer = Cast<ATDPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (m_tdPlayer == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("m_tdPlayer null: AUnitBase: %s"), *GetName());
	}
}

// Called every frame
void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_gameTime += DeltaTime;
	if (GetState() == UNIT_NONE)
	{
		return;
	}
	switch (GetState()) {
		case UNIT_PLACING:
		{
			if (ULib::fValid(m_tdPlayer))
			{
				if (!ULib::fValid(m_tdPlayer->m_placingUnit))
				{
					m_tdPlayer->m_placingUnit = this;
				}
			}
			break;
		}
		default: 
			break;
	}
}
void AUnitBase::PlaceUnit()
{
	SetState(UNIT_IDLE);
}
void AUnitBase::DestroyUnit()
{
	ULib::fDestroy(GetWorld(), this);
}

float AUnitBase::TakeDamage(float damage, struct FDamageEvent const& dmge, AController* DamageInstigator, AActor* Causer)
{
	damage = Super::TakeDamage(damage, dmge, DamageInstigator, Causer);
	m_unitStats.health -= damage;
	if (m_unitStats.health <= 0.f)
	{
		DestroyUnit();
	}
	return damage;
}
