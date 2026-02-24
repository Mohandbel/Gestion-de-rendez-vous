#ifndef LDC_RDV_H
#define LDC_RDV_H
#include"rendez_vous.h"
#include"ldc_personne.h"


class ChainonRDV
{
    friend  class LDC_RDV;
    friend class dialoguerdv;
    friend class dialogueModifierRdv;
public:
    ChainonRDV( const Rendez_Vous &  rdv);
    const Rendez_Vous& getrdv() const;
    ChainonRDV* getSuivantrdv() const;

private:
    Rendez_Vous d_Rdv;
    ChainonRDV *d_prec, *d_suiv;



};

class LDC_RDV{
public:
    friend class dialoguerdv;
    LDC_RDV();
    ~LDC_RDV();
    void AjoutRDV(const Rendez_Vous  & rdv);
    void SupprimerRDV(const std::string nom);
    ChainonRDV* RechercheRDV(const std::string & nomRDV ) const;
    bool verificationdePersonneEstLibre(const std::string & nomPersonne,const std::string & prenomPersonne, int anee , int mois , int jour , Heure Debut,Heure Fin) const;// verifier si la personne peut etre ajouter a un rendez-vous
    LDC_RDV* rechercheRendezVousParPersonne(const std::string &nom, const std::string &prenom) const;
    LDC_RDV* rechercheRendezVousParPersonne(const std::string &nom, const std::string &prenom, int annee, int mois, int jour, Heure heureDebut) const;
    LDC_RDV* rechercheParDate(int annee, int mois, int jour) const;
    void ajouterARdv(ChainonDC *P, const std::string &nomRDV);
    ChainonRDV *getTeterdv() const;
private:
    ChainonRDV *d_tete;


};

#endif // LDC_RDV_H
