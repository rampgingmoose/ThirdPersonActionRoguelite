// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DBPowerUp.h"
#include "DBPowerup_HealthPotion.generated.h"

class UStaticMeshComponent;
UCLASS()
class ACTIONROGUELITE_API ADBPowerup_HealthPotion : public ADBPowerUp
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Heal")
	float HealAmount;

public:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	ADBPowerup_HealthPotion();
};
