// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MainVoidSlashCharacter.h"
#include "Animations/PlayerAnimInstance.h" 

void AMainVoidSlashCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerAnim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
}

float AMainVoidSlashCharacter::GetDamage()
{
	return 10.0f;
}
