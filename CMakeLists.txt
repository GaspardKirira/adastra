cmake_minimum_required(VERSION 3.10)

# Déclaration du projet
project(Adastra)

# Définir la version de C++
set(CMAKE_CXX_STANDARD 20)

# Ajouter le répertoire "include" pour les fichiers d'en-tête
include_directories(include)

# Ajouter tous les fichiers sources du répertoire src
file(GLOB SOURCES "src/*.cpp")

# Créer une bibliothèque partagée à partir de tous les fichiers source trouvés dans src/
add_library(adastra SHARED ${SOURCES})

# Installer la bibliothèque dans le répertoire 'libs'
install(TARGETS adastra DESTINATION /home/softadastra/adastra/libs)

# Installer les fichiers d'en-tête dans le répertoire 'include'
install(DIRECTORY include/ DESTINATION /home/softadastra/adastra/include)
