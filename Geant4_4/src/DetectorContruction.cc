#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4Element.hh"
#include "G4Material.hh"

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{  
  G4NistManager* nist = G4NistManager::Instance();
  
  // -------------------------------------------------------------
  // 1. Temel Materyaller ve Elementler
  // -------------------------------------------------------------
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* al_mat    = nist->FindOrBuildMaterial("G4_Al");
  G4Material* pure_water = nist->FindOrBuildMaterial("G4_WATER");
  
  // Gadalyum Elementini Tanımlama (Nötron yakalama için)
  G4Element* Gd = nist->FindOrBuildElement("Gd");

  // -------------------------------------------------------------
  // 2. %0.1 Gadalyumlu Su Karışımının Oluşturulması (Gd-Doped Water)
  // -------------------------------------------------------------
  G4double gd_fraction = 0.1 * perCent; // Ağırlıkça %0.1 oranında Gd
  G4double water_fraction = 1.0 - gd_fraction;
  
  // Karışımın Yoğunluğu (Yaklaşık olarak su ile aynı kabul edilir)
  G4double gd_water_density = 1.0 * g/cm3; 
  
  G4Material* GdWater = new G4Material("GdWater", gd_water_density, 2);
  GdWater->AddMaterial(pure_water, water_fraction);
  GdWater->AddElement(Gd, gd_fraction);

  // -------------------------------------------------------------
  // 3. Optik Özellikler Tablosu (Cherenkov Işıması için Şart!)
  // -------------------------------------------------------------
  G4double photonEnergy[] = {2.0*eV, 4.0*eV};
  const G4int nEntries = sizeof(photonEnergy)/sizeof(G4double);

  // Gadalyumlu suyun kırılma indisi saf suya çok yakındır
  G4double waterRIndex[]  = {1.333, 1.333};
  G4double waterAbsorb[]  = {40.0*m, 40.0*m}; // Gd eklenmesi absorpsiyonu hafifçe artırabilir

  G4MaterialPropertiesTable* waterMPT = new G4MaterialPropertiesTable();
  waterMPT->AddProperty("RINDEX", photonEnergy, waterRIndex, nEntries);
  waterMPT->AddProperty("ABSLENGTH", photonEnergy, waterAbsorb, nEntries);
  
  // Optik özellikleri yeni hazırladığımız Gadalyumlu suya tanımlıyoruz
  GdWater->SetMaterialPropertiesTable(waterMPT);

  // -------------------------------------------------------------
  // 4. 1 Tonluk Yeni Tank Geometrisi (İç Hacim ~ 1 m3)
  // -------------------------------------------------------------
  // Dünya boyutunu tank büyüdüğü için 3 metreye çıkarıyoruz
  G4double world_size = 3.0*m;
  
  G4Box* solidWorld = new G4Box("World", 0.5*world_size, 0.5*world_size, 0.5*world_size);
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
  G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, true);

  // 1 Tonluk Alüminyum Dış Gövde Boyutları
  G4double tankRadius = 55.0*cm;  // Yarıçap r = 55 cm
  G4double tankHeight = 105.0*cm; // Yükseklik h = 105 cm
  G4double thickness  = 1.0*cm;   // Basınca dayanması için alüminyum duvarı 1 cm yaptık

  G4Tubs* solidAlTank = new G4Tubs("AlTank", 0, tankRadius + thickness, 0.5*tankHeight + thickness, 0*deg, 360*deg);
  G4LogicalVolume* logicAlTank = new G4LogicalVolume(solidAlTank, al_mat, "AlTank");
  new G4PVPlacement(0, G4ThreeVector(0,0,0), logicAlTank, "AlTank", logicWorld, false, 0, true);

  // İçindeki Gadalyumlu Su Hacmi (Water Tank)
  G4Tubs* solidWaterTank = new G4Tubs("WaterTank", 0, tankRadius, 0.5*tankHeight, 0*deg, 360*deg);
  
  // Burada materyal olarak yukarıda ürettiğimiz "GdWater" kütüphanesini bağlıyoruz:
  G4LogicalVolume* logicWaterTank = new G4LogicalVolume(solidWaterTank, GdWater, "WaterTank");
  
  new G4PVPlacement(0, G4ThreeVector(0,0,0), logicWaterTank, "WaterTank", logicAlTank, false, 0, true);

  return physWorld;
}