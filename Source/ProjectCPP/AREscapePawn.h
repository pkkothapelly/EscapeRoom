#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AREscapePawn.generated.h"

UCLASS()
class PROJECTCPP_API AAREscapePawn : public APawn
{
    GENERATED_BODY()

public:
    AAREscapePawn();

    UPROPERTY(VisibleAnywhere, Category = "AR")
    class UCameraComponent* ARCamera;
};