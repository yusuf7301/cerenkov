#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

// Geant4'te geometri tanımlamak için G4VUserDetectorConstruction'dan türetim yapılır [cite: 248]
class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    // Sistemin geometrisini döndüren ana fonksiyon [cite: 104]
    virtual G4VPhysicalVolume* Construct();
};

#endif