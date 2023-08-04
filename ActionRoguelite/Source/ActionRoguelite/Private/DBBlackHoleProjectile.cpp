// Fill out your copyright notice in the Description page of Project Settings.


#include "DBBlackHoleProjectile.h"
#include "DBAttributesComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"

ADBBlackHoleProjectile::ADBBlackHoleProjectile()
{
	MoveComp->InitialSpeed = 1500.0f;

	DetonateDelay = 4.0f;

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ADBBlackHoleProjectile::OnActorOverlap);

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetAutoActivate(true);
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->Radius = 1500.0f;
	RadialForceComp->ForceStrength = -250000.0f;
	RadialForceComp->SetupAttachment(SphereComp);
}

void ADBBlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &ADBBlackHoleProjectile::Explode, DetonateDelay);
}

void ADBBlackHoleProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if((OtherActor && OtherActor != GetInstigator()) && OtherComp)
	{
		UDBAttributesComponent *AttributesComp = Cast<UDBAttributesComponent>(OtherActor->GetComponentByClass(UDBAttributesComponent::StaticClass()));
		
		if(OtherComp->IsSimulatingPhysics())
		{
			OtherActor->Destroy();
		}
		
		if(AttributesComp)
		{
			AttributesComp->ApplyHealthChange(-50.0f);
		}
	}
}

void ADBBlackHoleProjectile::Explode_Implementation()
{
	if(ensure(IsValid(this)))
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);

		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

		Destroy();
	}
}


