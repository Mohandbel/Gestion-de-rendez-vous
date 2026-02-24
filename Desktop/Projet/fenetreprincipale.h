#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H
#include "dialoguepersonne.h"
#include "dialoguerdv.h"
#include "include/ldc_personne.h"
#include "include/LDC_RDV.h"
#include <QWidget>

class fenetrePrincipale : public QWidget
{
    Q_OBJECT

public:
    fenetrePrincipale(LDC_personne* LDC_p=nullptr, LDC_RDV *LDC_RDV=nullptr, QWidget *parent = nullptr);
private:
    LDC_personne* d_LDC_p;
    LDC_RDV* d_LDC_RDV;
    dialoguePersonne* dialogue_p;
    dialoguerdv *dialogue_rdv;
    void creeInterface();
private slots:
    void onQuitter();
    void onPersonne();
    void onRendezVous();
};
#endif // FENETREPRINCIPALE_H
