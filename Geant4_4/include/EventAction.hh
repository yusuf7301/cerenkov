#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class EventAction : public G4UserEventAction
{
  public:
    EventAction();
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

    // SteppingAction'dan veri almak için fonksiyonlar
    void AddPhoton() { fPhotonCount++; }
    void AddPhotonPosition(G4double x, G4double y, G4double z) {
        fSumX += x;
        fSumY += y;
        fSumZ += z;
    }

  private:
    G4int    fPhotonCount;
    G4double fSumX;
    G4double fSumY;
    G4double fSumZ;
};

#endif