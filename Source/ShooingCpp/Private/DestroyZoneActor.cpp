// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyZoneActor.h"
#include "Components/BoxComponent.h"
#include "BulletActor.h"

// Sets default values
ADestroyZoneActor::ADestroyZoneActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// 충돌체를 생성하고 루트컴포넌트로 지정하고싶다.
	BoxComp = CreateDefaultSubobject<UBoxComponent>( TEXT( "BoxComp" ) );
	SetRootComponent( BoxComp );
	// 외형을 생성하고 루트컴포넌트에 Attach 하고 싶다.
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "MeshComp" ) );
	MeshComp->SetupAttachment( RootComponent );

	BoxComp->SetGenerateOverlapEvents( true );
	BoxComp->SetCollisionProfileName( TEXT( "DestroyZone" ) );

	MeshComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );

}

// Called when the game starts or when spawned
void ADestroyZoneActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestroyZoneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestroyZoneActor::NotifyActorBeginOverlap( AActor* OtherActor )
{
	Super::NotifyActorBeginOverlap( OtherActor );
	
	// 부딪힌 상대가 총알이라면 비활성화 하고싶다.
	// OtherActor 를 변신!!
	ABulletActor* bullet = Cast<ABulletActor>( OtherActor );
	if (bullet)
	{
		bullet->SetActive( false );
	}
	// 그렇지않다면 부딪힌 상대를 파괴하고싶다.
	else
	{
		OtherActor->Destroy();
	}
}

