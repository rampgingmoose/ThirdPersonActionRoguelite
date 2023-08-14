// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DBProjectileBase.generated.h"

class USphereComponent;
class UParticleSystem;
class UProjectileMovementComponent;
class UAudioComponent;
class USoundCue;
class UCameraShakeBase;

UCLASS(Abstract)
class ACTIONROGUELITE_API ADBProjectileBase : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ImpactVFX;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components")
	UProjectileMovementComponent* MoveComp;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, category = "Components")
	UParticleSystemComponent* EffectComp;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Shake")
	TSubclassOf<UCameraShakeBase> ImpactShake;

	UPROPERTY(EditDefaultsOnly, Category= "Effects|Shake")
	float ImpactShakeInnerRadius;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects|Shake")
	float ImpactShakeOuterRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	USoundCue* ImpactSound;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UAudioComponent* AudioComp;

	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();

	virtual void PostInitializeComponents() override;

public:	
	// Sets default values for this actor's properties
	ADBProjectileBase();

};
