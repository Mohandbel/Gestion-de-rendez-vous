#include"../include/rendez_vous.h"
#include"../include/ldc_personne.h"

Rendez_Vous::Rendez_Vous(const std::string & nomRDV, int annee, int mois, int jour, Heure HeureDebut, Heure HeureFin, ChainonDC **personnes ):
    d_nomRDV{nomRDV} , d_annee{annee} , d_mois{mois} , d_jour{jour} , d_HeureDebut{HeureDebut} ,d_HeureFin{HeureFin},d_tab_personnes{personnes}, nb_personnes{0}
{}
//void Rendez_Vous::ModifierRDV(const std::string nomRDV)

std::string Rendez_Vous:: getnomrdv () const
{
    return d_nomRDV;
}
int Rendez_Vous::getannee()const
{
    return d_annee;
}
int Rendez_Vous::getmois() const
{
    return d_mois;
}
int Rendez_Vous::getjours() const {
    return d_jour;
}
Heure Rendez_Vous:: getHeureDebut() const
{
    return d_HeureDebut;
}
Heure Rendez_Vous::getHeureFin() const
{
    return d_HeureFin;
}
bool Rendez_Vous::aParticipant(const std::string & nom,const std::string  & prenom) const
{

    for (int i = 0; i < nb_personnes; i++) { // taille Ã©tant la taille du tableau
        if (d_tab_personnes[i] &&
            d_tab_personnes[i]->d_personne.nomDeFamille() == nom &&
            d_tab_personnes[i]->d_personne.prenom() == prenom) {
            return true;
        }
    }
    return false;

}
int Rendez_Vous::retournerNbTb()const
{
    return nb_personnes;
}
ChainonDC* Rendez_Vous::retournerValeurTab(int idx)   const {
    if (idx < 0 || idx >= nb_personnes) { // Vérification des limites
        return nullptr; // Retourne nullptr si l'index est invalide
    }
    return d_tab_personnes[idx]; // Retourne le pointeur vers le ChainonDC à l’indice idx
}
void Rendez_Vous::viderParticipants(){
    delete [] d_tab_personnes;
    d_tab_personnes=nullptr;
    nb_personnes=0;
}
void Rendez_Vous::ajouterParticipant(personne* p) {
    if (!p) {
        return; // Vérifier que le pointeur n'est pas nul
    }

    // Vérifier si la personne est déjà dans le tableau
    for (int i = 0; i < nb_personnes; ++i) {
        if (d_tab_personnes[i]->getPersonne() == *p) {
            return; // La personne est déjà présente, ne rien faire
        }
    }

    // Créer un nouveau tableau avec une capacité augmentée
    ChainonDC **nouveauTab = new ChainonDC*[nb_personnes + 1];

    // Copier les anciens éléments dans le nouveau tableau
    for (int i = 0; i < nb_personnes; ++i) {
        nouveauTab[i] = d_tab_personnes[i];
    }

    // Ajouter la nouvelle personne à la fin
    nouveauTab[nb_personnes] = new ChainonDC(*p); // Création d’un nouveau ChainonDC

    // Supprimer l'ancien tableau et assigner le nouveau
    delete[] d_tab_personnes;
    d_tab_personnes = nouveauTab;

    // Incrémenter le compteur de participants
    nb_personnes++;
}
void Rendez_Vous::setDate(int annee,int mois ,int jour){
    d_annee=annee;
        d_mois= mois;
    d_jour=jour;
}
void Rendez_Vous::setHeureDebut(Heure d)
{
    d_HeureDebut=d;
}
void Rendez_Vous::setHeureFin(Heure f)
{
    d_HeureFin=f;
}
