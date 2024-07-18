// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HPUI.generated.h"

/**
 * 
 */
UCLASS()
class SHOOINGCPP_API UHPUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HPBar;

	// 인라인 함수 : 컴파일 타임에 반영된다.
	FORCEINLINE void UpdateHPBar( float Cur , float Max )
	{
		HPBar->SetPercent( Cur / Max );
	}

	
};
