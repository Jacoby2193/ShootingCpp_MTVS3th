// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "Components/BoxComponent.h"
#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "ShooingGameMode.h"
#include "GameoverUI.h"
#include "MainUI.h"
#include "Components/WidgetComponent.h"

AEnemyActor::AEnemyActor()
{
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


	HPComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPComp"));
	HPComp->SetupAttachment( RootComponent );

}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	// HPComp의 위젯을 가져와서 HpUI에 기억시키고싶다.
	HpUI = Cast<UHPUI>(HPComp->GetWidget());

	// 태어날 때 방향을 정하고
	// 만약 30%의 확률로 플레이어방향
	int32 randValue = FMath::RandRange( 0 , 9 );
	if (randValue < 3)
	{
		//	목적지를 알고싶다.
		// 명시적, 암시적
		auto* player = GetWorld()->GetFirstPlayerController()->GetPawn();
		//	내가 목적지를 향하는 방향을 알고싶다.
		if (nullptr != player)
		{
			Direction = player->GetActorLocation() - this->GetActorLocation();
			//	그 방향의 크기를 1로 하고싶다.
			Direction.Normalize();
			//  그 방향을 기억하고싶다.
		}
	}
	// 그렇지 않고 나머지 확률로
	else {
		//	앞방향으로 기억하고 싶다.
		Direction = GetActorForwardVector();
	}
	// Java : 리스너
	// 델리게이트
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnMyBoxBeginOverlap );

	FRotator rot = UKismetMathLibrary::MakeRotFromXZ( Direction , GetActorUpVector() );
	SetActorRotation( rot );
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 살아가면서 그 방향으로 이동하고싶다.
	// P = P0 + vt
	SetActorLocation( GetActorLocation() + Direction * Speed * DeltaTime );
}

void AEnemyActor::NotifyActorBeginOverlap( AActor* OtherActor )
{
	//// 만약 상대가 플레이어라면
	//if (OtherActor->IsA<APlayerPawn>())
	//{
	//	// 너죽고
	//	OtherActor->Destroy();
	//	// 나죽자
	//	this->Destroy();
	//}

	// 만약 상대가 플레이어라면
	//if (OtherActor->GetActorNameOrLabel().Contains(TEXT("Player")))
	//{
	//}
	//if (OtherActor->Tags.Num() > 0 && OtherActor->Tags[0] == TEXT("Player"))
	//{
	//}
	// 너죽고 나죽고 하고싶다.
}

void AEnemyActor::OnMyBoxBeginOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	// 만약 상대가 플레이어라면
	if (OtherActor->IsA<APlayerPawn>())
	{
		APlayerPawn* player = Cast<APlayerPawn>( OtherActor );
		// 주인공의 체력을 1 감소하고 싶다.
		player->OnMyTakeDamage( 1 );
		// 만약 주인공의 체력이 0이하라면 파괴하고싶다.
		if (player->HP <= 0)
		{
			player->Destroy();
			
			// 게임모드를 가져오고싶다.
			auto* gm = Cast<AShooingGameMode>(GetWorld()->GetAuthGameMode());
			// 게임오버UI를 활성화 하고싶다.
			gm->MainUI->Gameover->SetVisibility( ESlateVisibility::Visible );
			// 마우스 커서를 보이게하고 입력을 UI로 하고싶다.
			auto* pc = GetWorld()->GetFirstPlayerController();
			pc->SetShowMouseCursor( true );
			pc->SetInputMode( FInputModeUIOnly() );

		}

		// 나죽자
		this->Destroy();

		// 폭발 SFX를 재생하고싶다.
		UGameplayStatics::PlaySound2D( GetWorld() , ExplosionSound );

		// 폭발 VFX를 재생하고싶다.
		UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , ExplosionVFX , GetActorLocation() );
	}
}

