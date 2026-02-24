#ifndef DIALOGUEPERSONNE_H
#define DIALOGUEPERSONNE_H
#include "include/ldc_personne.h"
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QDialog>
class dialoguePersonne : public QDialog
{
    Q_OBJECT
public:
    dialoguePersonne(LDC_RDV* ldc_rdv=nullptr, LDC_personne* personnes=nullptr, QWidget *parent = nullptr);
private:
    LDC_personne* d_personnes;
    LDC_RDV* d_ldcrdv;
    QTableWidget* d_table;
    QPushButton* d_boutonSupprimer;
    QPushButton* d_boutonModifier;
    void creeInterface();
    void mettreAjourListePersonne();
private slots:
    void onSupprimer();
    void onAjouter();
    void onModifier();
signals:
};

#endif // DIALOGUEPERSONNE_H
