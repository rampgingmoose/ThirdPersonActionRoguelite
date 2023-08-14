// Fill out your copyright notice in the Description page of Project Settings.


#include "DBPowerUp.h"
#include "Components/SphereComponent.h"


// Sets default values
ADBPowerUp::ADBPowerUp()
{
 	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Powerup");
	RootComponent = SphereComp;

	RespawnTime = 10.0f;
}

void ADBPowerUp::Interact_Implementation(APawn* InstigatorPawn)
{
	//logic in derived classes
}

void ADBPowerUp::ShowPowerup()
{
	SetPowerupState(true);
}

void ADBPowerUp::HideAndCooldownPowerup()
{
	SetPowerupState(false);
	
	GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &ADBPowerUp::ShowPowerup, RespawnTime);
}

void ADBPowerUp::SetPowerupState(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);

	//Set visibility on root and all children
	RootComponent->SetVisibility(bNewIsActive, true);
}



