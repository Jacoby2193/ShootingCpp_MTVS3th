// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManagerActor.h"
#include "EnemyActor.h"
#include "Components/ArrowComponent.h"

AEnemyManagerActor::AEnemyManagerActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>( TEXT( "RootComp" ) );
	SetRootComponent( RootComp );

	Origin = CreateDefaultSubobject<UArrowComponent>( TEXT( "Origin" ) );
	Origin->SetupAttachment( RootComponent );

	Origin->SetRelativeRotation( FRotator(-90, 180, 0) );
	//(Pitch = -90.000000 , Yaw = 180.000000 , Roll = 0.000000)
}

// Called when the game starts or when spawned
void AEnemyManagerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 1. 시간이 흐르다가
	CurrentTime += DeltaTime;
	// 2. 만약 현재시간이 생성시간을 초과하면
	if (CurrentTime > MakeTime)
	{
	//		3. MakeEnemy함수를 호출하고싶다.
		MakeEnemy();
	//		4. 현재시간을 0으로 초기화 하고싶다.
		CurrentTime = 0;
	 }
}

void AEnemyManagerActor::MakeEnemy()
{
	// 적을 생성해서 Origin의 위치와 회전값을 적용하고싶다.
	FTransform t = Origin->GetComponentTransform();
	GetWorld()->SpawnActor<AEnemyActor>( EnemyFactory , t );
}

