#include "MoveCommand.h"
#include "../GameGrid.h"  // Yol düzeltildi
#include "../UnitBase.h"  // Yol düzeltildi

MoveCommand::MoveCommand(FSGridPosition Src, FSGridPosition Dst) :
    Source(Src),
    Destination(Dst)
{
}

MoveCommand::~MoveCommand()
{
}

void MoveCommand::Execute()
{
    UE_LOG(LogTemp, Warning, TEXT("Executing MoveCommand..."));

    AGameSlot* SlotA = AGameGrid::FindSlot(Source);
    AGameSlot* SlotB = AGameGrid::FindSlot(Destination);

    if (SlotA && SlotB)
    {
        AUnitBase* UnitA = SlotA->Unit;
        if (UnitA)
        {
            UnitA->AssignToSlot(SlotB);
            SlotB->SetState(GS_Highlighted);
        }
    }
}

void MoveCommand::Revert()
{
    AGameSlot* SlotA = AGameGrid::FindSlot(Source);
    AGameSlot* SlotB = AGameGrid::FindSlot(Destination);

    if (SlotA && SlotB)
    {
        AUnitBase* UnitB = SlotB->Unit;
        if (UnitB)
        {
            UnitB->AssignToSlot(SlotA);
            SlotB->SetState(GS_Default);
        }
    }
}