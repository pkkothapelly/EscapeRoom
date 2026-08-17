
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARBlueprintLibrary.h"
#include "ARTrackable.h"
#include "ARSessionManager.generated.h"




UCLASS()
class PROJECTCPP_API ARSessionManager : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "AR Session")
	UARSessionConfig* SessionConfig;
	ARSessionManager();
	~ARSessionManager();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "AR Session")
	TSubclassOf<class ARubiksCube> CubeClass;

	UFUNCTION()
	void OnCameraPermissionDecided(const TArray<FString>& Permissions, const TArray<bool>& GrantResults);

	virtual void Tick(float DeltaTime) override;

	

	void ConfigureSession();
	void StartSession();
	void ExitSession();

private:
	bool bCubeSpawned = false;
};
