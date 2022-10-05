// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "lib.h"
#include "gameframework/playercontroller.h"
#include "kismet/gameplaystatics.h"
AGameHUD::AGameHUD()
{

}
void AGameHUD::DrawHUD()
{
	Super::DrawHUD();
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!controller) return;
	int32 X, Y;
	controller->GetViewportSize(X,Y);
	float dt = GetWorld()->GetDeltaSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("FPS: %f"), 1.f / dt);
	if ((1.f / dt) < 58.f)
	{
		DrawText(FString("BELOW 60 FPS"), FColor::Red, X - X/7.f, Y/6.f, (UFont*)0, 1.f, true);
	}
}