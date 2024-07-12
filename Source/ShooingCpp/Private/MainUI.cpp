// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "GameoverUI.h"

void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();

	Text_Score->SetText( FText::AsNumber( 0 ) );
	// 시작할 때 게임오버IU를 비활성화 해놓고싶다.
	Gameover->SetVisibility( ESlateVisibility::Hidden );
}

void UMainUI::SetScore( int32 NewScore )
{
	// UI가 그 Score를 표현하게 하고싶다.
	Text_Score->SetText( FText::AsNumber( NewScore ) );
}

void UMainUI::SetHP( float Cur , float Max )
{
	HPBar->SetPercent( Cur / Max );
}
