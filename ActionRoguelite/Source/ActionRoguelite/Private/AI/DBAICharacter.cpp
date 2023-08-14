// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DBAICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "DBAttributesComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ADBAICharacter::ADBAICharacter()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AttributesComp = CreateDefaultSubobject<UDBAttributesComponent>("AttributesComp");
}

void ADBAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	PawnSensingComp->OnSeePawn.AddDynamic(this, &ADBAICharacter::OnPawnSeen);
	AttributesComp->OnHealthDamaged.AddDynamic(this, &ADBAICharacter::OnHealthDamaged);
}

void ADBAICharacter::SetTargetActor(AActor* newTarget)
{
	AAIController* AIC = Cast<AAIController>(GetController());

	if(AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor", newTarget);
	}
}

void ADBAICharacter::OnPawnSeen(APawn* Pawn)
{
	SetTargetActor(Pawn);

	//DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.0f, true);
}

void ADBAICharacter::OnHealthDamaged(AActor* InsitgatorActor, UDBAttributesComponent* OwningComp, float NewHealth, float Delta)
{
	if(Delta < 0)
	{
		if(InsitgatorActor != this)
		{
			SetTargetActor(InsitgatorActor);
		}
		
		if(NewHealth <= 0 )
		{
			//stop BT
			AAIController* AIC = Cast<AAIController>(GetController());
			if(AIC)
			{
				/*BrainComponent is the base class of the behavior tree component.
				 *"Killed" is the reason for stopping the behavior tree logic,
				this has no bearing on the execution of code, just for debugging purposes*/
				AIC->GetBrainComponent()->StopLogic("Killed");
			}
			//ragdoll
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");
			
			//set lifespan
			SetLifeSpan(10.0f);
		}
	}
}



