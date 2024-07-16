// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooingGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.h"
#include "ShootingSaveGame.h"

void AShooingGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySound2D( GetWorld() , BGM );

	// MainUI를 생성하고 
	MainUI = Cast<UMainUI>( CreateWidget( GetWorld() , MainUIFactory ) );
	// 화면에 보이게하고싶다.
	MainUI->AddToViewport();

	// 게임이 시작될 때 읽어오기 기능을 호출해서  HighScore의 값을 갱신하고싶다. + UI도...
	HighScore = LoadGame();
	MainUI->SetHighScore( HighScore );
}

void AShooingGameMode::AddScore( int32 point )
{
	Score += point;

	// 만약 Score가 HighScore보다 크다면
	if (Score > HighScore)
	{
		// HighScore의 값을 Score로 갱신하고
		HighScore = Score;
		// HighScore가 갱신될때 저장하기를 호출하고싶다.
		SaveGame();
		 // UI에도 표현하고싶다.
		MainUI->SetHighScore( HighScore );
	}

	// UI에게 Score를 전달하고
	MainUI->SetScore( Score );

	UE_LOG( LogTemp , Warning , TEXT( "Score : %d, HighScore : %d" ) , Score , HighScore );

	//FString str = FString::Printf( TEXT( "Score : %d" ) , Score );
	//GEngine->AddOnScreenDebugMessage( 0 , 3 , FColor::Yellow , str );
}

void AShooingGameMode::SaveGame()
{
	// 1. ShootingSaveGame 객체를 만들고
	UShootingSaveGame* sg = Cast<UShootingSaveGame>( UGameplayStatics::CreateSaveGameObject( UShootingSaveGame::StaticClass() ) );
	// 2. 그 객체의 HighScoreSave의 값을 HighScore로 갱신한다.
	sg->HighScoreSave = HighScore;
	// 3. 파일로 쓰고싶다.
	UGameplayStatics::SaveGameToSlot( sg , MySlotName , MyUserIndex );
}

int32 AShooingGameMode::LoadGame()
{
	// 1. 파일이 존재하는지 검사하고
	bool isExist = UGameplayStatics::DoesSaveGameExist( MySlotName , MyUserIndex );
	// 2. 만약 있다면
	if (isExist)
	{
		//	  2-1. 그 파일을 읽어서 ShootingSaveGame 객체로 생성해서
		UShootingSaveGame* sg = Cast<UShootingSaveGame>( UGameplayStatics::LoadGameFromSlot( MySlotName , MyUserIndex ));
		
		if (sg)
		{
			//	  2-2. 그안의 값을 반환 하고싶다.
			return sg->HighScoreSave;
		}
	}
	// 3. 그렇지 않다면
	//    3-1. 0을 반환하고싶다.
	return 0;
}

void AShooingGameMode::SetHPUI( float Cur , float Max )
{
	MainUI->SetHP( Cur , Max );
}
