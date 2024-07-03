// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/BoxComponent.h"

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

	MeshComp->SetupAttachment( RootComponent );
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

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );

	PlayerInputComponent->BindAxis( TEXT( "Horizontal" ) , this , &APlayerPawn::OnMyAxisHorizontal );
	PlayerInputComponent->BindAxis( TEXT( "Vertical" ) , this , &APlayerPawn::OnMyAxisVertical );

}

void APlayerPawn::OnMyAxisHorizontal( float value )
{
	h = value;
}

void APlayerPawn::OnMyAxisVertical( float value )
{
	v = value;
}

