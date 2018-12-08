// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieStateComponent.h"
#include "CustomDamageType/FrozenDamageType.h"

void UZombieStateComponent::CalculateCurrentHP(float AddHP, const class UDamageType* DamageType)
{
	if (IsDead())
	{
		return;
	}

	// FronzenDamage는 State,HP 상관없이 즉사
	const UFrozenDamageType* FrozenDamageType = Cast<UFrozenDamageType>(DamageType);
	if (FrozenDamageType)
	{
		SetCurrentHP(0);
		SetCurrentState(ECharacterState::Dead);
		return;
	}
	// 아니면 일반적인 데미지
	
	
	//Frozen은 데미지 받지않음.
	if (CurrentState == ECharacterState::Frozen)
	{
		return;
	}

	float NewCurrentHP = CurrentHP + AddHP;	
	if (NewCurrentHP <= 0)
	{
		NewCurrentHP = 0;		
	}
	SetCurrentHP(NewCurrentHP);
	if (NewCurrentHP == 0)
	{
		SetCurrentState(ECharacterState::Frozen);
		UE_LOG(LogClass, Warning, TEXT("Frozen"));
	}	
}

void UZombieStateComponent::BeginPlay()
{
	Super::BeginPlay();
}
