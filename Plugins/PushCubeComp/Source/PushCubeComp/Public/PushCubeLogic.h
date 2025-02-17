// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PushCubeLogic.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUSHCUBECOMP_API UPushCubeLogic : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPushCubeLogic();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Presets")
	float Force;

	UPROPERTY(EditAnywhere, Category = "Presets")
	TSubclassOf<AActor> SpawnedCube;

public:	
	UFUNCTION(BlueprintCallable, Category = "Presets")
	void StartPushing(bool spawnCube);
};
