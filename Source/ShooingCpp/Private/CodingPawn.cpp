// Fill out your copyright notice in the Description page of Project Settings.


#include "CodingPawn.h"

// Sets default values
ACodingPawn::ACodingPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACodingPawn::BeginPlay()
{
	Super::BeginPlay();
	
	//// 반복문

	////배열
	//TArray<int32> ar;
	//ar.Empty( 10 );
	//ar.Add( 10 );
	//ar.Add( 11 );
	//ar.Add( 12 );
	//if (false == ar.Contains( 10 ))	// 10을 이미 포함하고 있지 않다면
	//{
	//	ar.Add( 10 );		// 10을 추가하고싶다.
	//}

	//ar.Num();	// Add한 갯수가 몇개인가?
	//ar.GetSlack();// 메모리공간을 몇개 할당 받았는가?

	//for (int32 i = 0; i < ar.Num(); i++)
	//{
	//	UE_LOG( LogTemp , Warning , TEXT( "%d" ) , ar[i] );
	//}

	//// for each
	//for (int32 item : ar)
	//{
	//	UE_LOG( LogTemp , Warning , TEXT( "%d" ) , item );
	//}

	//TMap<FString, int32> map;

	//map.Add( "Coin" , 10 );
	//if (false == map.Contains( "Coin" ))
	//{
	//	map.Add( "Coin" , 20 );
	//}
	//else {
	//	map["Coin"] = 20;
	//}

	//UE_LOG( LogTemp , Warning , TEXT( "%d" ) , map["Coin"] );

	//for (TPair<FString , int32> pair : map)
	//{
	//	UE_LOG( LogTemp , Warning , TEXT( "%d" ) , pair.Value );
	//}



	//// 조건문

	//switch (Number)
	//{
	//case 1:
	//	break;

	//case 2:
	//	break;

	//default:
	//	break;
	//}

	//if (Number < 10)
	//{

	//}
	//else if (Number < 20)
	//{

	//}
	//else {

	//}




	//UE_LOG( LogTemp , Warning , TEXT( "%d" ) , Number );
	//UE_LOG( LogTemp , Warning , TEXT( "%.2f" ) , Distance );
	//UE_LOG( LogTemp , Warning , TEXT( "%d" ) , bGood );

	//UE_LOG( LogTemp , Warning , TEXT( "%s" ) , *MyName );



	//// 헬로 월드
	////UE_LOG(LogTemp, Warning, TEXT("Hello World"));

	////GEngine->AddOnScreenDebugMessage(0, 10, FColor::Cyan, TEXT("Hello World"));




}

// Called every frame
void ACodingPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ACodingPawn::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );

}

int32 ACodingPawn::MyAddCallable( int32 a , int32 b )
{
	return a + b;
}

int32 ACodingPawn::MyAddPure( int32 a , int32 b )
{
	return a + b;
}

int32 ACodingPawn::MyAddNativeEvent_Implementation( int32 a , int32 b )
{
	return a + b;
}

