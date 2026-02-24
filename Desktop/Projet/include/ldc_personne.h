#ifndef LDC_PERSONNE_H
#define LDC_PERSONNE_H

#include "personne.h"
class LDC_RDV;

class ChainonDC
{
    friend class LDC_personne;
    friend class dialoguePersonne;
    friend class Rendez_Vous;
    friend class LDC_RDV;
    friend class dialogueModifierRdv;
private:
    ChainonDC(const personne& p);
    personne d_personne;
    ChainonDC *d_prec;
    ChainonDC *d_suiv;
    public:
    const personne& getPersonne() const;
        ChainonDC* getSuivant() const;


};

class LDC_personne
{
public:
    friend class dialoguePersonne;
    LDC_personne();
    ~LDC_personne();
    void ajouterPersonne(const personne& p);
    void supprimerPersonne(const std::string& nom, const std::string& prenom);
    bool supprimablePersonne(LDC_RDV* ouchercher,const std::string& nom, const std::string& prenom);
    void modifierPersonne(const std::string &nom, const std::string &prenom, const std::string& numero, const std::string& adresseMail);
    bool personneModifiable(const std::string& nom, const std::string &prenom);
    ChainonDC* trouverPersonne(const std::string &nom, const std::string & prenom);
    ChainonDC* getTete() const;


private:
    ChainonDC* d_tete;
};


#endif // LDC_PERSONNE_H
