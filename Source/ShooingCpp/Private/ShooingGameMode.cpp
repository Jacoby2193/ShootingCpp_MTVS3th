// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooingGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.h"

void AShooingGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySound2D( GetWorld() , BGM );

	// MainUI를 생성하고 
	MainUI = Cast<UMainUI>(CreateWidget( GetWorld() , MainUIFactory ));
	// 화면에 보이게하고싶다.
	MainUI->AddToViewport();
}

void AShooingGameMode::AddScore( int32 point )
{
	Score += point;

	// UI에게 Score를 전달하고
	MainUI->SetScore( Score );
	
	UE_LOG( LogTemp , Warning , TEXT( "Score : %d" ) , Score );

	FString str = FString::Printf( TEXT( "Score : %d" ) , Score );
	GEngine->AddOnScreenDebugMessage( 0 , 3 , FColor::Yellow , str );
}

void AShooingGameMode::SetHPUI( float Cur , float Max )
{
	MainUI->SetHP( Cur , Max );
}
