// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ToggleTraceNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class VOIDSLASH_API UToggleTraceNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

	virtual void NotifyBegin(
		USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation,
		float TotalDuration,
		FAnimNotifyEventReference const& EventReference
	) override;
	
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation,
		FAnimNotifyEventReference const& EventReference
	) override;

};
