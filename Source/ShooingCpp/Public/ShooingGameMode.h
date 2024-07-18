// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooingGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOINGCPP_API AShooingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class USoundBase* BGM;

	// 점수를 저장하고 싶다.
	// - 점수 변수
public:
	// 총알이 적을 파괴했을 때 점수를 1점 추가하고싶다. + UI에도 표현하고싶다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Score;
	
	// 점수가 갱신되었을 때 최고점수보다 값이 크다면
	// 최고점수의 값을 현재 점수로 하고싶다.
	// 게임을 다시 시작해도 최고점수값을 유지하고싶다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 HighScore;


	void AddScore( int32 point );

	// 저장할 위치를 기억하고싶다.
	// -  SlotName, UserIndex
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString MySlotName = TEXT( "HighScore" );

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MyUserIndex = 0;

	// 저장하기 , 읽어오기 기능을 만들고싶다.
	// HighScore가 갱신될때 저장하기를 호출하고싶다.
	// 게임이 시작될 때 읽어오기 기능을 호출해서  HighScore의 값을 갱신하고싶다.

	void SaveGame();

	int32 LoadGame();


	// 태어날 때 WBP_Main 을 생성해서 Viewport에 붙이고싶다.
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> MainUIFactory;

	UPROPERTY()
	class UMainUI* MainUI;

	// UI의 값을 갱신하고싶다.
	void SetHPUI(float Cur, float Max);

	UPROPERTY(EditAnywhere)
	bool bBossMode = true;
	
};
