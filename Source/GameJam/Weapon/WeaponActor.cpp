// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "CustomDamageType/CustomDamageType.h"
#include "Components/ShapeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultScene = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultScene"));
	SetRootComponent(DefaultScene);

	TargetComp = CreateDefaultSubobject<USphereComponent>(TEXT("TargetComponent"));
	TargetComp->SetupAttachment(RootComponent);
	TargetComp->SetSphereRadius(30.0f);
	
	
}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();

	APawn* ParentPawn = Cast<APawn>(this->GetParentActor());
	if (ParentPawn)
	{
		Instigator = ParentPawn;
	}	

	//UShapeComponent* Collision = this->FindComponentByClass<UShapeComponent>();
	if (TargetComp)
	{
		TargetComp->OnComponentHit.AddDynamic(this, &AWeaponActor::OnComponentHit);
		TargetComp->OnComponentBeginOverlap.AddDynamic(this, &AWeaponActor::OnComponentBeginOverlap);
	}

	//SetActorEnableCollision(InitialEnableCollision);
}

// Called every frame
void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponActor::OnComponentHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor != UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		return;
	}

	UE_LOG(LogClass, Warning, TEXT("AWeaponActor::OnComponentHit: %s, %s, %s"), *OtherActor->GetName(), *OtherComp->GetName(), *Hit.BoneName.ToString());
		
	IgnoreActors.Add(this);
	
	// 프로젝타일 액터의 데미지를 발생시킨 액터
	if (Instigator != nullptr && Instigator->IsValidLowLevel() && OtherActor != Instigator)
	{
		// nullptr != 캐스팅하여 UCustomDamageType 가져오기 , nullptr이면 UCustomDamageType의 CDO 가져오기 
		UCustomDamageType const* const DamageTypeCDO = CustomDamageTypeClass ? CustomDamageTypeClass->GetDefaultObject<UCustomDamageType>() : GetDefault<UCustomDamageType>();
		switch (DamageTypeCDO->CustomDamageEventType)
		{
		case ECustomDamageEventType::Point:
			{
				FVector Dir = CurrLocation - PrevLocation;
				Dir.Normalize();
				UGameplayStatics::ApplyPointDamage(OtherActor, BaseDamage, Dir, Hit, nullptr, this, CustomDamageTypeClass);
				break;
			}
		case ECustomDamageEventType::Radial:
			UGameplayStatics::ApplyRadialDamage(GetWorld(), BaseDamage, Hit.Location, RadialDamageRadius, CustomDamageTypeClass, IgnoreActors, this);
			break;
		default:
			UGameplayStatics::ApplyDamage(OtherActor, BaseDamage, nullptr, this, CustomDamageTypeClass);
			break;
		}
	}	
}

void AWeaponActor::OnComponentBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		return;
	}

	UE_LOG(LogClass, Warning, TEXT("AWeaponActor::OnComponentBeginOverlap: %s %s %s"), *OtherActor->GetName(), *OtherComp->GetName(), *SweepResult.BoneName.ToString());
	   	  
	IgnoreActors.Add(this);

	//TArray<AActor*> IgnoreActors;
	// 데미지를 발생시킨 액터
	if (Instigator != nullptr && Instigator->IsValidLowLevel() && OtherActor != Instigator)
	{
		// nullptr != 캐스팅하여 UCustomDamageType 가져오기 , nullptr이면 UCustomDamageType의 CDO 가져오기 
		UCustomDamageType const* const DamageTypeCDO = CustomDamageTypeClass ? CustomDamageTypeClass->GetDefaultObject<UCustomDamageType>() : GetDefault<UCustomDamageType>();
		switch (DamageTypeCDO->CustomDamageEventType)
		{
		case ECustomDamageEventType::Point:
			{
				FVector Dir = CurrLocation - PrevLocation;
				Dir.Normalize();
				UGameplayStatics::ApplyPointDamage(OtherActor, BaseDamage, Dir, SweepResult, nullptr, this, CustomDamageTypeClass);
				break;
			}

		case ECustomDamageEventType::Radial:
			UGameplayStatics::ApplyRadialDamage(GetWorld(), BaseDamage, SweepResult.Location, RadialDamageRadius, CustomDamageTypeClass, IgnoreActors, this);
			break;
		default:
			UGameplayStatics::ApplyDamage(OtherActor, BaseDamage, nullptr, this, CustomDamageTypeClass);
			break;
		}
	}
}

void AWeaponActor::AddIgnoreActor(AActor* TargetActor)
{
	IgnoreActors.Add(TargetActor);
}