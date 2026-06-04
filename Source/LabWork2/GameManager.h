#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameGrid.h"
#include "UnitBase.h"
#include "Command.h" 
#include "GameManager.generated.h" 

USTRUCT(BlueprintType)
struct FSUnitInfo
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere)
    TSubclassOf<AUnitBase> UnitClass;

    UPROPERTY(EditAnywhere)
    FSGridPosition StartPosition;
};

USTRUCT(BlueprintType)
struct FSLevelInfo
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere)
    TArray<FSUnitInfo> Units;
};

UCLASS()
class LABWORK2_API AGameManager : public AActor
{
    GENERATED_BODY()

public:
    AGameManager();

    void OnActorClicked(AActor* Actor, FKey button);
    void CreateLevelActors(FSLevelInfo& Info);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int CurrentLevel;

    UPROPERTY(EditAnywhere)
    TArray<FSLevelInfo> Levels;

    UPROPERTY(EditAnywhere)
    AGameGrid* GameGrid;

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // FONKSİYON SINIFIN İÇİNDE (BURADA) OLMALI!
    UFUNCTION(BlueprintCallable)
    bool UndoLastMove();

private:
    AUnitBase* ThePlayer;

    TArray<TSharedRef<Command>> CommandPool;
    TSharedPtr<Command> CurrentCommand;
};