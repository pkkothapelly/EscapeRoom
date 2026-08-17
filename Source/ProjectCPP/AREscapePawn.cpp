#include "AREscapePawn.h"
#include "Camera/CameraComponent.h"

AAREscapePawn::AAREscapePawn()
{
    PrimaryActorTick.bCanEverTick = false;

    ARCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ARCamera"));
    RootComponent = ARCamera;

    // AR drives the camera from device tracking, so the pawn itself
    // shouldn't try to use control rotation or auto-possess movement.
    AutoPossessPlayer = EAutoReceiveInput::Player0;
}