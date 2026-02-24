#ifndef DIALOGUEMODIFIERRDV_H
#define DIALOGUEMODIFIERRDV_H
#include "include/LDC_RDV.h"
#include "include/ldc_personne.h"
#include<QDialog>
#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>

class dialogueModifierRdv : public QDialog
{
    friend class dialoguerdv;
    Q_OBJECT
public:
    explicit dialogueModifierRdv( ChainonRDV* rdv,LDC_personne* ldc_personne,  QWidget *parent = nullptr);
private:
    LDC_personne* d_ldc_personne;
    ChainonRDV* d_rdvModifier;
    QComboBox *comboPersonnes;
    QTableWidget *tableParticipants;
    QPushButton *btnAjouter;
    QPushButton *btnSupprimer;
    QPushButton *btnValider;
    QLineEdit *d_EditNom;
    QLineEdit *d_EditDate ;
    QLineEdit *d_EditHeureDebut ;
    QLineEdit *d_EditHeureFin ;
    void creeInterface();
    void mettreAJourList();
private slots:
    void onAjouter();
    void onSupprimer();


signals:
};

#endif // DIALOGUEMODIFIERRDV_H
