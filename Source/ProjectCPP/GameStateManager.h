// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameStateManager.generated.h"

/**
 * 
 */

UCLASS()

class PROJECTCPP_API AGameStateManager : public AGameModeBase
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Game State")
	float TimeRemaining;

	UPROPERTY(EditAnywhere, Category = "Game State")
	TArray<bool> PuzzleSolvedStates;

	UPROPERTY(EditAnywhere, Category = "Game State")
	int32 CurrentPuzzleIndex;

	UPROPERTY(EditAnywhere, Category = "Game State")
	bool bGameWon;

	UPROPERTY(EditAnywhere, Category = "Game State")
	bool bGameLost;

	
	void SetupGame();
	void UpdateTimer(float DeltaTime);
	void OnPuzzleSolved(int32 PuzzleIndex);
	bool CheckAllPuzzlesSolved();
	void WinGame();
	void LoseGame();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;



	AGameStateManager();
	~AGameStateManager();

	

	


};
