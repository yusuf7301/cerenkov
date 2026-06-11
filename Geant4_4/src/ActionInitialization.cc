#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "EventAction.hh"   // Yeni eklendi
#include "SteppinAction.hh" // Yeni eklendi

ActionInitialization::ActionInitialization()
: G4VUserActionInitialization()
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::BuildForMaster() const
{
  // Multithreading için gerekirse
}

void ActionInitialization::Build() const
{
  // 1. Parçacık tabancasını ata
  SetUserAction(new PrimaryGeneratorAction);

  // 2. EventAction (Kumbara) oluştur ve ata
  EventAction* eventAction = new EventAction();
  SetUserAction(eventAction);

  // 3. SteppingAction (Dedektif) oluştur ve kumbarayı ona bağla
  SetUserAction(new SteppingAction(eventAction));
}