#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4MaterialPropertiesTable.hh"

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction() {}
DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4NistManager* nist = G4NistManager::Instance();

    // 1. DÜNYA TANIMLAMA (Hava)
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
    G4Box* solidWorld = new G4Box("World", 1.0*m, 1.0*m, 1.0*m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0);

    // 2. SU VE OPTİK ÖZELLİKLER
    G4Material* water = nist->FindOrBuildMaterial("G4_WATER");

    // Enerji aralığı (foton enerjisi olarak: 2.0 eV - 5.17 eV arası görünür ışık civarı)
    G4double energy[] = {2.034*eV, 4.136*eV};
    G4double rindexWater[] = {1.333, 1.333}; // Kırılma indisi 
    G4double absorption[] = {100.0*m, 100.0*m}; // Soğurulma boyu 

    G4MaterialPropertiesTable* mptWater = new G4MaterialPropertiesTable();
    mptWater->AddProperty("RINDEX", energy, rindexWater, 2);
    mptWater->AddProperty("ABSLENGTH", energy, absorption, 2);
    
    water->SetMaterialPropertiesTable(mptWater);

    // 3. HEDEF SİLİNDİR (Su Tankı)
    G4Tubs* solidTarget = new G4Tubs("Target", 0, 20*cm, 30*cm, 0*deg, 360*deg);
    G4LogicalVolume* logicTarget = new G4LogicalVolume(solidTarget, water, "Target");
    new G4PVPlacement(0, G4ThreeVector(), logicTarget, "Target", logicWorld, false, 0);

    return physWorld;
}