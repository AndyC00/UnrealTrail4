// Fill out your copyright notice in the Description page of Project Settings.


#include "PushCubeLogic.h"
//if the pluin needs to be packed, it is necessary to include the reference file:
#include "GameFrameWork/Actor.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UPushCubeLogic::UPushCubeLogic()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Force = 500.0f;
}


// Called when the game starts
void UPushCubeLogic::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPushCubeLogic::StartPushing(bool spawnCube)
{
	if (GetOwner())
	{
		FVector Start = GetOwner()->GetActorLocation();
		FVector End = Start + (GetOwner()->GetActorForwardVector() * 300.0f);

		if (spawnCube && SpawnedCube)
		{
			//spawn the cube
			GetWorld()->SpawnActor<AActor>(SpawnedCube, End, FRotator(0,0,0) );
		}

		// shoot the ray, push the cube
		FHitResult Hit;
		FCollisionQueryParams QParams;
		bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, QParams);

		//get the hit actor detected, get its Static Mesh Component
		if (bHit)
		{
			UStaticMeshComponent* SMComp = Cast<UStaticMeshComponent>(Hit.GetActor()->GetRootComponent());
			bool CubeMovable = Hit.GetActor()->IsRootComponentMovable();

			if (CubeMovable && SMComp)
			{
				//show the testing ray
				DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 0.5f);

				//push the cube
				SMComp->AddImpulse(GetOwner()->GetActorForwardVector() * SMComp->GetMass() * Force);
			}
		}
	}
}

