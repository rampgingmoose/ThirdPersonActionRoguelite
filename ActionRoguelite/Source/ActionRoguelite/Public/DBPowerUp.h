// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DBGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "DBPowerUp.generated.h"

class USphereComponent;

UCLASS()
class ACTIONROGUELITE_API ADBPowerUp : public AActor, public IDBGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADBPowerUp();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere, Category = "Powerup")
	float RespawnTime;

	FTimerHandle TimerHandle_RespawnTimer;
	
	UFUNCTION()
	void ShowPowerup();

	void HideAndCooldownPowerup();

	void SetPowerupState(bool bNewIsActive);

public:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};
