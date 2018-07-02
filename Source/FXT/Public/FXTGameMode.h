// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FXTGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FXT_API AFXTGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFXTGameMode();
	
protected:
	virtual void BeginPlay() override;
	
	
};
