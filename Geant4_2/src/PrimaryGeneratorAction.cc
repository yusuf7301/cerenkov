#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
  : G4VUserPrimaryGeneratorAction()
{
  G4int n_particle = 1; // Her atışta 1 parçacık
  fParticleGun = new G4ParticleGun(n_particle);

  // Parçacık türünü seçiyoruz: geantino (hiçbir fiziksel etkileşim yapmaz)
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("geantino");

  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.)); // Z ekseninde ileri
  fParticleGun->SetParticleEnergy(1.0*GeV); // Enerji (etkileşim olmadığı için izi değiştirmez)
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // Parçacığın fırlatılacağı konum: Dünyanın biraz gerisi (Z = -50 cm)
  fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,-50.*cm));
  fParticleGun->GeneratePrimaryVertex(anEvent);
}