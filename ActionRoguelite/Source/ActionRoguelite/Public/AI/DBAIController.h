// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DBAIController.generated.h"

class UBehaviorTree;

/**
 * 
 */
UCLASS()
class ACTIONROGUELITE_API ADBAIController : public AAIController
{
	GENERATED_BODY()

protected:
	 virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	UBehaviorTree *BehaviorTree;
	
};
