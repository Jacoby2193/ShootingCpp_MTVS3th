// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UBoxComponent;

UCLASS()
class SHOOINGCPP_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// 충돌체 컴포넌트를 추가해서 Root컴포넌트로 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp;
	
	//메시 컴포넌트를 추가해서 Root컴포넌트에 Attach
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* FirePositionComp;


	// 오른쪽으로 이동하고싶다.
	// P = P0 + v(방향*Speed)t
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 500;

	// 사용자의 입력에따라 상하좌우로 이동하고싶다.
	float h;
	float v;

	void OnMyAxisHorizontal( float value );
	void OnMyAxisVertical( float value );

	void OnMyActionFire();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABulletActor> BulletFactory;

	// Fire를 하면 소리를 내고싶다.
	UPROPERTY(EditAnywhere)
	class USoundBase* FireSound;

	// 자동 총쏘기 기능을 만들고싶다.
	// 마우스버튼 누르면  true, 떼면 false 를 기억하기 위한 변수 bAutoFire;
	// Tick에서 시간이 흐르다가 발사 시간이 되면 총알을 만들고싶다.	
	bool bAutoFire;
	float CurrentTime;
	float FireTime = 0.2f;

	void MakeBullet();

	// 최대체력, 현재체력을 만들고 싶다.
	float HP;
	
	UPROPERTY(EditAnywhere)
	float MaxHP = 2;

	void OnMyTakeDamage(int32 damage); // 적이 호출할 예정~!!!

	UPROPERTY()
	class AShooingGameMode* GM;

	// 태어날 때 체력의 값을 최대체력으로 하고싶다. + UI에 반영하고싶다.
	// 적이 나와 충돌하면 체력을 1 소모하고싶다. + UI에 반영하고싶다.
	// 만약 체력이 0이하가되면 파괴되고싶다.


	// 총알을 오브젝트풀 처리하고싶다.
	// [필요요소]
	// - 최초 생성할 총알 갯수(몇개 만들것인가?)
	UPROPERTY(EditAnywhere)
	int32 MaxBulletCount = 10;
	// - 총알 목록(탄창)
	UPROPERTY()
	TArray<class ABulletActor*> Magazine;
};

