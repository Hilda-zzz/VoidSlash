// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VoidSlashCharacter.h"
#include "Interfaces/MainPlayer.h"
#include "Interfaces/Fighter.h"
#include "MainVoidSlashCharacter.generated.h"

class UPlayerAnimInstance;
/**
 * 
 */
UCLASS()
class VOIDSLASH_API AMainVoidSlashCharacter : public AVoidSlashCharacter, public IMainPlayer, public IFighter
{
	GENERATED_BODY()
	
public:
	AMainVoidSlashCharacter();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	class UStatsComponent* StatsComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class ULockonComponent* LockonComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UCombatComponent* CombatComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UTraceComponent* TraceComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UBlockComponent* BlockComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UPlayerActionsComponent* PlayerActionsComp;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	UPlayerAnimInstance* PlayerAnim;

	virtual float GetDamage() override;

	virtual bool HasEnoughStamina(float Cost) override;
};
