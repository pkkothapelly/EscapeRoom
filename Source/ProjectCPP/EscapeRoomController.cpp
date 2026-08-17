// Fill out your copyright notice in the Description page of Project Settings.


#include "EscapeRoomController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "RubiksCube.h"

void AEscapeRoomController::BeginPlay()

{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);

			UE_LOG(LogTemp, Warning, TEXT("EscapeRoomController active - mapping context added."));
		}
	}

}

void AEscapeRoomController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInput =
		Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (TapAction)
		{
			EnhancedInput->BindAction(TapAction, ETriggerEvent::Started, this, &AEscapeRoomController::OnTap);
		}
	}


}

void AEscapeRoomController::OnTap()
{
	UE_LOG(LogTemp, Warning, TEXT("OnTap fired"));
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		if (ARubiksCube* Cube = Cast<ARubiksCube>(Hit.GetActor()))
		{
			Cube->RotateFace(0);   // for now, always rotate face 0
		}
	}
}

