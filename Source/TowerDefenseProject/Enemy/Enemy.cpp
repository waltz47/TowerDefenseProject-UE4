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
#include "kismet/gameplaystatics.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*cameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	cameraBoom->SetupAttachment(GetMesh());

	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	camera->SetupAttachment(cameraBoom);*/

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
void AEnemy::Attack(AActor* target)
{
	if (!ULib::fValid(target))
		return;
	UGameplayStatics::ApplyDamage(target, damage, nullptr, nullptr, UDamageType::StaticClass());
}