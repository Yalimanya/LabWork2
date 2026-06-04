#include "GameManager.h" //
#include "TBPlayerController.h" //
#include "GameSlot.h" //
#include "MoveCommand.h"

AGameManager::AGameManager() //
{
    PrimaryActorTick.bCanEverTick = true; //
}

void AGameManager::BeginPlay() //
{
    Super::BeginPlay(); //

    if (auto PlayerController = Cast<ATBPlayerController>(GetWorld()->GetFirstPlayerController())) //
    {
        PlayerController->GameManager = this; //
    }

    if (Levels.IsValidIndex(CurrentLevel)) //
    {
        CreateLevelActors(Levels[CurrentLevel]); //
    }
}

void AGameManager::Tick(float DeltaTime) //
{
    Super::Tick(DeltaTime);

    if (CurrentCommand.IsValid()) {
        CurrentCommand->Update(DeltaTime);
    }
}

void AGameManager::CreateLevelActors(FSLevelInfo& Info) //
{
    ThePlayer = nullptr; //

    for (auto UnitInfo : Info.Units) //
    {
        if (AGameSlot* Slot = GameGrid->GetSlot(UnitInfo.StartPosition)) //
        {
            Slot->SpawnUnitHere(UnitInfo.UnitClass); //
            if (Slot->Unit && Slot->Unit->IsControlledByThePlayer()) //
            {
                ThePlayer = Slot->Unit; //
            }
        }
    }
}

void AGameManager::OnActorClicked(AActor* Actor, FKey button) //
{
    if (CurrentCommand.IsValid() && CurrentCommand->IsExecuting()) return;

    AGameSlot* Slot = Cast<AGameSlot>(Actor);
    if (!Slot) return;

    if (!ThePlayer) {
        UE_LOG(LogTemp, Error, TEXT("No Player Unit Detected!"));
        return;
    }

    // Boş bir slota tıklanmışsa oyuncu için MoveCommand oluştur
    if (Slot->Unit == nullptr)
    {
        TSharedRef<MoveCommand> Cmd = MakeShared<MoveCommand>(ThePlayer->Slot->GridPosition, Slot->GridPosition);
        CommandPool.Add(Cmd);
        Cmd->Execute();
        CurrentCommand = Cmd;
    }
}

bool AGameManager::UndoLastMove()
{
    // Eğer o anda çalışan bir animasyon/komut varsa işlemi reddet
    if (CurrentCommand.IsValid() && CurrentCommand->IsExecuting()) return false;

    if (CommandPool.Num() > 0)
    {
        // TArray.Pop() ile CommandPool'dan son komutu al ve havuzdan çıkar
        TSharedRef<Command> LastCmd = CommandPool.Pop();
        LastCmd->Revert(); // İşlemi geri al
        CurrentCommand = nullptr;
        return true;
    }

    return false; // Geri alınacak hamle kalmadıysa false döndür
}