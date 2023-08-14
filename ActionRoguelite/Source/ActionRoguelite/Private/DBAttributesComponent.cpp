// Fill out your copyright notice in the Description page of Project Settings.


#include "DBAttributesComponent.h"

// Sets default values for this component's properties
UDBAttributesComponent::UDBAttributesComponent()
{
	MaxHealth = 100.0f;
	Health = MaxHealth;
}

bool UDBAttributesComponent::isAlive() const
{
	return Health > 0.0f;
}


bool UDBAttributesComponent::ApplyHealthChange(float Delta)
{
	//Store old health value to find difference between current health and old health for UMG component
	float OldHealth = Health;

	//Clamp the health value to be between 0 and 100 regardless of what the result of health + delta is.
	Health = FMath::Clamp(Health + Delta, 0.0f,MaxHealth);
	
	//Difference between old health and new health is Displayed on UMG component. IE oldhealth = 100 and current health = 80
	//oldhealth - current health = 20. 20 damage is sent to UMG text component to be displayed on UI.
	float ActualDelta = Health - OldHealth;
	OnHealthDamaged.Broadcast(nullptr, this, Health, ActualDelta);
	
	return !ActualDelta != 0;
}

int UDBAttributesComponent::GetMaxHealth() const
{
	return MaxHealth;
}

bool UDBAttributesComponent::IsFullHealth() const
{
	return Health == MaxHealth;
}

