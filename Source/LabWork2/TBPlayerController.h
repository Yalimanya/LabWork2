#pragma once

#include "CoreMinimal.h" //
#include "GameFramework/PlayerController.h" //
#include "TBPlayerController.generated.h" //

class AGameManager; //

UCLASS()
class LABWORK2_API ATBPlayerController : public APlayerController //
{
    GENERATED_BODY() //

public:
    ATBPlayerController(); //

    virtual void BeginPlay() override; //

    void OnActorClicked(AActor* Actor, FKey key); //

    UPROPERTY(BlueprintReadWrite) //
        AGameManager* GameManager; //
};