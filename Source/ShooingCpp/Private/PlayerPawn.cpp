// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "BulletActor.h"
#include "Kismet/GameplayStatics.h"
#include "ShooingGameMode.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// 충돌체 컴포넌트를 추가해서 Root컴포넌트로 설정
	BoxComp = CreateDefaultSubobject<UBoxComponent>( TEXT( "BoxComp" ) );
	SetRootComponent( BoxComp );
	// 박스 Extent를 50으로 하고싶다.
	BoxComp->SetBoxExtent( FVector( 50 ) );


	//BoxComp->SetCollisionEnabled( ECollisionEnabled::QueryAndPhysics );
	//BoxComp->SetCollisionObjectType( ECC_GameTraceChannel1 );	// Player
	//BoxComp->SetCollisionResponseToAllChannels( ECR_Ignore );
	//BoxComp->SetCollisionResponseToChannel( ECC_GameTraceChannel3 , ECR_Overlap );

	//메시 컴포넌트를 추가해서 Root컴포넌트에 Attach
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "MeshComp" ) );
	MeshComp->SetupAttachment( BoxComp );


	BoxComp->SetGenerateOverlapEvents( true );
	BoxComp->SetCollisionProfileName( TEXT( "Player" ) );

	MeshComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );


	// 총구위치를 생성하고 루트에 붙이고 배치하고싶다.
	FirePositionComp = CreateDefaultSubobject<UArrowComponent>( TEXT( "FirePositionComp" ) );
	FirePositionComp->SetupAttachment( RootComponent );
	FirePositionComp->SetRelativeLocationAndRotation( FVector( 0 , 0 , 100 ) , FRotator( 90 , 0 , 0 ) );

	FirePositionComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	
	
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	GM = Cast<AShooingGameMode>(GetWorld()->GetAuthGameMode());
	
	// 현재체력을 최대체력으로 하고싶다.
	HP = MaxHP;
	// UI를 호출
	GM->SetHPUI( HP , MaxHP );

	// 마우스 커서를 안보이게하고 입력을 Game로 하고싶다.
	auto* pc = GetWorld()->GetFirstPlayerController();
	pc->SetShowMouseCursor( false );
	pc->SetInputMode( FInputModeGameOnly() );

	// 탄창에 총알을 10개 추가하고싶다.
	for (int32 i = 0; i < 10; i++)
	{
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ABulletActor* bullet = GetWorld()->SpawnActor<ABulletActor>( BulletFactory , params );
		// 생성된 총알을 비활하고
		bullet->SetActive(false);
		// 탄창에 넣고싶다.
		Magazine.Add( bullet );
	}
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

	SetActorLocation( p0 + velocity * DeltaTime, true);



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
	// 마우스 왼쪽 버튼을 누르면 bAutoFire를 On/Off 전환하고싶다.
	bAutoFire = !bAutoFire;

	// 만약 bAutoFire가 활성화 되면 총알을 한발 쏘고싶다.
	if (bAutoFire)
	{
		MakeBullet();
		CurrentTime = 0;
	}
}

void APlayerPawn::MakeBullet()
{
	// 탄창을 전부 검사해서 비활성화된 총알을 찾고싶다.
	bool FindResult = false;
	for (int i = 0; i < Magazine.Num(); i++)
	{
		// 찾았다면 
		if (false == Magazine[i]->MeshComp->GetVisibleFlag())
		{
			FindResult = true;
			// 그 총알을 활성화하고 총구 위치에 배치하고싶다.
			Magazine[i]->SetActive( true );
			FTransform t = FirePositionComp->GetComponentTransform();
			Magazine[i]->SetActorTransform( t );
			// 소리를 재생하고싶다.
			UGameplayStatics::PlaySound2D( GetWorld() , FireSound );
			// 반복을 그만하고싶다.
			break;
		}
	}
	if (false == FindResult)
	{
		//  찰칵 소리를 내고싶다.
	}

}

void APlayerPawn::OnMyTakeDamage( int32 damage )
{
	HP -= damage;

	// UI를 호출
	GM->SetHPUI( HP , MaxHP );

	UE_LOG( LogTemp , Warning , TEXT( "%.1f" ) , HP );
}

