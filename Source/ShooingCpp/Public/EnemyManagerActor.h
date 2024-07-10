// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManagerActor.generated.h"

// 일정시간마다 Enemy를 생성하고 배치하고싶다.
// - 현재시간, 생성시간, 적공장

UCLASS()
class SHOOINGCPP_API AEnemyManagerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManagerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// 일정시간마다 Enemy를 생성하고 배치하고싶다.
	// - 현재시간, 생성시간, 적공장:UClass:TSubclassOf
	float CurrentTime;
	float MakeTime = 1;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyActor> EnemyFactory;

	void MakeEnemy();

	UPROPERTY(EditAnywhere)
	class USceneComponent* RootComp;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* Origin;

	FTimerHandle Handle;
};
