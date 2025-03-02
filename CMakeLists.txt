cmake_minimum_required(VERSION 3.10)

# Déclaration du projet
project(Adastra)

# Définir la version de C++
set(CMAKE_CXX_STANDARD 17)

# Ajouter le répertoire "include" pour les fichiers d'en-tête
include_directories(include)

# Ajouter explicitement le répertoire d'en-têtes de MySQL Connector/C++
include_directories(/usr/include)  # Modifiez ici le chemin en fonction de l'emplacement réel du fichier mysql_driver.h

# Ajouter tous les fichiers sources du répertoire src
file(GLOB SOURCES "src/*.cpp")

# Créer une bibliothèque partagée à partir de tous les fichiers source trouvés dans src/
add_library(adastra SHARED ${SOURCES})

# Lier MySQL Connector/C++ (la bibliothèque libmysqlcppconn)
target_link_libraries(adastra mysqlcppconn)

# Installer la bibliothèque dans le répertoire 'libs'
install(TARGETS adastra DESTINATION /home/softadastra/adastra/libs)

# Installer les fichiers d'en-tête dans le répertoire 'include'
install(DIRECTORY include/ DESTINATION /home/softadastra/adastra/include)
