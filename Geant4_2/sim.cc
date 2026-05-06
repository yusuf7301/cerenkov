#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "QBBC.hh" // Standart fizik listesi

int main(int argc, char** argv)
{
    // 1. Run Manager oluşturma
    auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

    // 2. Zorunlu sınıfları sisteme tanıtma
    runManager->SetUserInitialization(new DetectorConstruction()); // Geometri [cite: 277]
    runManager->SetUserInitialization(new QBBC);                  // Fizik [cite: 577]
    runManager->SetUserInitialization(new ActionInitialization()); // Eylemler

    // 3. Görselleştirme ve Arayüz
    G4UIExecutive* ui = nullptr;
    if (argc == 1) ui = new G4UIExecutive(argc, argv); // Komut satırı yoksa GUI aç

    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    // 4. Kullanıcı komutlarını dinlemeye başla
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    
    if (ui) {
        // Otomatik görselleştirme komutlarını çalıştır [cite: 279, 406]
        UImanager->ApplyCommand("/vis/open OGL");
        UImanager->ApplyCommand("/vis/drawVolume");
        UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
        ui->SessionStart();
        delete ui;
    }

    delete visManager;
    delete runManager;
    return 0;
}