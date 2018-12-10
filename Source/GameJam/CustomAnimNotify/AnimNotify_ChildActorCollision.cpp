// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotify_ChildActorCollision.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Weapon/WeaponActor.h"

void UAnimNotify_ChildActorCollision::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	AActor* Actor = MeshComp->GetOwner();
	if (!Actor)
	{
		return;
	}
	TArray<class AActor*> ChildActors;
	Actor->GetAllChildActors(ChildActors);

	for (auto ChildActor : ChildActors)
	{
		if (ChildActor->GetParentComponent()->GetAttachSocketName() == SocketName)
		{
			TargetActor.Add(ChildActor);
			AWeaponActor* WeaponActor = Cast<AWeaponActor>(ChildActor);
			//WeaponActor->GetShpereComp()->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
			WeaponActor->GetShpereComp()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			//ChildActor->SetActorEnableCollision(true);
			//UE_LOG(LogClass, Warning, TEXT(__FUNCTION__));
		}
	}
}

void UAnimNotify_ChildActorCollision::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	for (auto Actor : TargetActor)
	{
		AWeaponActor* WeaponActor = Cast<AWeaponActor>(Actor);
		//WeaponActor->GetShpereComp()->SetCollisionProfileName(TEXT("NoCollision"));
		WeaponActor->GetShpereComp()->SetCollisionEnabled(ECollisionEnabled::NoCollision);


		//Actor->SetActorEnableCollision(false);		
		//UE_LOG(LogClass, Warning, TEXT(__FUNCTION__));
	}
	TargetActor.Empty();
}
