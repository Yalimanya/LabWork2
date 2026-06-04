#include "GameSlot.h" //
#include "UnitBase.h" //
#include "TBPlayerController.h"

AGameSlot::AGameSlot() //
{
    PrimaryActorTick.bCanEverTick = true; //

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); //

    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box")); //
    Box->SetupAttachment(RootComponent); //
    Box->SetBoxExtent(FVector(50, 50, 2)); //
    Box->SetCollisionResponseToAllChannels(ECR_Block); //

    Plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane")); //
    Plane->SetupAttachment(RootComponent); //

    static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultSlotMesh(TEXT("/Engine/BasicShapes/Plane")); //
    if (DefaultSlotMesh.Succeeded())
    {
        Plane->SetStaticMesh(DefaultSlotMesh.Object); //
    }

    SetState(GS_Default);
}

void AGameSlot::BeginPlay() //
{
    Super::BeginPlay(); //
    
    OnClicked.AddUniqueDynamic(this, &AGameSlot::OnGridClicked);
}

void AGameSlot::SetState(EGridState NewState) //
{
    GridState = NewState; //

    static ConstructorHelpers::FObjectFinder<UMaterialInterface> DefaultSlotMaterial(TEXT("Material'/Game/Materials/MAT_GridSlot.MAT_GridSlot'")); //
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> DefaultSlotMaterial_H(TEXT("MaterialInstanceConstant'/Game/Materials/MAT_GridSlot_Highlighted.MAT_GridSlot_Highlighted'")); //
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> DefaultSlotMaterial_O(TEXT("MaterialInstanceConstant'/Game/Materials/MAT_GridSlot_Offensive.MAT_GridSlot_Offensive'")); //
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> DefaultSlotMaterial_S(TEXT("MaterialInstanceConstant'/Game/Materials/MAT_GridSlot_Supportive.MAT_GridSlot_Supportive'")); //

    switch (NewState) //
    {
    case GS_Default: //
        if (DefaultSlotMaterial.Succeeded()) Plane->SetMaterial(0, DefaultSlotMaterial.Object); //
        break;
    case GS_Highlighted: //
        if (DefaultSlotMaterial_H.Succeeded()) Plane->SetMaterial(0, DefaultSlotMaterial_H.Object); //
        break;
    case GS_Offensive: //
        if (DefaultSlotMaterial_O.Succeeded()) Plane->SetMaterial(0, DefaultSlotMaterial_O.Object); //
        break;
    case GS_Supportive: //
        if (DefaultSlotMaterial_S.Succeeded()) Plane->SetMaterial(0, DefaultSlotMaterial_S.Object); //
        break;
    }
}

void AGameSlot::SpawnUnitHere(TSubclassOf<AUnitBase>& UnitClass) //
{
    FVector Location = GetActorLocation(); //
    AUnitBase* NewUnit = Cast<AUnitBase>(GetWorld()->SpawnActor(UnitClass, &Location)); //

    if (NewUnit) NewUnit->AssignToSlot(this); //
}

void AGameSlot::OnGridClicked(AActor* TouchedActor, FKey ButtonPressed) //
{
    if (auto PlayerController = Cast<ATBPlayerController>(GetWorld()->GetFirstPlayerController())) //
    {
        PlayerController->OnActorClicked(this, ButtonPressed); //
    }
}