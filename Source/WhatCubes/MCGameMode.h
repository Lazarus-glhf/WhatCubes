// Fill out your copyright notice in the description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Chunk.h"
#include "MCGameMode.generated.h"

/**
 * %class
 */
UCLASS()
class WHATCUBES_API AMCGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

};
