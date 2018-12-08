// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieStateComponent.h"
#include "CustomDamageType/FrozenDamageType.h"

void UZombieStateComponent::CalculateCurrentHP(float AddHP, const class UDamageType* DamageType)
{
	if (IsDead())
	{
		return;
	}

	// FronzenDamage�� State,HP ������� ���
	const UFrozenDamageType* FrozenDamageType = Cast<UFrozenDamageType>(DamageType);
	if (FrozenDamageType)
	{
		SetCurrentHP(0);
		SetCurrentState(ECharacterState::Dead);
		return;
	}
	// �ƴϸ� �Ϲ����� ������
	
	
	//Frozen�� ������ ��������.
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
