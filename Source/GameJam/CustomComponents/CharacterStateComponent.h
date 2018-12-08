// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Engine/EngineTypes.h"
#include "Components/ActorComponent.h"
#include "CharacterStateComponent.generated.h"


UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	NotSet = 0		UMETA(Display, "NotSet"),
	Normal = 1		UMETA(Display, "Normal"),
	Battle = 2		UMETA(Display, "Battle"),
	Chase = 3		UMETA(Display, "Chase"),
	Dead = 4		UMETA(Display, "Dead"),
	Frozen = 5 		UMETA(Display, "Frozen"),
	Stun = 6 		UMETA(Display, "Stun")
};

UCLASS(Blueprintable,ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEJAM_API UCharacterStateComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeStateDelegate,FName, VariableName);
public:	
	// Sets default values for this component's properties
	UCharacterStateComponent();

	/** Delegate to execute when we change State. */
	UPROPERTY(BlueprintAssignable)
	FChangeStateDelegate OnChangeCharacterState;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetCurrentHP, Category = "StateInfo")
	float CurrentHP=0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetMaxHP, Category = "StateInfo")
	float MaxHP = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetCurrentState, Category = "StateInfo")
	ECharacterState CurrentState = ECharacterState::NotSet;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void CalculateCurrentHP(float AddHP,const class UDamageType* DamageType);
	bool IsDead();

	UFUNCTION(BlueprintSetter)
	void SetCurrentHP(float NewCurrentHP);
	float GetCurrentHP();

	UFUNCTION(BlueprintSetter)
	void SetMaxHP(float NewMaxHP);
	float GetMaxHP();

	UFUNCTION(BlueprintSetter)
	void SetCurrentState(ECharacterState NewCurrentState);
	ECharacterState GetCurrentState();

	UFUNCTION()
	virtual void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
	UFUNCTION()
	virtual void OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);
	
	UFUNCTION()
	virtual void OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintNativeEvent)
	float CalculateAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	virtual float CalculateAnyDamage_Implementation(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
	UFUNCTION(BlueprintNativeEvent)
	float CalculatePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);
	virtual float CalculatePointDamage_Implementation(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);
	
	UFUNCTION(BlueprintNativeEvent)
	float CalculateRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser);
	virtual float CalculateRadialDamage_Implementation(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser);	
};
