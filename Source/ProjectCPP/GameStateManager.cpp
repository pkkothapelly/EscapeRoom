// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStateManager.h"
#include "EscapeRoomController.h"
#include "AREscapePawn.h"

AGameStateManager::AGameStateManager()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<APlayerController> ControllerBP(
		TEXT("/Game/Blueprints/BP_EscapeRoomController"));
	if (ControllerBP.Succeeded())
	{
		PlayerControllerClass = ControllerBP.Class;
	}

	DefaultPawnClass = AAREscapePawn::StaticClass();   // <-- add this
}

AGameStateManager::~AGameStateManager()
{
}

void AGameStateManager::BeginPlay()
{
	Super::BeginPlay();
	SetupGame();
	
}

void AGameStateManager::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
	UpdateTimer(DeltaTime);
}



void AGameStateManager::SetupGame() {
	TimeRemaining = 300.0f;
	PuzzleSolvedStates.Init(false, 4);
	CurrentPuzzleIndex = 0;
	bGameWon = false;
	bGameLost = false;
}

void AGameStateManager::UpdateTimer(float DeltaTime) {
	if (bGameWon || bGameLost) { return; }

	TimeRemaining -= DeltaTime ;
	//UE_LOG(LogTemp, Warning, TEXT("Time remaining: %f"), TimeRemaining);

	if (TimeRemaining <= 0.0f)
	{
		TimeRemaining = 0.0f;
		LoseGame();
	}
}

void AGameStateManager::LoseGame(){

	bGameLost = true;
	UE_LOG(LogTemp, Warning, TEXT("GAME OVER - time ran out."));
}

void AGameStateManager::OnPuzzleSolved(int32 PuzzleIndex) {

	if (bGameWon || bGameLost) { return; }

	if (!PuzzleSolvedStates.IsValidIndex(PuzzleIndex)) {

		UE_LOG(LogTemp, Warning, TEXT("OnPuzzleSolved: invalid index %d"), PuzzleIndex);

		return;

	}

	PuzzleSolvedStates[PuzzleIndex] = true;
	CurrentPuzzleIndex++;

	UE_LOG(LogTemp, Warning, TEXT("Puzzle %d Solved."), PuzzleIndex);

	if (CheckAllPuzzlesSolved()) {

		WinGame();

	}

}

bool AGameStateManager::CheckAllPuzzlesSolved() {

	for (bool bSolved : PuzzleSolvedStates)
	if(!bSolved){
		
		return false;
	}
	return true;
}

void AGameStateManager::WinGame() {

	bGameWon = true;
	UE_LOG(LogTemp, Warning, TEXT("YOU ESCAPED - all puzzles solved!"));
}
