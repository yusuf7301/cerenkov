#include "EventAction.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

EventAction::EventAction()
: G4UserEventAction(), fPhotonCount(0), fSumX(0.), fSumY(0.), fSumZ(0.)
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{
  // Her yeni parçacıkta kumbarayı sıfırla
  fPhotonCount = 0;
  fSumX = 0.0;
  fSumY = 0.0;
  fSumZ = 0.0;
}

void EventAction::EndOfEventAction(const G4Event*)
{
  // Fotonların tank içindeki ortalama üretim koordinatlarını (ağırlık merkezini) hesapla
  G4double avgX = 0.0;
  G4double avgY = 0.0;
  G4double avgZ = 0.0;

  if (fPhotonCount > 0) {
    avgX = fSumX / fPhotonCount;
    avgY = fSumY / fPhotonCount;
    avgZ = fSumZ / fPhotonCount;
  }

  // ML MODELİNİN OKUYACAĞI GİRDİ VERİLERİ (Terminale Yazdırılıyor)
  // Format: [DATA_PRED] FotonSayısı OrtalamaX OrtalamaY OrtalamaZ
  G4cout << "[DATA_PRED] " 
         << fPhotonCount << " " 
         << avgX/cm << " " 
         << avgY/cm << " " 
         << avgZ/cm << " " 
         << G4endl;
}