// Fill out your copyright notice in the Description page of Project Settings.

#include "FXTGameMode.h"

AFXTGameMode::AFXTGameMode()
{

}

void AFXTGameMode::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *GetActorLabel());


}
