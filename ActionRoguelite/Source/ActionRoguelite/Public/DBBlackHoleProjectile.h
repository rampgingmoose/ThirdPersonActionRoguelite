// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DBProjectileBase.h"
#include "DBBlackHoleProjectile.generated.h"

class URadialForceComponent;
UCLASS()
class ACTIONROGUELITE_API ADBBlackHoleProjectile : public ADBProjectileBase
{
	GENERATED_BODY()

public:
	ADBBlackHoleProjectile();

protected:

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = "DetonateTimer")
	float DetonateDelay;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	URadialForceComponent *RadialForceComp;

	FTimerHandle TimerHandle_DelayedDetonate;
	
	virtual void Explode_Implementation() override;

	virtual void BeginPlay() override;
	
};
