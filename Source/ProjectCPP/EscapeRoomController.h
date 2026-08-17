// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EscapeRoomController.generated.h"

class UInputMappingContext;   // forward declaration
class UInputAction;

UCLASS()
class PROJECTCPP_API AEscapeRoomController : public APlayerController
{
    GENERATED_BODY()

public:
    // The mapping context asset (IMC_Default) — assigned in the editor.
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, Category="Input")
    UInputAction* TapAction;

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;
    void OnTap();
};