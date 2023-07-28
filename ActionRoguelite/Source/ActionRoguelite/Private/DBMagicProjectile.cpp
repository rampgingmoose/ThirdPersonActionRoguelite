// Fill out your copyright notice in the Description page of Project Settings.


#include "DBMagicProjectile.h"

#include "DBAttributesComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "DBAttributesComponent.h"

// Sets default values
ADBMagicProjectile::ADBMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MoveComp->InitialSpeed = 2000.0f;

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ADBMagicProjectile::OnActorOverlap);
}

void ADBMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != GetInstigator())
	{
		UDBAttributesComponent *AttributeComp = Cast<UDBAttributesComponent>(OtherActor->GetComponentByClass(UDBAttributesComponent::StaticClass()));
		if(AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-20.0f);

			Destroy();
		}
	}
}

// Called when the game starts or when spawned
void ADBMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADBMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

