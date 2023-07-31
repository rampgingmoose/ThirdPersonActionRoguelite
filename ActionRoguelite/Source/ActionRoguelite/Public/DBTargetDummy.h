// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DBAttributesComponent.h"
#include "GameFramework/Actor.h"
#include "DBTargetDummy.generated.h"

class UStaticMeshComponent;
class UDBAttributesComponent;

UCLASS()
class ACTIONROGUELITE_API ADBTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADBTargetDummy();

protected:
	UPROPERTY(VisibleAnywhere)
	UDBAttributesComponent* AttributesComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;
	
	UFUNCTION()
	void OnHealthDamaged(AActor* InstigatorActor, UDBAttributesComponent* OwningComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;

};
