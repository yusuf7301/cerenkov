#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4RandomTools.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // Varsayılan parçacık: Müon (Kozmik ışınların en yaygın bileşeni)
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("mu-");
  fParticleGun->SetParticleDefinition(particle);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // -----------------------------------------------------------------
  // 1. Rastgele AGN Türü ve Enerji Spektrumu Simülasyonu (Etiketimiz)
  // -----------------------------------------------------------------
  // G4UniformRand() 0.0 ile 1.0 arasında rastgele sayı üretir.
  // 3.0 ile çarpıp tam sayıya cast ederek kesin olarak 0, 1 veya 2 elde ederiz.
  G4int agnType = (G4int)(G4UniformRand() * 3.0); 
  if (agnType > 2) agnType = 2; // Sınır güvenliği

  G4double energy = 0.0;

  if(agnType == 0) {
      // Blazar: Yüksek enerjili spektrum (5 GeV - 20 GeV arası)
      energy = (5.0 + G4UniformRand() * 15.0) * GeV;
  } else if(agnType == 1) {
      // Seyfert: Orta enerjili spektrum (1 GeV - 5 GeV arası)
      energy = (1.0 + G4UniformRand() * 4.0) * GeV;
  } else {
      // Radyo Galaksi: Düşük enerjili spektrum (200 MeV - 1 GeV arası)
      energy = (0.2 + G4UniformRand() * 0.8) * GeV;
  }
  fParticleGun->SetParticleEnergy(energy);

  // -----------------------------------------------------------------
  // 2. Rastgele Konum ve Açı (Giriş Koordinatları)
  // -----------------------------------------------------------------
  // -70.0 ile +70.0 cm arasında rastgele X ve Y koordinatları
  G4double randX = (-70.0 + G4UniformRand() * 140.0) * cm;
  G4double randY = (-70.0 + G4UniformRand() * 140.0) * cm;
  G4double randZ = -60.0 * cm; // Tankın üst çatısının hemen üzeri
  
  fParticleGun->SetParticlePosition(G4ThreeVector(randX, randY, randZ));

  // Rastgele doğrultu (Açı): X ve Y eksenlerinde hafif sapmalar (-0.3 ile +0.3 arası)
  G4double dirX = -0.3 + G4UniformRand() * 0.6;
  G4double dirY = -0.3 + G4UniformRand() * 0.6;
  G4double dirZ = 1.0; // Aşağı doğru hareket
  
  G4ThreeVector direction(dirX, dirY, dirZ);
  fParticleGun->SetParticleMomentumDirection(direction.unit()); // Vektörü normalize et

  // -----------------------------------------------------------------
  // 3. Yapay Zeka İçin Gerçek Değerleri (Etiketleri) Geant4 Loguna Yazma
  // -----------------------------------------------------------------
  G4cout << "[DATA_TRUE] " 
         << agnType << " " 
         << energy/GeV << " "
         << randX/cm << " " 
         << randY/cm << " " 
         << direction.unit().x() << " " 
         << direction.unit().y() << " " 
         << G4endl;

  fParticleGun->GeneratePrimaryVertex(anEvent);
}