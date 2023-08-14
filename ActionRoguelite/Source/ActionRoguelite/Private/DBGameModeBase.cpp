// Fill out your copyright notice in the Description page of Project Settings.


#include "DBGameModeBase.h"

#include "DBAttributesComponent.h"
#include "AI/DBAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"

ADBGameModeBase::ADBGameModeBase()
{
	SpawnTimerInterval = 2.0f;
}

void ADBGameModeBase::StartPlay()
{
	Super::StartPlay();

	/*Continuous timer to spawn in more bots
	 *Actual amount of bots and whether their allowed to be spawn defined later in chain
	 */
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ADBGameModeBase::SpawnTimerElapsed, SpawnTimerInterval, true);
}

void ADBGameModeBase::SpawnTimerElapsed()
{
	int32 NumOfAliveBots = 0;
	for(TActorIterator<ADBAICharacter> It(GetWorld()); It; ++It)
	{
		ADBAICharacter* Bot = *It;

		UDBAttributesComponent *AttributeComp = UDBAttributesComponent::GetAttributes(Bot);
		if(ensure(AttributeComp) && AttributeComp->isAlive())
		{
			NumOfAliveBots++;
		}
	}

	UE_LOG(LogTemp, Log,TEXT("Found %i number of bots"), NumOfAliveBots);
	
	float MaxBots = 5.0f;

	if(DifficultyCurve)
	{
		MaxBots = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}
		
	if(NumOfAliveBots >= MaxBots)
	{
		UE_LOG(LogTemp, Log, TEXT("Max number of bots reached skipping spawn"))
		return;
	}
	
	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);

	//Check for nullptr in case we didn't set up a SpawnBotQuery which has to be assigned in Blueprints
	if(ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ADBGameModeBase::OnQueryCompleted);	
	}
}

/*Triggered a few frames after we have run our EQS Query.
 *Gives the location of where we want to spawn our bots
 */
void ADBGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if(QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("SPAWN BOT EQS QUERY FAILED!"));
		return;
	}
	
	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	//Check to make sure there is at least 1 valid location to spawn a bot
	if(Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);
		DrawDebugSphere(GetWorld(), Locations[0], 50.0f, 20, FColor::Blue, false, 60.0f);
	}
}


