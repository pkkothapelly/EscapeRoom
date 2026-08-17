// Fill out your copyright notice in the Description page of Project Settings.


#include "ARSessionManager.h"
#include "ARBlueprintLibrary.h"
#include "ARTrackable.h"
#include "RubiksCube.h"
#if PLATFORM_ANDROID
#include "AndroidPermissionFunctionLibrary.h"
#include "AndroidPermissionCallbackProxy.h"
#endif

ARSessionManager::ARSessionManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

ARSessionManager::~ARSessionManager()
{
}


void ARSessionManager::ConfigureSession()
{
    if (!SessionConfig)
    {
        UE_LOG(LogTemp, Warning, TEXT("ARSessionManager: No SessionConfig assigned!"));
        return;
    }

    // SessionConfig is now assigned in the editor — no NewObject needed.
    UE_LOG(LogTemp, Warning, TEXT("ARSessionManager: Starting session with assigned config."));
}

void ARSessionManager::StartSession() {

    UE_LOG(LogTemp, Warning, TEXT("StartSession called."));

    ConfigureSession();
    UARBlueprintLibrary::StartARSession(SessionConfig);

}

void ARSessionManager::ExitSession() {

    UARBlueprintLibrary::StopARSession();

}



void ARSessionManager::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("ARSessionManager BeginPlay running - about to handle permission."));

#if PLATFORM_ANDROID
    // On device: check if we already have camera permission.
    if (UAndroidPermissionFunctionLibrary::CheckPermission(TEXT("android.permission.CAMERA")))
    {
        StartSession();   // already granted (e.g. relaunch) — go straight in
    }
    else
    {
        // Ask for it. The answer comes back later, via our callback.
        TArray<FString> Permissions;
        Permissions.Add(TEXT("android.permission.CAMERA"));

        UAndroidPermissionCallbackProxy* Proxy =
            UAndroidPermissionFunctionLibrary::AcquirePermissions(Permissions);

        if (Proxy)
        {
            Proxy->OnPermissionsGrantedDelegate.AddUObject(
                this, &ARSessionManager::OnCameraPermissionDecided);
        }
    }
#else
    // In editor / on PC: no Android permissions exist, just start.
    StartSession();
#endif
}

void ARSessionManager::OnCameraPermissionDecided(
    const TArray<FString>& Permissions, const TArray<bool>& GrantResults)
{
    // The user has now answered the dialog.
    for (int32 i = 0; i < Permissions.Num(); i++)
    {
        if (Permissions[i] == TEXT("android.permission.CAMERA") &&
            GrantResults.IsValidIndex(i) && GrantResults[i])
        {
            UE_LOG(LogTemp, Warning, TEXT("Camera permission granted - starting AR session."));
            StartSession();   // NOW we start — permission is in hand
            return;
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Camera permission denied - AR cannot start."));
}

void ARSessionManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bCubeSpawned) { return; }   // already placed it — nothing to do

    // Ask AR for every image it's currently tracking
    TArray<UARTrackedImage*> TrackedImages =
        UARBlueprintLibrary::GetAllGeometriesByClass<UARTrackedImage>();

    for (UARTrackedImage* Image : TrackedImages)
    {
        if (!Image) { continue; }

        // Only act on solidly-tracked images, not lost/limited ones
        if (Image->GetTrackingState() != EARTrackingState::Tracking) { continue; }

        // The transform of the detected marker in the real world
        FTransform MarkerTransform = Image->GetLocalToWorldTransform();
        FVector MarkerLoc = MarkerTransform.GetLocation();
        UE_LOG(LogTemp, Warning, TEXT("Marker world location: X=%f Y=%f Z=%f"),
            MarkerLoc.X, MarkerLoc.Y, MarkerLoc.Z);

        if (CubeClass)
        {
            ARubiksCube* NewCube = GetWorld()->SpawnActor<ARubiksCube>(CubeClass, MarkerTransform);
            if (NewCube)
            {
                NewCube->SetActorScale3D(FVector(3.0f));   // tune this number
            }
            bCubeSpawned = true;
            
            UE_LOG(LogTemp, Warning, TEXT("Marker detected - cube spawned!"));
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green,
                    TEXT("Marker detected - cube spawned!"));
            }
        }

        break;   // one marker is enough
    }
}