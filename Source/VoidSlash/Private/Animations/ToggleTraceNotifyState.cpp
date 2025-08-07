// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/ToggleTraceNotifyState.h"
#include "Combat/TraceComponent.h"

void UToggleTraceNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, FAnimNotifyEventReference const& EventReference)
{
	UTraceComponent* TraceComp{
		MeshComp->GetOwner()->FindComponentByClass<UTraceComponent>()
	};

	if (!IsValid(TraceComp)) { return; }

	TraceComp->bIsAttacking = true;
}

void UToggleTraceNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, FAnimNotifyEventReference const& EventReference)
{
	UTraceComponent* TraceComp{
		MeshComp->GetOwner()->FindComponentByClass<UTraceComponent>()
	};

	if (!IsValid(TraceComp)) { return; }

	TraceComp->bIsAttacking = false;
}
