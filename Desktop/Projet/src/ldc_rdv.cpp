#include "../include/LDC_RDV.h"
#include "../include/rendez_vous.h"
#include<string>
#include"../include/ldc_personne.h"
ChainonRDV:: ChainonRDV( const Rendez_Vous &  rdv): d_Rdv{rdv}, d_prec{nullptr},d_suiv {nullptr}
{}
LDC_RDV ::LDC_RDV():  d_tete{nullptr}
{}
LDC_RDV ::~LDC_RDV(){
    while(d_tete){
        ChainonRDV *tmp = d_tete -> d_suiv ;
        delete d_tete ;
        d_tete = tmp ;
    }
}
void LDC_RDV ::AjoutRDV(const Rendez_Vous  & rdv)
{
    ChainonRDV *nv = new ChainonRDV(rdv);

    //Cas 1 : La liste est vide
    if(d_tete==nullptr)
    {
        d_tete=nv;
        return;
    }

    //Recherche de la position d'insertion (ordre alphabétique)
    ChainonRDV *courant=d_tete;
    ChainonRDV *prec=nullptr;

    while(courant!=nullptr && courant->d_Rdv.getnomrdv() < nv->d_Rdv.getnomrdv())
    {
        prec=courant;
        courant=courant->d_suiv;
    }

    //Cas 2 : Insertion en tête (Si le nom doit être saisi avant les autres)
    if(prec==nullptr)
    {
        nv->d_suiv=d_tete;
        d_tete->d_prec=nv;
        d_tete=nv;
    }

    //Cas 3 : Insertion en milieu OU fin
    else{
        nv->d_suiv=courant;
        nv->d_prec=prec;
        prec->d_suiv=nv;
        if(courant!=nullptr) //Si l'insertion ne se fait pas en fin de liste
        {
            courant->d_prec=nv;
        }

    }
}
const Rendez_Vous& ChainonRDV::getrdv() const
{
    return d_Rdv;
}
ChainonRDV* ChainonRDV::getSuivantrdv() const
{
    return d_suiv;
}

void LDC_RDV :: SupprimerRDV(const std::string nom)
{
    ChainonRDV *tmp=d_tete;
    while (tmp!=nullptr && tmp->d_Rdv.getnomrdv()!=nom)
    {
        tmp=tmp->d_suiv;
    }
    if(tmp!=nullptr)
    {
        if (tmp->d_prec == nullptr) // suppression de la tete
        {
            d_tete = tmp->d_suiv;
            if (d_tete != nullptr)
            {
                d_tete->d_prec = nullptr;
            }
            delete tmp;
        }else
        {
            if(tmp->d_suiv!=nullptr)//supression au milieu
            {
                tmp->d_suiv->d_prec=tmp->d_prec;
                tmp->d_prec->d_suiv=tmp->d_suiv;
                delete tmp;
            }else{// supression a la fin
                tmp->d_prec->d_suiv=nullptr;

                delete tmp;
            }
        }
    }
}
ChainonRDV* LDC_RDV::RechercheRDV(const std::string & nomRDV) const
{
    if (d_tete==nullptr)
    {
        return nullptr;
    }
    ChainonRDV* crt=d_tete;
    while (crt!=nullptr && crt->d_Rdv.getnomrdv()<nomRDV)
    {
        crt=crt->d_suiv;
    }
    if (crt!=nullptr && crt->d_Rdv.getnomrdv()==nomRDV)
    {
        return crt;
    }
    else
    {
        return nullptr;
    }
}


