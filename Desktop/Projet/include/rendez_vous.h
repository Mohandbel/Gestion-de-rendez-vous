#ifndef RENDEZ_VOUS_H
#define RENDEZ_VOUS_H
#include"ldc_personne.h"
#include<string>

struct Heure {
    int   heure;
    int  minute;
     Heure(int  h, int m) : heure(h), minute(m) {}

    bool operator<(const Heure& nv) const {
        if (heure < nv.heure) return true;
        if (heure > nv.heure) return false;
        return minute < nv.minute;
    }

    bool operator>(const Heure& nv) const {
        if (heure > nv.heure) return true;
        if (heure < nv.heure) return false;
        return minute > nv.minute;

    }
    bool operator==(const Heure& nv) const {
        return heure == nv.heure && minute == nv.minute;
    }
};

class Rendez_Vous
{
    friend class LDC_RDV;
public:
    Rendez_Vous(const std::string & nomRDV, int annee, int mois, int jour , Heure HeureDebut, Heure HeureFin, ChainonDC **personnes  );
    void ModifierRDV(const std::string & nomRDV);
    std::string getnomrdv () const ;
    int getannee() const ;
    int getmois() const;
    int getjours() const;
    Heure getHeureDebut() const;
    Heure getHeureFin() const;
    bool aParticipant(const std::string & nom,const std::string  & prenom)const;
    int retournerNbTb() const ;
    ChainonDC* retournerValeurTab(int idx) const;
    void viderParticipants();
    void ajouterParticipant( personne*  p);
    void setDate(int annee,int mois ,int jour);
    void setHeureDebut(Heure d);
    void setHeureFin(Heure f);
private:
    std::string d_nomRDV;
    int d_annee,d_mois ,d_jour;
    Heure d_HeureDebut, d_HeureFin;
    ChainonDC **d_tab_personnes;
    int nb_personnes;


};

#endif // RENDEZ_VOUS_H
