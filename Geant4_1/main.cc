#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

int main(int argc, char** argv)
{
    // 1. Kullanıcı arayüzünü (GUI) başlat
    G4UIExecutive* ui = nullptr;
    if (argc == 1) ui = new G4UIExecutive(argc, argv);

    // 2. Run Manager'ı oluştur (Simülasyonun beyni)
    auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

    // 3. Zorunlu sınıfları Run Manager'a ata
    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new PhysicsList());
    runManager->SetUserInitialization(new ActionInitialization());

    // 4. Görselleştirme yöneticisini başlat
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    // 5. Kullanıcı arayüzünü çalıştır
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if (!ui) {
        // Makro modunda (batch mode) çalıştırma
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }
    else {
        // Etkileşimli modda çalıştırma
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    }

    // Belleği temizle
    delete visManager;
    delete runManager;

    return 0;
}