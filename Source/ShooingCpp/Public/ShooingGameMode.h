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
	int32 Score;
	void AddScore( int32 point );

	// 태어날 때 WBP_Main 을 생성해서 Viewport에 붙이고싶다.
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> MainUIFactory;

	UPROPERTY()
	class UMainUI* MainUI;

	// UI의 값을 갱신하고싶다.
	void SetHPUI(float Cur, float Max);
	
};
