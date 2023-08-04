// Fill out your copyright notice in the Description page of Project Settings.


#include "DBCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DBInteractionComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DBAttributesComponent.h"

// Sets default values
ADBCharacter::ADBCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UDBInteractionComponent>("InteractionComp");

	AttributesComp = CreateDefaultSubobject<UDBAttributesComponent>("AttributesComp");
	
	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

void ADBCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributesComp->OnHealthDamaged.AddDynamic(this, &ADBCharacter::OnHealthDamaged);
}

// Called to bind functionality to input
void ADBCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADBCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADBCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ADBCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryDash", IE_Pressed, this, &ADBCharacter::Dash);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ADBCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &ADBCharacter::BlackHole);
}

void ADBCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	AddMovementInput(ControlRot.Vector(),Value);
}

void ADBCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(RightVector, Value);
}

void ADBCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ADBCharacter::PrimaryAttack_TimeElapsed, 0.2f);

	//Stop Attack if player character is killed
	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
}

void ADBCharacter::PrimaryAttack_TimeElapsed()
{
	SpawnProjectile(ProjectileClass);
}

void ADBCharacter::Dash()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_Dash, this, &ADBCharacter::Dash_TimeElapsed, 0.2f);
}

void ADBCharacter::Dash_TimeElapsed()
{
	SpawnProjectile(DashProjectileClass);
}

void ADBCharacter::BlackHole()
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimeHandle_BlackHole, this, &ADBCharacter::BlackHole_TimeElapsed, 0.2f);
}

void ADBCharacter::BlackHole_TimeElapsed()
{
	SpawnProjectile(BlackHoleProjectileClass);
}

void ADBCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	if(ensureAlways(ClassToSpawn))
	{
		FVector HandLocation= GetMesh()->GetSocketLocation("Muzzle_01");
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;
		
		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

		FCollisionQueryParams Params;
		//ignore the player
		Params.AddIgnoredActor(this);
		
		FCollisionShape SphereShape;
		SphereShape.SetSphere(20.0f);
		FHitResult Hit;

		FVector TraceStart = CameraComp->GetComponentLocation();
		//endpoint set far into look at distance but not too far. Still adjusts projectile towards crosshair on miss over time.
		FVector TraceEnd = TraceStart + (GetControlRotation().Vector() * 5000);

		//returns true on hit
		bool bHasHit = GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjectQueryParams, SphereShape, Params);

		if(bHasHit)
		{
			TraceEnd = Hit.ImpactPoint;
		}
		//Finds a new direction/rotation from hand to impact point in the world from line trace
		FRotator ProjectileRot = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();
		FTransform SpawnTM = FTransform(ProjectileRot, HandLocation);
		GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);
	}
}

void ADBCharacter::OnHealthDamaged(AActor* InstigatorActor, UDBAttributesComponent* OwningComp, float NewHealth,
	float Delta)
{

	if(NewHealth <= 0 && Delta < 0)
	{
		APlayerController *playerControls = Cast<APlayerController>(GetController());
		DisableInput(playerControls);
	}	
}




void ADBCharacter::PrimaryInteract()
{
	if(InteractionComp != nullptr)
	{
		InteractionComp->PrimaryInteract();
	}
}


