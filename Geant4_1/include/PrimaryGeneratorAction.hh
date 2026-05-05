#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();

    // Her olay (event) başında parçacığı fırlatan fonksiyon
    virtual void GeneratePrimaries(G4Event*);

  private:
    G4ParticleGun* fParticleGun; // Geant4'ün temel tabancası
};

#endif