// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VoidSlashCharacter.h"
#include "Interfaces/MainPlayer.h"

#include "MainVoidSlashCharacter.generated.h"

class UPlayerAnimInstance;
/**
 * 
 */
UCLASS()
class VOIDSLASH_API AMainVoidSlashCharacter : public AVoidSlashCharacter, public IMainPlayer
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	UPlayerAnimInstance* PlayerAnim;
};
