#include "PrimaryGeneratorAction.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction() {
    // 1 adet parçacık fırlatacak tabancayı oluştur
    fParticleGun = new G4ParticleGun(1);

    // Parçacık tipini seç (Muonlar Cherenkov halkası için çok temiz iz bırakır)
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("mu-");
    fParticleGun->SetParticleDefinition(particle);

    // Parçacığın gidiş yönünü (Z ekseni boyunca ileri) ayarla
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));

    // Parçacığın enerjisini ayarla (1 GeV oldukça yüksek bir hız demektir)
    fParticleGun->SetParticleEnergy(1.0*GeV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    // Parçacığın başlangıç pozisyonunu (Z = -25 cm, yani tankın biraz dışı) ayarla
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -25.*cm));
    
    // Tabancayı ateşle!
    fParticleGun->GeneratePrimaryVertex(anEvent);
}