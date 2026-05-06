#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();    
    virtual ~PrimaryGeneratorAction();

    // Her olayda (event) parçacık fırlatmak için gereken ana fonksiyon
    virtual void GeneratePrimaries(G4Event*);

  private:
    G4ParticleGun* fParticleGun; // Parçacık tabancası nesnesi
};

#endif