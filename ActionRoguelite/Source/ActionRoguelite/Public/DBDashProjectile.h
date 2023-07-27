// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DBProjectileBase.h"
#include "DBDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELITE_API ADBDashProjectile : public ADBProjectileBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float TeleportDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float DetonateDelay;

	//Handle to cancel timer if we already hit something
	FTimerHandle TimerHandle_DelayedDetonate;

	virtual void Explode_Implementation() override;

	void TeleportInsitgator();

	virtual void BeginPlay() override;

public:

	ADBDashProjectile();
	
};
