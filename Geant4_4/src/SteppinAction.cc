#include "SteppinAction.hh"
#include "EventAction.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"

SteppingAction::SteppingAction(EventAction* eventAction)
: G4UserSteppingAction(), fEventAction(eventAction)
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  G4Track* track = step->GetTrack();
  
  // Sadece yeni doğan Cherenkov fotonlarını yakalayıp kumbaraya atıyoruz
  if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
    if (track->GetCurrentStepNumber() == 1) {
      fEventAction->AddPhoton();
      
      G4ThreeVector pos = step->GetPreStepPoint()->GetPosition();
      fEventAction->AddPhotonPosition(pos.x(), pos.y(), pos.z());
    }
  }
}