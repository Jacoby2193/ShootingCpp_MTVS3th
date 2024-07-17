// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletActor.generated.h"

UCLASS()
class SHOOINGCPP_API ABulletActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 만약 부딪힌 상대가 AEnemy라면 너죽고 나죽고 하고 싶다.
	UFUNCTION()
	void OnMyBoxBeginOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult );


	// 앞으로 이동하고싶다.
	// 외형, 충돌체, Speed
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
	float Speed = 1000;

	// 누군가와 충돌하면 폭발소리를 내고싶다.
	UPROPERTY(EditAnywhere)
	class USoundBase* ExplosionSound;

	// - 폭발 VFX를 배치하고싶다.
	UPROPERTY(EditAnywhere)
	class UParticleSystem* ExplosionVFX;

	void SetActive( bool bValue );

};
