// Fill out your copyright notice in the Description page of Project Settings.


#include "GameoverUI.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameoverUI::NativeConstruct()
{
	Super::NativeConstruct();

	// 시작할 때 버튼에 기능을 연결하고싶다.
	Button_Restart->OnClicked.AddDynamic( this , &UGameoverUI::OnMyRestart );
	Button_Quit->OnClicked.AddDynamic( this , &UGameoverUI::OnMyQuit );
}

void UGameoverUI::OnMyRestart()
{
	// 재시작 버튼을 누르면 현재 레벨을 다시 시작하고싶다.
	FString mapName = UGameplayStatics::GetCurrentLevelName( GetWorld() );
	UGameplayStatics::OpenLevel( GetWorld() , FName( *mapName ) );
}

void UGameoverUI::OnMyQuit()
{
	// 종료 버튼을 누르면 종료하고싶다.
	auto* pc = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), pc, EQuitPreference::Quit, false);
}
