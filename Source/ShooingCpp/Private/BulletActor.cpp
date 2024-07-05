﻿

#include "BulletActor.h"
#include "Components/BoxComponent.h"
#include "EnemyActor.h"

ABulletActor::ABulletActor()
{
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>( TEXT( "BoxComp" ) );
	SetRootComponent( BoxComp );
	BoxComp->SetBoxExtent( FVector( 37.5f, 12.5f, 50.f ) );

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "MeshComp" ) );
	MeshComp->SetupAttachment( RootComponent );

	// 생성자 도우미를 이용해서 에셋을 로드하고싶다.
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh( TEXT( "/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'" ) );

	// 만약 로드한것이 성공했다면
	if (TempMesh.Succeeded())
	{
		// 그 에셋을 컴포넌트에 넣어주고싶다.
		MeshComp->SetStaticMesh(TempMesh.Object);
		MeshComp->SetRelativeScale3D(FVector( 0.75f , 0.25f , 1));
	}


	BoxComp->SetGenerateOverlapEvents( true );
	BoxComp->SetCollisionProfileName( TEXT( "Bullet" ) );

	MeshComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );

}

void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
	
	// 충돌체야 너 누군가와 부딪히면 나도 좀 알려줘!!
	BoxComp->OnComponentBeginOverlap.AddDynamic( this , &ABulletActor::OnMyBoxBeginOverlap );
}

void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 나의 앞으로 이동하고 싶다.
	// P = P0 + vt
	FVector P0 = GetActorLocation();
	FVector velocity = GetActorForwardVector() * Speed;
	float t = DeltaTime;
	SetActorLocation( P0 + velocity * t );

}

// 만약 부딪힌 상대가 AEnemy라면 너죽고 나죽고 하고 싶다.
void ABulletActor::OnMyBoxBeginOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	// 만약 상대액터가 AEnemy라면
	if (OtherActor->IsA<AEnemyActor>())
	{
		// 너죽고 : 죽어주세요!
		OtherActor->Destroy();
		// 나죽고
		this->Destroy();
	}
}

