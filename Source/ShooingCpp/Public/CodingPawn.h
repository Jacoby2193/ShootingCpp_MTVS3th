// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CodingPawn.generated.h"

// 전방선언 
class UStaticMeshComponent;

UCLASS()
class SHOOINGCPP_API ACodingPawn : public APawn
{
	GENERATED_BODY()

public:
	//기본 생성자
	ACodingPawn();	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	// 자료형과 변수
	// 정수형, 실수형, 논리형, 문자열
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MyVar)
	int32 Number = 11;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyVar)
	float Distance = 3.14f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyVar)
	bool bGood = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyVar)
	FString MyName  = TEXT("이영훈");

	UFUNCTION(BlueprintCallable)
	int32 MyAddCallable( int32 a , int32 b );

	UFUNCTION(BlueprintPure)
	int32 MyAddPure( int32 a , int32 b );

	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent)
	int32 MyAddImplementableEvent( int32 a , int32 b );

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent)
	int32 MyAddNativeEvent( int32 a , int32 b );
};
