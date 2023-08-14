// Fill out your copyright notice in the Description page of Project Settings.


#include "DBPowerup_HealthPotion.h"
#include "DBAttributesComponent.h"

ADBPowerup_HealthPotion::ADBPowerup_HealthPotion()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);

	HealAmount = 50.0f;
}

void ADBPowerup_HealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if(!ensure(InstigatorPawn))
	{
		return;	
	}

	UDBAttributesComponent* AttributesComponent = Cast<UDBAttributesComponent>(InstigatorPawn->GetComponentByClass(UDBAttributesComponent::StaticClass()));

	//Check to make sure player is not already max health
	if(ensure(AttributesComponent) && !AttributesComponent->IsFullHealth())
	{
		AttributesComponent->ApplyHealthChange(this, HealAmount);
		HideAndCooldownPowerup();
	}
}
