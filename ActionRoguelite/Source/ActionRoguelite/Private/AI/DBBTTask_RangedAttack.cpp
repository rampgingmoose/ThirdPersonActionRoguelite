// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DBBTTask_RangedAttack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UDBBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Spawn a projectile in the direction of our target actor
	 AAIController *MyController = OwnerComp.GetAIOwner();

	if(ensure(MyController))
	{
		//Cast to ACharacter because we need the GetMesh() in the character class to obtain the socket location for the projectile spawn point
		ACharacter *AIPawn = Cast<ACharacter>(MyController->GetPawn());
		
		//if MyPawn equals nullptr then return node result failed.
		if(!AIPawn)
		{
			return EBTNodeResult::Failed;
		}

		FVector MuzzleLocation = AIPawn->GetMesh()->GetSocketLocation("Muzzle_01");

		AActor *TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		//If AI has not yet "seen" the player the targetActor will be null and will return a failed result
		if(TargetActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		//Always pass the target first then the origin to get the direction vector
		FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;
		//convert this vector to a rotator so the AI knows which way to rotates towards
		FRotator MuzzleRotation = Direction.Rotation();

		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Params.Instigator = AIPawn;

		AActor *NewProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, Params);

		//if projectile spawn successfully return succeeded otherwise return failed
		return NewProjectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}
