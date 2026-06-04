#pragma once

#include "CoreMinimal.h" //
#include "GameFramework/Actor.h" //
#include "Components/BoxComponent.h" //
#include "GameSlot.generated.h" //

UENUM(Blueprintable)
enum EGridState //
{
    GS_Default, //
    GS_Highlighted, //
    GS_Offensive, //
    GS_Supportive, //
};

USTRUCT(Blueprintable)
struct FSGridPosition //
{
    GENERATED_USTRUCT_BODY() //

        UPROPERTY(EditAnywhere, BlueprintReadWrite) //
        uint8 Col; //

    UPROPERTY(EditAnywhere, BlueprintReadWrite) //
        uint8 Row; //

    FSGridPosition() {} //
    FSGridPosition(int col, int row) : Col(col), Row(row) {} //
};

UCLASS()
class LABWORK2_API AGameSlot : public AActor //
{
    GENERATED_BODY() //

public:
    AGameSlot(); //

    UPROPERTY(EditAnywhere) //
        UBoxComponent* Box; //

    UPROPERTY(EditAnywhere) //
        UStaticMeshComponent* Plane; //

    UPROPERTY(BlueprintReadWrite) //
        FSGridPosition GridPosition; //

    EGridState GridState; //

    UPROPERTY(VisibleAnywhere) //
        class AUnitBase* Unit; //

    UFUNCTION() //
        void SetState(EGridState NewState); //

    UFUNCTION() //
        void OnGridClicked(AActor* TouchedActor, FKey ButtonPressed); //

    void SpawnUnitHere(TSubclassOf<class AUnitBase>& UnitClass); //

protected:
    virtual void BeginPlay() override; //
};