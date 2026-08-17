// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RubiksCube.generated.h"

UCLASS()
class PROJECTCPP_API ARubiksCube : public AActor
{
	GENERATED_BODY()

private:
	bool bIsRotating = false;
	FRotator StartRotation;
	FRotator TargetRotation;
	float RotationAlpha = 0.0f;      // 0 to 1 progress
	float RotationDuration = 0.25f;  // seconds per 90° turn	
public:	
	// Sets default values for this actor's properties
	ARubiksCube();

	UPROPERTY(EditAnywhere, Category = "Rubiks")
	TArray<int32> FaceAngles;

	UPROPERTY(VisibleAnywhere, Category = "Rubiks")
	UStaticMeshComponent* CubeMesh;

	void RotateFace(int32 FaceIndex);

	bool IsSolved();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



};
