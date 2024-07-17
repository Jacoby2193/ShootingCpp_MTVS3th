// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameoverUI.generated.h"

// 시작할 때 버튼에 기능을 연결하고싶다.
// 재시작 버튼을 누르면 현재 레벨을 다시 시작하고싶다.
// 종료 버튼을 누르면 종료하고싶다.
// [필요 요소]
// - 재시작버튼
// - 종료버튼

UCLASS()
class SHOOINGCPP_API UGameoverUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Button_Restart;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Button_Quit;

	UPROPERTY(EditAnywhere, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* MyAnim;

	UFUNCTION()
	void OnMyRestart();

	UFUNCTION()
	void OnMyQuit();

};
