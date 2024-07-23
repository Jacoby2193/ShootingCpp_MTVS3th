// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossActor.generated.h"

UCLASS()
class SHOOINGCPP_API ABossActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void OnMyBoxBeginOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult );

	// 0 : 목적지 찾기, 1 : 이동, 2 : 공격
	const int State_FindTarget = 0;
	const int State_Move = 1;
	const int State_Attack = 2;
	int32 State = State_FindTarget;

	FVector StartLocation;

	UPROPERTY()
	AActor* MoveTarget;

	float Alpha;

	int32 PrevChooseIndex = -1;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> BulletFactory;

	float angle = 0;
	FQuat rot;
	float CurrentTime;
	float FireTime = 0.1f;
	
	UPROPERTY(EditAnywhere)
	bool bDelay = true;

	void TickFindTarget();
	void TickMove( float DeltaTime );
	void TickAttack( float DeltaTime );
};
