// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DBAttributesComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthDamaged, AActor*, insitgatorActor, UDBAttributesComponent*, OwningComp,float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELITE_API UDBAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDBAttributesComponent();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Health;

public:

	UFUNCTION(BlueprintCallable)
	bool isAlive() const;
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthDamaged OnHealthDamaged;
	
	//ApplyHealthChange returns a boolean as we want to know whether or not the change actually succeeded
	//We're interested in this as the character may be invincible, dead, etc in which case we would not want damage applied.
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(float Delta); //Where delta is the difference we want to apply to the health
	
		
};
