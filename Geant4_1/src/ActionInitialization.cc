#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"

ActionInitialization::ActionInitialization() : G4VUserActionInitialization() {}
ActionInitialization::~ActionInitialization() {}

void ActionInitialization::Build() const
{
    // Hazırladığımız parçacık tabancasını sisteme tanıtıyoruz
    SetUserAction(new PrimaryGeneratorAction);
}