#ifndef AJOUTERRDV_H
#define AJOUTERRDV_H

#include <QDialog>
#include <QComboBox>
#include <QTableWidget>
#include <QPushButton>
#include<QTimeEdit>
#include<QLineEdit>
#include<QDateEdit>
#include "include/ldc_personne.h"
#include "include/ldc_rdv.h"
#include"include/ldc_rdv.h"
#include<QWidget>
#include<QLabel>

class ajouterrdv : public QDialog {
    Q_OBJECT
    friend class dialoguerdv;
public:
    ajouterrdv(LDC_personne *listePersonnes = nullptr, LDC_RDV *listeRDV=nullptr, QWidget *parent = nullptr);
private:
    LDC_personne *d_listePersonnes;
    LDC_RDV *d_listeRDV;
    QComboBox *comboPersonnes;
    QTableWidget *tableParticipants;
    QPushButton *btnAjouter;
    QPushButton *btnSupprimer;
    QPushButton *btnValider;
    QLineEdit *d_EditNom;
    QLineEdit *d_EditDate ;
    QLineEdit *d_EditHeureDebut ;
    QLineEdit *d_EditHeureFin ;
    void actualiserListePersonnes();
    void creeInterface();
private slots:
    void onAjouterParticipant();
    void onSupprimerParticipant();
};

#endif // AJOUTERRDV_H
