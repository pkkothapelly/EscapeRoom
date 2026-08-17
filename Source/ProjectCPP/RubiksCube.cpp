// Fill out your copyright notice in the Description page of Project Settings.


#include "RubiksCube.h"
#include "GameStateManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARubiksCube::ARubiksCube()
{
	PrimaryActorTick.bCanEverTick = true;

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	RootComponent = CubeMesh;

}
void ARubiksCube::RotateFace(int32 FaceIndex)
{
    if (!FaceAngles.IsValidIndex(FaceIndex)) { return; }
    if (bIsRotating) { return; }

    FaceAngles[FaceIndex] = (FaceAngles[FaceIndex] + 90) % 360;

    StartRotation = CubeMesh->GetRelativeRotation();
    FQuat StartQuat = CubeMesh->GetRelativeRotation().Quaternion();
    FQuat DeltaQuat = FRotator(0.0f, 90.0f, 0.0f).Quaternion();   // your working snap axis
    TargetRotation = (DeltaQuat * StartQuat).Rotator();
    RotationAlpha = 0.0f;
    bIsRotating = true;

    UE_LOG(LogTemp, Warning, TEXT("Face %d rotated to %d degrees"), FaceIndex, FaceAngles[FaceIndex]);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Cyan,
            FString::Printf(TEXT("Face rotated to %d degrees"), FaceAngles[FaceIndex]));
    }

    if (IsSolved())
    {
        AGameStateManager* Brain =
            Cast<AGameStateManager>(UGameplayStatics::GetGameMode(GetWorld()));
        if (Brain)
        {
            Brain->OnPuzzleSolved(0);
        }
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Yellow,
                TEXT("PUZZLE SOLVED!"));
        }

    }
   
}

void ARubiksCube::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bIsRotating) { return; }

    RotationAlpha += DeltaTime / RotationDuration;

    if (RotationAlpha >= 1.0f)
    {
        RotationAlpha = 1.0f;
        CubeMesh->SetRelativeRotation(TargetRotation);
        bIsRotating = false;
        return;
    }

    // smooth ease using the fixed start/target, not the live rotation
    FQuat Result = FQuat::Slerp(StartRotation.Quaternion(), TargetRotation.Quaternion(), RotationAlpha);
    CubeMesh->SetRelativeRotation(Result.Rotator());
}

void ARubiksCube::BeginPlay()
{
	Super::BeginPlay();
	FaceAngles.Init(0,6);

    CubeMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
}

bool ARubiksCube::IsSolved()
{
	for (int32 Angle : FaceAngles)
	{
		if (Angle!=0)
		{
			return false;
		}
	}
	return true;
}

