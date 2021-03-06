// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomDamageType/CustomDamageType.h"
#include "RadialDamageType.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAM_API URadialDamageType : public UCustomDamageType
{
	GENERATED_BODY()
public:
	URadialDamageType()
	{
		CustomDamageEventType = ECustomDamageEventType::Radial;
	}
};
