// Fill out your copyright notice in the Description page of Project Settings.


#include "DBLever.h"
#include "Components/StaticMeshComponent.h"
#include "DBInteractionComponent.h"

// Sets default values
ADBLever::ADBLever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;
	
	LeverMesh = CreateDefaultSubobject<UStaticMeshComponent>("LeverMesh");
	LeverMesh->SetupAttachment(BaseMesh);

	InteractComp = CreateDefaultSubobject<UDBInteractionComponent>("InteractComp");

	TargetPitch = -30;
}

void ADBLever::Interact_Implementation(APawn* InstigatorPawn)
{
	LeverMesh->SetRelativeRotation(FRotator(0, TargetPitch, 0));

	
}


// Called when the game starts or when spawned
void ADBLever::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADBLever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



