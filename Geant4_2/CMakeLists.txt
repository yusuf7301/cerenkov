# 1. En düşük CMake versiyonunu belirle
cmake_minimum_required(VERSION 3.16...3.27)

# 2. Proje adını tanımla
project(N01_Simulasyon)

# 3. Geant4 paketini bul (Görselleştirme ve UI desteğiyle birlikte)
find_package(Geant4 REQUIRED ui_all vis_all)

# 4. Geant4 ayarlarını dahil et
include(${Geant4_USE_FILE})

# 5. Başlık dosyalarının (.hh) olduğu dizini tara
include_directories(${PROJECT_SOURCE_DIR}/include)

# 6. Kaynak dosyalarını (.cc) listele
file(GLOB SOURCES src/*.cc sim.cc)

# 7. Çalıştırılabilir dosyayı oluştur
add_executable(sim ${SOURCES})

# 8. Geant4 kütüphanelerini projeye bağla
target_link_libraries(sim ${Geant4_LIBRARIES})

# 9. Derleme sonrası çalıştırılabilir dosyayı ana dizine kopyala (Opsiyonel)
set_target_properties(sim PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})