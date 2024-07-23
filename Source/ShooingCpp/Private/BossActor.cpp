// Fill out your copyright notice in the Description page of Project Settings.


#include "BossActor.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABossActor::ABossActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 충돌체를 생성하고 루트컴포넌트로 지정하고싶다.
	BoxComp = CreateDefaultSubobject<UBoxComponent>( TEXT( "BoxComp" ) );
	SetRootComponent( BoxComp );
	// 외형을 생성하고 루트컴포넌트에 Attach 하고 싶다.
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "MeshComp" ) );
	MeshComp->SetupAttachment( RootComponent );

	BoxComp->SetGenerateOverlapEvents( true );
	BoxComp->SetCollisionProfileName( TEXT( "Enemy" ) );

	MeshComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );
}

// Called when the game starts or when spawned
void ABossActor::BeginPlay()
{
	Super::BeginPlay();
	BoxComp->OnComponentBeginOverlap.AddDynamic( this , &ABossActor::OnMyBoxBeginOverlap );
}

// Called every frame
void ABossActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	// 상태에따른 분기처리
	if (State_FindTarget == State)
	{
		TickFindTarget();
	}
	else if (State_Move == State)
	{
		TickMove( DeltaTime );
	}
	else if (State_Attack == State)
	{
		TickAttack( DeltaTime );
	}
}

void ABossActor::OnMyBoxBeginOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
}

void ABossActor::TickFindTarget()
{
	// 목적지 찾기
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClassWithTag( GetWorld() , AStaticMeshActor::StaticClass() , TEXT( "BossWayPoint" ) , OutActors );
	MoveTarget = nullptr;
	if (OutActors.Num() > 0)
	{
		int32 chooseIndex = FMath::RandRange( 0 , OutActors.Num() - 1 );

		// 만약 한번이상 인덱스를 선택한 적이 있다. 그리고 chooseIndex와PrevChooseIndex가 같다면
		if (PrevChooseIndex != -1 && chooseIndex == PrevChooseIndex)
		{
			// chooseIndex를 다시 다른값으로 하고싶다.
			chooseIndex = (chooseIndex + 1) % OutActors.Num();
			//chooseIndex = (chooseIndex + OutActors.Num() - 1) % OutActors.Num();
		}

		MoveTarget = OutActors[chooseIndex];

		PrevChooseIndex = chooseIndex;
	}
	// 만약 MoveTarget이 nullptr이 아니라면 이동상태로 전이하고싶다.
	// 나의 현재위치를 기억하고싶다.
	if (MoveTarget)
	{
		State = State_Move;
		Alpha = 0;
		StartLocation = GetActorLocation();
	}
}

void ABossActor::TickMove( float DeltaTime )
{
	// 이동
	// 시간이 흐르다가
	Alpha += DeltaTime;
	// 그 시간에 맞게 위치를 결정하고
	FVector newLoc = FMath::Lerp( StartLocation , MoveTarget->GetActorLocation() , Alpha );
	SetActorLocation( newLoc );
	// 만약 1초가 되면 공격(목적지 찾기) 상태로 전이 하고싶다.
	if (Alpha >= 1)
	{
		State = State_Attack;
		rot = GetActorRotation().Quaternion();
		angle = 0;
		CurrentTime = 0;
	}
}

void ABossActor::TickAttack(float DeltaTime)
{
	// 발사
	if (bDelay)
	{
		CurrentTime += DeltaTime;
		if (CurrentTime > FireTime)
		{
			CurrentTime = 0;
			int step = 30;
			float stepAngle = 360.f / step;

			FVector up = GetActorUpVector();
			FQuat add = FRotator( 0 , stepAngle , 0 ).Quaternion();
			FVector loc = GetActorLocation() + (rot * up).ForwardVector * 50;
			GetWorld()->SpawnActor<AActor>( BulletFactory , loc , (rot * up).Rotation() );
			rot *= add;

			angle += stepAngle;

			if (angle >= 360.f)
			{
				State = State_FindTarget;
			}
		}
	}
	else
	{
		int step = 30;
		float stepAngle = 360.f / step;
		FVector up = GetActorUpVector();
		FQuat add = FRotator( 0 , stepAngle , 0 ).Quaternion();
		rot = GetActorRotation().Quaternion();
		for (int i = 0; i < step; i++)
		{
			FVector loc = GetActorLocation() + (rot * up).ForwardVector * 50;
			GetWorld()->SpawnActor<AActor>( BulletFactory , loc , (rot * up).Rotation() );
			rot = rot * add;
		}

		State = State_FindTarget;
	}
}

