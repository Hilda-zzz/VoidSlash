// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/LockonComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "VoidSlashCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/Enemy.h"
// Sets default values for this component's properties
ULockonComponent::ULockonComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void ULockonComponent::StartLockon(float Radius)
{
	FHitResult OutResult;
	FVector CurrentLocation{ OwnerRef->GetActorLocation() };
	FCollisionShape Sphere{ FCollisionShape::MakeSphere(Radius) };
	FCollisionQueryParams IgnorParams{
		FName{TEXT("Ignore Collision Params")},
		false,
		OwnerRef
	};

	bool bHasFoundTarget=GetWorld()->SweepSingleByChannel(
		OutResult,
		CurrentLocation,
		CurrentLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		Sphere,
		IgnorParams
	);

	if (!bHasFoundTarget) { return; }
	if (!OutResult.GetActor()->Implements<UEnemy>()) { return; }  // Valid the interface

	CurrentTargetActor = OutResult.GetActor();

	Controller->SetIgnoreLookInput(true);
	MovementComp->bOrientRotationToMovement = false;
	MovementComp->bUseControllerDesiredRotation = true;
	SpringArmComp->TargetOffset = FVector{ 0.0,0.f,100.0 };

	IEnemy::Execute_OnSelect(CurrentTargetActor);     // implement in blueprint in each enemy bpa
	OnUpdateTargetDelegate.Broadcast(CurrentTargetActor);
	//--------------------------------
	UE_LOG(
		LogTemp, Warning, TEXT("Lockon Started! Actor Detected: %s"),
		*OutResult.GetActor()->GetName()
	);

}

void ULockonComponent::EndLockon()
{
	IEnemy::Execute_OnDeselect(CurrentTargetActor);

	CurrentTargetActor =nullptr;
	
	MovementComp->bOrientRotationToMovement = true;
	MovementComp->bUseControllerDesiredRotation = false;
	SpringArmComp->TargetOffset = FVector::ZeroVector;

	Controller->ResetIgnoreLookInput();

	OnUpdateTargetDelegate.Broadcast(CurrentTargetActor);
}

void ULockonComponent::ToggleLockon(float Radius)
{
	if (IsValid(CurrentTargetActor))
	{
		EndLockon();
	}
	else
	{
		StartLockon(Radius);
	}
}


// Called when the game starts
void ULockonComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerRef = Cast<ACharacter>(GetOwner());
	if (!OwnerRef)
	{
		UE_LOG(LogTemp, Error, TEXT("LockonComponent: Owner is not a Character!"));
		return;
	}
	Controller = GetWorld()->GetFirstPlayerController();
	MovementComp = OwnerRef->GetCharacterMovement();
	SpringArmComp = OwnerRef->FindComponentByClass<USpringArmComponent>();
}


// Called every frame
void ULockonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsValid(CurrentTargetActor)) { return; }
	FVector CurrentLocation = OwnerRef->GetActorLocation();
	FVector TargetLocation = CurrentTargetActor->GetActorLocation();

	double TargetDistance{
		FVector::Distance(CurrentLocation,TargetLocation)
	};
	if (TargetDistance >= BreakDistance)
	{
		EndLockon();
		return;
	}

	TargetLocation.Z -= 125;
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(
		CurrentLocation, TargetLocation
	);

	Controller->SetControlRotation(NewRotation);
}

