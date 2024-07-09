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
	
};
