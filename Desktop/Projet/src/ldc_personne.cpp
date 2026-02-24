#include"../include/ldc_personne.h"
#include"../include/LDC_RDV.h"

ChainonDC::ChainonDC(const personne& p) : d_personne{p}, d_prec{nullptr}, d_suiv{nullptr}
{}

LDC_personne::LDC_personne() : d_tete{nullptr}
{}

LDC_personne::~LDC_personne()
{
    while(d_tete)
    {
        ChainonDC *tmp=d_tete->d_suiv;
        delete d_tete;
        d_tete=tmp;
    }
}

void LDC_personne::ajouterPersonne(const personne& p)
{
    ChainonDC *nv=new ChainonDC(p);

    //Cas 1 : La liste est vide
    if(d_tete==nullptr)
    {
        d_tete=nv;
        return;
    }

    //Recherche de la position d'insertion (ordre alphabétique)
    ChainonDC *courant=d_tete;
    ChainonDC *prec=nullptr;

    while(courant!=nullptr && courant->d_personne.nomDeFamille() < p.nomDeFamille())
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

void LDC_personne::supprimerPersonne(const std::string& nom, const std::string& prenom)
{
    // Si la liste est vide, rien à faire
        if (d_tete == nullptr) {
        return;
    }

    ChainonDC* courant = d_tete;
    ChainonDC* aSupprimer = nullptr;

    // Rechercher la personne à supprimer
    while (courant != nullptr && (courant->d_personne.nomDeFamille() != nom || courant->d_personne.prenom() != prenom))
    {
        courant = courant->d_suiv;
    }

    // Si la personne n'est pas trouvée, rien à faire
    if (courant == nullptr) return;

    aSupprimer = courant;

    // Cas 1 : Suppression en tête
    if (aSupprimer == d_tete) {
        d_tete = aSupprimer->d_suiv;
        if (d_tete != nullptr) {
            d_tete->d_prec = nullptr;
        }
    }
    // Cas 2 : Suppression ailleurs dans la liste
    else {
        if (aSupprimer->d_prec != nullptr) {
            aSupprimer->d_prec->d_suiv = aSupprimer->d_suiv;
        }
        if (aSupprimer->d_suiv != nullptr) {
            aSupprimer->d_suiv->d_prec = aSupprimer->d_prec;
        }
    }

    // Libérer la mémoire
    delete aSupprimer;
}

bool LDC_personne::supprimablePersonne(LDC_RDV *ouchercher, const std::string &nom, const std::string &prenom)
{
    ChainonRDV* tmp = ouchercher->getTeterdv();

    while (tmp != nullptr)
    {
        const Rendez_Vous& rdv = tmp->getrdv();

        for (int i = 0; i < rdv.retournerNbTb(); i++)
        {
            ChainonDC* participant = rdv.retournerValeurTab(i);
            if (participant != nullptr) // Vérification pour éviter un crash
            {
                const personne& p = participant->getPersonne(); // Utilisation de la méthode `getPersonne()`

                if (p.nomDeFamille() == nom && p.prenom() == prenom)
                {
                    return false; // La personne est trouvée dans un RDV, donc elle n'est pas supprimable.
                }
            }
        }

        tmp = tmp->getSuivantrdv(); // Passer au rendez-vous suivant
    }

    return true; // Aucun rendez-vous trouvé pour cette personne, donc elle est supprimable.
}




void LDC_personne::modifierPersonne(const std::string& nom, const std::string& prenom, const std::string& numero, const std::string& adresseMail)
{
    ChainonDC *crt = trouverPersonne(nom, prenom);
    crt->d_personne.setNum(numero);
    crt->d_personne.setAdresseMail(adresseMail);
}

bool LDC_personne::personneModifiable(const std::string& nom, const std::string& prenom)
{
    if(trouverPersonne(nom, prenom)!=nullptr)
        return true;
    return false;
}

ChainonDC* LDC_personne::trouverPersonne(const std::string& nom, const std::string& prenom)
{
    ChainonDC* courant=d_tete;
    while(courant!=nullptr)
    {
        if(courant->d_personne.nomDeFamille()==nom && courant->d_personne.prenom()==prenom)
        {
            return courant;
        }
        courant=courant->d_suiv;
    }
    return nullptr;
}
ChainonDC* LDC_personne::getTete() const
{
    return d_tete;
}

const personne& ChainonDC::getPersonne() const
{
    return this->d_personne;
}

ChainonDC* ChainonDC::getSuivant() const
{
    return this->d_suiv;
}

