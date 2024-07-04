﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "BulletActor.h"
#include "Kismet/GameplayStatics.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// 충돌체 컴포넌트를 추가해서 Root컴포넌트로 설정
	BoxComp = CreateDefaultSubobject<UBoxComponent>( TEXT( "BoxComp" ) );
	SetRootComponent( BoxComp );
	// 박스 Extent를 50으로 하고싶다.
	BoxComp->SetBoxExtent( FVector( 50 ) );

	//메시 컴포넌트를 추가해서 Root컴포넌트에 Attach
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "MeshComp" ) );
	MeshComp->SetupAttachment( BoxComp );

	// 총구위치를 생성하고 루트에 붙이고 배치하고싶다.
	FirePositionComp = CreateDefaultSubobject<UArrowComponent>( TEXT( "FirePositionComp" ) );
	FirePositionComp->SetupAttachment( RootComponent );
	FirePositionComp->SetRelativeLocationAndRotation( FVector( 0 , 0 , 100 ) , FRotator( 90 , 0 , 0 ) );
	
	
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	// 좌우방향, 상하방향
	FVector dir = FVector( 0 , h , v );
	// dir의 길이를 1로 만들고싶다.
	dir.Normalize();
	// P = P0 + vt;
	FVector p0 = GetActorLocation();
	FVector velocity = dir * Speed;

	SetActorLocation( p0 + velocity * DeltaTime );



	// 1. Tick에서 bAutoFire가 true일 때 
	if (bAutoFire)
	{
		// 2. 시간이 흐르다가
		CurrentTime += DeltaTime;
		// 3. 현재시간이 발사 시간이 되면
		if (CurrentTime > FireTime)
		{
			// 4. 총알을 만들고싶다.
			MakeBullet();
			// 5. 현재시간을 0으로 초기화하고싶다.
			CurrentTime = 0;
		}
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );

	PlayerInputComponent->BindAxis( TEXT( "Horizontal" ) , this , &APlayerPawn::OnMyAxisHorizontal );
	PlayerInputComponent->BindAxis( TEXT( "Vertical" ) , this , &APlayerPawn::OnMyAxisVertical );

	PlayerInputComponent->BindAction( TEXT( "Fire" ) , IE_Pressed , this , &APlayerPawn::OnMyActionFire );
	PlayerInputComponent->BindAction( TEXT( "Fire" ) , IE_Released, this , &APlayerPawn::OnMyActionFire );

}

void APlayerPawn::OnMyAxisHorizontal( float value )
{
	h = value;
}

void APlayerPawn::OnMyAxisVertical( float value )
{
	v = value;
}

void APlayerPawn::OnMyActionFire()
{
	bAutoFire = !bAutoFire;
	MakeBullet();
	CurrentTime = 0;
}

void APlayerPawn::MakeBullet()
{
	FTransform t = FirePositionComp->GetComponentTransform();
	GetWorld()->SpawnActor<ABulletActor>( BulletFactory , t );

	// 소리를 재생하고싶다.
	UGameplayStatics::PlaySound2D(GetWorld(), FireSound);
}

