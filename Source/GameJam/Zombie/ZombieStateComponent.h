// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomComponents/CharacterStateComponent.h"
#include "ZombieStateComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAMEJAM_API UZombieStateComponent : public UCharacterStateComponent
{
	GENERATED_BODY()

public:
	virtual void CalculateCurrentHP(float AddHP, const class UDamageType* DamageType);

	// Called when the game starts
	virtual void BeginPlay() override;
};
