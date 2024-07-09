// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooingGameMode.h"
#include "Kismet/GameplayStatics.h"

void AShooingGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySound2D( GetWorld() , BGM );
}
