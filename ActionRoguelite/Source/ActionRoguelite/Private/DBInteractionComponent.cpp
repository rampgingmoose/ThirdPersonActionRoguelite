// Fill out your copyright notice in the Description page of Project Settings.


#include "DBInteractionComponent.h"
#include "DBGameplayInterface.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UDBInteractionComponent::UDBInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDBInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDBInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//Will fire out a linetrace and will return the AActor Component it hits a Component that implements the IDBGameplayInterface
void UDBInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();
	
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);
	
	// FHitResult Hit;
	// bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	TArray<FHitResult> Hits;
	FCollisionShape SphereShape;
	float radius = 30.0f;
	SphereShape.SetSphere(radius);
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, SphereShape);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
	
	for(FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		//HitActor must be checked to see if it's null before being passed into Interact Func
		if(HitActor != nullptr)
		{
			if(HitActor->Implements<UDBGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);

				IDBGameplayInterface::Execute_Interact(HitActor, MyPawn);
				break;
			}
		}

		DrawDebugSphere(GetWorld(),Hit.ImpactPoint, radius, 32, LineColor, false, 2.0f);
	}
	DrawDebugLine(GetWorld(),EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);
}
