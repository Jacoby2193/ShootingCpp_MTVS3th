// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class SHOOINGCPP_API AEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 충돌하고싶다.
	// 1. Actor기반으로
	virtual void NotifyActorBeginOverlap( AActor* OtherActor ) override;
	// 2. Component기반으로...


	// 태어날 때 방향을 정하고
	// 30%의 확률로 플레이어방향, 나머지 확률로 앞방향으로 정하고싶다.

	// 살아가면서 그 방향으로 이동하고싶다.

	// 외형, 충돌체 
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;
	
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void OnMyBoxBeginOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult );


	float RandomRate = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Direction;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite)
	float Speed = 500.f;
};
