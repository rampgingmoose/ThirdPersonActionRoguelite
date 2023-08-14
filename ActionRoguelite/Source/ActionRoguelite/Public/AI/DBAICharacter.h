// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DBAttributesComponent.h"
#include "GameFramework/Character.h"
#include "DBAICharacter.generated.h"

class UDBAttributesComponent;
class UPawnSensingComponent;
UCLASS()
class ACTIONROGUELITE_API ADBAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADBAICharacter();

protected:

	virtual void PostInitializeComponents() override;

	void SetTargetActor(AActor* newTarget);
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent *PawnSensingComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDBAttributesComponent* AttributesComp;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
	void OnHealthDamaged(AActor* InsitgatorActor, UDBAttributesComponent* OwningComp, float NewHealth, float Delta);
};
