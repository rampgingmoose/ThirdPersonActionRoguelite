// Fill out your copyright notice in the Description page of Project Settings.


#include "DBDashProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

ADBDashProjectile::ADBDashProjectile()
{
	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;

	MoveComp->InitialSpeed = 6000.0f;
}

void ADBDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &ADBDashProjectile::Explode, DetonateDelay);
}

void ADBDashProjectile::Explode_Implementation()
{
	//Clear Timer if Explode was already called through another source like OnHit
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);

	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

	EffectComp->DeactivateSystem();

	MoveComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ADBDashProjectile::TeleportInsitgator, TeleportDelay);
}

void ADBDashProjectile::TeleportInsitgator()
{
	AActor* ActorToTeleport = GetInstigator();
	if(ensure(ActorToTeleport))
	{
		//keep instigator rotation otherwise the effect may be jarring
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
	}
}



