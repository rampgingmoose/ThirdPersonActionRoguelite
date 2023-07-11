// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DBGameplayInterface.h"
#include "DBInteractionComponent.h"
#include "GameFramework/Actor.h"
#include "DBLever.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELITE_API ADBLever : public AActor, public IDBGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADBLever();

	float TargetPitch;

	void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LeverMesh;

	UPROPERTY(VisibleAnywhere)
	UDBInteractionComponent* InteractComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
