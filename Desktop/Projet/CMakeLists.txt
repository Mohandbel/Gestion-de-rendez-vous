cmake_minimum_required(VERSION 3.19)
project(DialogueTestProjet LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(DialogueTestProjet
    WIN32 MACOSX_BUNDLE
    main.cpp
    fenetreprincipale.cpp
    fenetreprincipale.h
    dialoguepersonne.h dialoguepersonne.cpp
    ajouterpersonnedialogue.h ajouterpersonnedialogue.cpp
    modifierpersonnedialogue.h modifierpersonnedialogue.cpp
    dialoguerdv.h dialoguerdv.cpp
    dialoguemodifierrdv.h dialoguemodifierrdv.cpp
    ajouterrdv.cpp ajouterrdv.h
    include/ldc_personne.h src/ldc_personne.cpp
    include/ldc_rdv.h src/ldc_rdv.cpp
    include/personne.h src/personne.cpp
    include/rendez_vous.h src/rendez_vous.cpp
    .gitignore
)

target_link_libraries(DialogueTestProjet
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS DialogueTestProjet
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET DialogueTestProjet
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
