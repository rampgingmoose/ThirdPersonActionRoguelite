// Fill out your copyright notice in the Description page of Project Settings.


#include "DBTargetDummy.h"
#include "Components/StaticMeshComponent.h"
#include "DBAttributesComponent.h"

// Sets default values
ADBTargetDummy::ADBTargetDummy()
{
 	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	AttributesComp = CreateDefaultSubobject<UDBAttributesComponent>("AttributesComp");
	
}

void ADBTargetDummy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	//Triggered when health is changed through damage/healing
	AttributesComp->OnHealthDamaged.AddDynamic(this, &ADBTargetDummy::OnHealthDamaged);
}


void ADBTargetDummy::OnHealthDamaged(AActor* InstigatorActor, UDBAttributesComponent* OwningComp, float NewHealth, float Delta)
{
	if(Delta < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("HitTime", GetWorld()->TimeSeconds);	
	}
}




