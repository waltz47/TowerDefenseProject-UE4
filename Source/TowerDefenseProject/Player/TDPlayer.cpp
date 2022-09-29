// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TDPlayer.h"
#include "camera/cameracomponent.h"
#include "gameframework/springarmcomponent.h"
#include "units/unitbase.h"
#include "lib.h"
#include "gameframework/playercontroller.h"
#include "kismet/gameplaystatics.h"
#include "drawdebughelpers.h"

#define MIN_DIST_TO_PLAYER 100.f
#define GROUND_RADIUS_TO_BUILD 60.f

// Sets default values
ATDPlayer::ATDPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	if(GetMesh()) SpringArm->SetupAttachment(GetMesh());
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	health = maxHealth;

}

// Called when the game starts or when spawned
void ATDPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATDPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ULib::fValid(m_placingUnit) == false)
	{
		return;
	}
	if (GetWorld() == nullptr)
	{
		return;
	}
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playerController == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("null controller"));
		m_placeable = 0;
		return;
	}
	//playerController->SetShowMouseCursor(true);
	FVector worldLoc, worldDir;
	playerController->DeprojectMousePositionToWorld(worldLoc, worldDir);
	FVector eyeLocation;
	FRotator eyeRotation;
	playerController->GetActorEyesViewPoint(eyeLocation, eyeRotation);
	FVector endLoc = worldLoc + worldDir * unitPlacementRange;
	FHitResult hit;
	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(hit,
		eyeLocation,
		endLoc,
		ECollisionChannel::ECC_WorldStatic,
		queryParams
	);
	
	if (!hit.bBlockingHit)
	{
		//UE_LOG(LogTemp, Warning, TEXT("No placeable location"));
		m_placeable = 0;
		DrawDebugLine(GetWorld(), eyeLocation, endLoc, FColor::Red);
		return;
	}
	DrawDebugLine(GetWorld(), eyeLocation, endLoc, FColor::Green);
	FVector location = hit.Location;
	float distToPlayer = (GetActorLocation() - location).Size();
	if (distToPlayer < MIN_DIST_TO_PLAYER)
	{
		m_placeable = 0;
		return;
	}
	if (ULib::GroundSlopeCheck(this, location, GROUND_RADIUS_TO_BUILD, 40.f))
	{
		m_placingUnit->SetActorLocation(location);
		m_placeable = 1;
	}

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *(hit.GetActor()->GetName()));
}

// Called to bind functionality to input
void ATDPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATDPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATDPlayer::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ATDPlayer::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &ATDPlayer::LookRight);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("LeftMouse", EInputEvent::IE_Pressed, this, &ATDPlayer::LeftMouseEval);
	PlayerInputComponent->BindAction("RightMouse", EInputEvent::IE_Pressed, this, &ATDPlayer::RightMouseEval);

}
void ATDPlayer::MoveForward(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, value);
}
void ATDPlayer::MoveRight(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, value);

}
void ATDPlayer::LookRight(float value)
{
	AddControllerYawInput(value);
}
void ATDPlayer::LookUp(float value)
{
	AddControllerPitchInput(value);
}
void ATDPlayer::LeftMouseEval()
{
	if (ULib::fValid(m_placingUnit))
	{
		if (m_placeable) {
			m_placingUnit->PlaceUnit();
			m_placingUnit = nullptr;
			return;
		}
		else {
			ULib::fDestroy(GetWorld(), m_placingUnit);
			return;
		}

	}
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Blue, FString("Light Attack"));
	}
}
void ATDPlayer::RightMouseEval()
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Red, FString("Heavy Attack"));
	}
}

float ATDPlayer::TakeDamage(float damage, FDamageEvent const & dmgEvent, AController * DamageInstigator, AActor * causer)
{
	damage = Super::TakeDamage(damage, dmgEvent, DamageInstigator, causer);
	health -= damage;
	if (health <= 0.f)
	{
		//detach controller and death animations
		FTimerHandle timerHandleDeath;
		GetWorld()->GetTimerManager().SetTimer(timerHandleDeath, this, &ATDPlayer::Respawn, respawnTime, false);
	}
	return damage;
}
void ATDPlayer::Respawn()
{
	health = maxHealth;
	//set respawn location 
}