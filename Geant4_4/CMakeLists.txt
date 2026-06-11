cmake_minimum_required(VERSION 3.16...3.26)
project(CherenkovSim)

# Geant4 paketini ve gerekli modülleri bul
find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})

# Başlık (Header) dosyalarının yollarını derleyiciye göster
include_directories(${PROJECT_SOURCE_DIR}/include ${Geant4_INCLUDE_DIRS})

# Sol paneldeki gerçek dosya isimlerinle birebir eşitledik (Steppin ve Contruction)
set(SOURCES
    sim.cc
    src/DetectorContruction.cc
    src/ActionInitialization.cc
    src/PrimaryGeneratorAction.cc
    src/EventAction.cc
    src/SteppinAction.cc
)

# Ana yürütülebilir dosyayı kaynak kodlarla bağla
add_executable(sim ${SOURCES})
target_link_libraries(sim ${Geant4_LIBRARIES})

# Derlenen dosyayı ana dizine yükle
install(TARGETS sim DESTINATION ${PROJECT_SOURCE_DIR})