bool LDC_RDV::verificationdePersonneEstLibre(const std::string & nomPersonne, const std::string & prenomPersonne, int anee, int mois, int jour, Heure Debut, Heure Fin) const
{
    // Si la liste est vide, la personne est libre
    if (d_tete == nullptr)
        return true;

    // Pointeur pour parcourir la liste chaînée
    ChainonRDV* crt = d_tete;

    // Parcourir tous les rendez-vous
    while (crt != nullptr)
    {
        // Vérifier si le rendez-vous est à la même date
        if (crt->d_Rdv.getannee() == anee && crt->d_Rdv.getmois() == mois && crt->d_Rdv.getjours() == jour)
        {
            // Vérifier si la personne est dans ce rendez-vous
            if (crt->d_Rdv.aParticipant(nomPersonne, prenomPersonne))
            {
                // Vérifier si les intervalles de temps se chevauchent
                if (Debut < crt->d_Rdv.getHeureFin() && Fin > crt->d_Rdv.getHeureDebut() )
                {
                    return false; // Chevauchement trouvé, la personne n'est pas libre
                }
            }
        }
        // Passer au rendez-vous suivant
        crt = crt->d_suiv;
    }

    // Aucun chevauchement trouvé, la personne est libre
    return true;
}
LDC_RDV* LDC_RDV::rechercheRendezVousParPersonne(const std::string& nom,const  std::string& prenom) const
{
    // Création d'une nouvelle liste pour stocker les rendez-vous trouvés
    LDC_RDV* nouvelleListe = new LDC_RDV();

    // Parcours de la liste existante
    ChainonRDV* tmp = d_tete;
    while (tmp != nullptr)
    {
        // Vérifier si la personne est présente dans ce rendez-vous
        for (int i = 0; i < tmp->d_Rdv.retournerNbTb(); i++)
        {
            if (tmp->d_Rdv.retournerValeurTab(i)->d_personne.nomDeFamille() == nom &&
                tmp->d_Rdv.retournerValeurTab(i)->d_personne.prenom() == prenom)
            {
                // Ajouter ce rendez-vous à la nouvelle liste chaînée
                nouvelleListe->AjoutRDV(tmp->d_Rdv);
                break;  // Arrêter la recherche pour ce RDV, car la personne a été trouvée
            }
        }

        // Passer au rendez-vous suivant
        tmp = tmp->d_suiv;
    }

    // Retourner la nouvelle liste contenant les rendez-vous filtrés
    return nouvelleListe;
}
LDC_RDV* LDC_RDV::rechercheRendezVousParPersonne(const std::string& nom, const std::string& prenom, int annee, int mois, int jour, Heure heureDebut) const
{
    // Création d'une nouvelle liste pour stocker les rendez-vous trouvés
    LDC_RDV* nouvelleListe = new LDC_RDV();

    // Parcours de la liste existante
    ChainonRDV* tmp = d_tete;
    while (tmp != nullptr)
    {
        // Vérifier si la personne est présente dans ce rendez-vous
        for (int i = 0; i < tmp->d_Rdv.retournerNbTb(); i++)
        {
            // Vérifier si le nom, prénom, date et horaire correspondent
            if (tmp->d_Rdv.retournerValeurTab(i)->d_personne.nomDeFamille() == nom &&
                tmp->d_Rdv.retournerValeurTab(i)->d_personne.prenom() == prenom &&
                tmp->d_Rdv.getannee() == annee &&
                tmp->d_Rdv.getmois() == mois &&
                tmp->d_Rdv.getjours() == jour &&
                tmp->d_Rdv.getHeureDebut() == heureDebut )
            {
                // Ajouter ce rendez-vous à la nouvelle liste chaînée
                nouvelleListe->AjoutRDV(tmp->d_Rdv);
                break;  // Arrêter la recherche pour ce RDV, car la personne et les critères ont été trouvés
            }
        }

        // Passer au rendez-vous suivant
        tmp = tmp->d_suiv;
    }

    // Retourner la nouvelle liste contenant les rendez-vous filtrés
    return nouvelleListe;
}
LDC_RDV* LDC_RDV::rechercheParDate(int annee, int mois, int jour) const
{
    // Création d'une nouvelle liste pour stocker les rendez-vous trouvés
    LDC_RDV* nouvelleListe = new LDC_RDV();

    // Parcours de la liste existante des rendez-vous
    ChainonRDV* tmp = d_tete;
    while (tmp != nullptr)
    {
        // Vérifier si la date du rendez-vous correspond à la date recherchée
        if (tmp->d_Rdv.getannee() == annee &&
            tmp->d_Rdv.getmois() == mois &&
            tmp->d_Rdv.getjours() == jour)
        {
            // Ajouter ce rendez-vous à la nouvelle liste chaînée
            nouvelleListe->AjoutRDV(tmp->d_Rdv);
        }

        // Passer au rendez-vous suivant
        tmp = tmp->d_suiv;
    }

    // Retourner la nouvelle liste contenant les rendez-vous filtrés
    return nouvelleListe;
}
void LDC_RDV::ajouterARdv(ChainonDC *P, const std::string &nomRDV)
{
    ChainonRDV* tmp=RechercheRDV(nomRDV);
    if(tmp==nullptr)
        return;

    // Créer un nouveau tableau avec une taille augmentée de 1
    int nb =tmp->d_Rdv.retournerNbTb();
    ChainonDC** nouveau_tableau = new ChainonDC*[nb+ 1];

    // Copier les éléments existants dans le nouveau tableau
    for (int i = 0; i <nb; i++) {
        nouveau_tableau[i] = tmp->d_Rdv.retournerValeurTab(i);
    }

    // Ajouter le nouveau ChainonDC à la fin
    nouveau_tableau[nb] = P;

    // Libérer l'ancien tableau
    delete[] tmp->d_Rdv.d_tab_personnes;

    // Mettre à jour le pointeur du tableau
    tmp->d_Rdv.d_tab_personnes = nouveau_tableau;

    // Incrémenter le nombre de personnes
    tmp->d_Rdv.nb_personnes++;
}
ChainonRDV* LDC_RDV::getTeterdv() const
{
    return d_tete;
}

