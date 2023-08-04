// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DBAICharacter.h"

// Sets default values
ADBAICharacter::ADBAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADBAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADBAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



