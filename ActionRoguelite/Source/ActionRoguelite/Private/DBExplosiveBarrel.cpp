// Fill out your copyright notice in the Description page of Project Settings.


#include "DBExplosiveBarrel.h"
#include "Engine/StaticMesh.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ADBExplosiveBarrel::ADBExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BarrelMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("BarrelMesh");
	BarrelMeshComp->SetEnableGravity(true);
	BarrelMeshComp->SetSimulatePhysics(true);
	BarrelMeshComp->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	RootComponent = BarrelMeshComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(BarrelMeshComp);

	RadialForceComp->SetAutoActivate(false);
	
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->Radius = 750.0f;
	RadialForceComp->ImpulseStrength = 2500.0f;

	RadialForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

// Called when the game starts or when spawned
void ADBExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BarrelMeshComp->OnComponentHit.AddDynamic(this, &ADBExplosiveBarrel::OnActorHit);
}

// Called every frame
void ADBExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ADBExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComp->FireImpulse();

	UE_LOG(LogTemp, Log, TEXT("OnActorHit in Explosive Barrel"));

	//Example of Log Message:
	//logs: "OtherActor: MyActor_1, at gametime: 124.4"
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	FString CombinedString = FString::Printf(TEXT("Hit at Location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);
}


