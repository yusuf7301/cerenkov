#include "DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction() {}
DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // 1. Materyal Tanımlama (NIST veritabanı kullanılarak) [cite: 248]
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* aluminum = nist->FindOrBuildMaterial("G4_Al");

    // 2. DÜNYA HACMİ (World Volume): Diğer tüm nesnelerin içinde bulunduğu kutu [cite: 108, 200]
    G4double world_size = 1.0*m;
    G4Box* solidWorld = new G4Box("World", world_size, world_size, world_size);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, air, "World");
    
    // Dünyayı sisteme yerleştiriyoruz (PhysWorld döndürülmelidir) [cite: 104, 250]
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0);

    // 3. HEDEF NESNE (Örn: Alüminyum bir silindir)
    G4Tubs* solidCylinder = new G4Tubs("Cylinder", 0, 10*cm, 20*cm, 0*deg, 360*deg);
    G4LogicalVolume* logicCylinder = new G4LogicalVolume(solidCylinder, aluminum, "Cylinder");
    
    // Nesneyi Dünyanın (logicWorld) içine yerleştiriyoruz [cite: 256]
    new G4PVPlacement(0, G4ThreeVector(0,0,0), logicCylinder, "Cylinder", logicWorld, false, 0);

    return physWorld; // Geometri motoru bu hacmi referans alır [cite: 104, 212]
}