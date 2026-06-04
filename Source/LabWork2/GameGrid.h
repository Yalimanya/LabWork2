#pragma once

#include "CoreMinimal.h" //
#include "GameFramework/Actor.h" //
#include "GameSlot.h" //
#include "GameGrid.generated.h" //

UCLASS()
class LABWORK2_API AGameGrid : public AActor //
{
    GENERATED_BODY() //

public:
    AGameGrid(); //
    virtual void OnConstruction(const FTransform& Transform) override; //

    UPROPERTY(EditAnywhere) //
        TSubclassOf<AGameSlot> GridClass; //

    UPROPERTY(EditAnywhere, BlueprintReadWrite) //
        int NumRows; //

    UPROPERTY(EditAnywhere, BlueprintReadWrite) //
        int NumCols; //

    UPROPERTY(VisibleAnywhere) //
        TArray<UChildActorComponent*> GridActors; //

    AGameSlot* GetSlot(FSGridPosition& Position); //
    static AGameSlot* FindSlot(FSGridPosition Position); //

protected:
    virtual void BeginPlay() override; //

private:
    static AGameGrid* GameGrid; //
};