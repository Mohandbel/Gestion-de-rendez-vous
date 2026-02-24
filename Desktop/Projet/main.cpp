#include "fenetreprincipale.h"
#include "include/personne.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LDC_personne ldc;
    personne Mohand{"BELKACEM", "mohand", "0601010101", "mohand.belkacem@uha.fr"};
    personne Youcef{"SARNI", "youcef", "0602020202", "youcef.sarni@uha.fr"};
    personne Maria{"BOUAKAZ", "maria", "0603030303", "maria.bouakkaz@uha.fr"};
    personne Cherif{"BELKACEM", "cherif", "0603030123", "cherif.belkacem@uha.fr"};
    ldc.ajouterPersonne(Mohand);
    ldc.ajouterPersonne(Youcef);
    ldc.ajouterPersonne(Maria);
    //ldc.ajouterPersonne(Cherif);
    Heure heureDebut(10,30);  // 10h30
    Heure heureFin(11,30);    // 11h30
    ChainonDC** tab1=nullptr;
    ChainonDC** tab2=nullptr;
    Rendez_Vous rdv1("Réunion Projet", 2025, 3, 30, heureDebut, heureFin,tab1);
    Heure heureDebut2(14,00);  // 14h00
    Heure heureFin2(15,00);    // 15h00
    Rendez_Vous rdv2("Séminaire", 2025, 3, 31, heureDebut2, heureFin2,tab2);
    LDC_RDV rdv_ldc;
    rdv_ldc.AjoutRDV(rdv1);
    rdv_ldc.AjoutRDV(rdv2);
    rdv_ldc.ajouterARdv(ldc.trouverPersonne("BELKACEM", "mohand"), "Réunion Projet");
    rdv_ldc.ajouterARdv(ldc.trouverPersonne("BOUAKAZ", "maria"), "Réunion Projet");

    LDC_RDV* RendezVous = &rdv_ldc;

    LDC_personne* Personnes = &ldc;
    fenetrePrincipale w{Personnes, RendezVous};
    w.show();
    return a.exec();
}
