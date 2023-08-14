// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DBBTService_CheckAttackRange.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UDBBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//Check Distance Between AIPawn and TargetActor
	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	
	if(ensure(BlackBoardComp))
	{
		//Cast To Actor as GetValueAsObject returns a UObject which does not have GetActorLocation() and is needed for distance check
		AActor *TargetActor = Cast<AActor>(BlackBoardComp->GetValueAsObject("TargetActor"));

		//No ensure added as this will be nullptr many times
		if(TargetActor)
		{
			//Need an AIController pointer in order to get the associated AI Pawn
			AAIController *MyController = OwnerComp.GetAIOwner();
			
			if(ensure(MyController))
			{
				//Need a Pawn pointer for the AI in order to access the GetActorLocation for the distance check
				APawn *AIPawn = MyController->GetPawn();

				//ensure added as BehaviorTree should not be running if the AIPawn is null
				if(ensure(AIPawn))
				{
					//Distance between two Vectors, TargetActor and AIPawn
					float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

					//If the Distance to the target Actor is less than the predetermined then the AI is within range and can attack
					bool bWithinRange = DistanceTo < 2000.0f;

					//automatically set line of sight equal to false if AI is out of range of player.
					//if AI is within range then check to see if the AI has line of sight, if not reposition to gain Line of sight
					bool bHasLineOfSight = false;
					if(bWithinRange)
					{
						bHasLineOfSight = MyController->LineOfSightTo(TargetActor);
					}

					//Pass this bool back to BlackBoard as it is the "memory" for the AI, "SelectedKeyName" used as an FName is expected in SetValueAsBool()
					BlackBoardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bWithinRange && bHasLineOfSight));
				}
			}
		}
	}
}


