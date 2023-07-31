// Fill out your copyright notice in the Description page of Project Settings.


#include "DBAttributesComponent.h"

// Sets default values for this component's properties
UDBAttributesComponent::UDBAttributesComponent()
{
	Health = 100.0f;
}


bool UDBAttributesComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	OnHealthDamaged.Broadcast(nullptr, this, Health, Delta);
	
	return true; //Currently no alternate test cases that would return false. 
}

