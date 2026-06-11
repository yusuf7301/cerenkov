#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4PhysListFactory.hh"
#include "G4OpticalPhysics.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

int main(int argc, char** argv)
{
    // Otomatik UI (Arayüz) seçimi
    G4UIExecutive* ui = nullptr;
    if ( argc == 1 ) {
        ui = new G4UIExecutive(argc, argv);
    }

    // Run Manager oluşturulması
    auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

    // 1. Geometri ve Malzeme Tanımlaması (1 Tonluk Gd'lu Tank)
    runManager->SetUserInitialization(new DetectorConstruction());

    // 2. Fizik Listesi Tanımlaması ve Optik Fizik Entegrasyonu
    G4PhysListFactory factory;
    G4VModularPhysicsList* physicsList = factory.GetReferencePhysList("FTFP_BERT");
    physicsList->RegisterPhysics(new G4OpticalPhysics());
    runManager->SetUserInitialization(physicsList);

    // 3. Kullanıcı Aksiyonları (PrimaryGenerator, Event ve Stepping bağları burada tetikleniyor)
    runManager->SetUserInitialization(new ActionInitialization());

    // Görselleştirme Yöneticisi
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if ( ! ui ) {
        // Makro modu (Veri üretimi için terminal modu)
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }
    else {
        // İnteraktif görsel mod
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    }

    // Bellek temizliği
    delete visManager;
    delete runManager;
    return 0;
}