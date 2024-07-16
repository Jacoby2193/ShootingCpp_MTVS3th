// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"

/**
 * 
 */
UCLASS()
class SHOOINGCPP_API UMainUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* Text_Score;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* Text_HighScore;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* HPBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UGameoverUI* Gameover;


	void SetScore( int32 NewScore );

	void SetHP( float Cur , float Max );
	void SetHighScore( int32 NewHighScore );
};
