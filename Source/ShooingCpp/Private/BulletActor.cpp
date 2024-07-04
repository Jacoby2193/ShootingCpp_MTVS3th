

#include "BulletActor.h"
#include "Components/BoxComponent.h"

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
}

void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
	
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

