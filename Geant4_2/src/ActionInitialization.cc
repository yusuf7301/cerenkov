#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"

ActionInitialization::ActionInitialization() : G4VUserActionInitialization() {}
ActionInitialization::~ActionInitialization() {}

void ActionInitialization::Build() const
{
  // Daha önce yazdığımız parçacık fırlatıcıyı sisteme kaydediyoruz
  SetUserAction(new PrimaryGeneratorAction);
}