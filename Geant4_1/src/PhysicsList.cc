#include "PhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4SystemOfUnits.hh"

PhysicsList::PhysicsList() : G4VModularPhysicsList() {
    defaultCutValue = 0.7*mm;

    // 1. Standart EM Fiziği Kaydet
    RegisterPhysics(new G4EmStandardPhysics());

    // 2. Parçacık Bozunma Fiziğini Kaydet
    RegisterPhysics(new G4DecayPhysics());

    // 3. Optik Fiziği Kaydet (Cherenkov burada otomatik tetiklenir)
    G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
    RegisterPhysics(opticalPhysics);
}

PhysicsList::~PhysicsList() {}

void PhysicsList::SetCuts() {
    // Tüm parçacıklar için varsayılan kesme değerlerini uygula
    SetCutsWithDefault();
}