#pragma once

#include "CoreMinimal.h"
#include "Command.h"
#include "../GameSlot.h" // Yol düzeltildi

class MoveCommand : public Command
{
public:
    MoveCommand(FSGridPosition Src, FSGridPosition Dst);
    virtual ~MoveCommand() override; // Uyarıyı çözmek için virtual eklendi

    virtual void Execute() override;
    virtual void Revert() override;

private:
    FSGridPosition Source;
    FSGridPosition Destination;
};