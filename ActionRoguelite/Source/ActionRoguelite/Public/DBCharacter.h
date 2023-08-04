// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DBCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UDBInteractionComponent;
class UDBAttributesComponent;
class UAnimMontage;

UCLASS()
class ACTIONROGUELITE_API ADBCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> DashProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> BlackHoleProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_Dash;
	FTimerHandle TimeHandle_BlackHole;

public:
	// Sets default values for this character's properties
	ADBCharacter();

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

protected:
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UDBInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDBAttributesComponent* AttributesComp;
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	void PrimaryInteract();
	void Dash();
	void Dash_TimeElapsed();
	void BlackHole();
	void BlackHole_TimeElapsed();
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);
	
	UFUNCTION()
	void OnHealthDamaged(AActor* InstigatorActor, UDBAttributesComponent* OwningComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
