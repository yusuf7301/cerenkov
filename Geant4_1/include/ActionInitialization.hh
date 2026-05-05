#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization();
    virtual ~ActionInitialization();

    // Hem seri hem de çok çekirdekli (multithreading) modda çalışması için gerekli
    virtual void Build() const;
};

#endif