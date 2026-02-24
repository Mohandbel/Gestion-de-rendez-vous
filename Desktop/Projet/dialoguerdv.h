#ifndef DIALOGUERDV_H
#define DIALOGUERDV_H
#include"include/LDC_RDV.h"
#include <QWidget>
#include<QTableWidget>
#include<QComboBox>
#include<QCheckBox>
#include<QDialog>
class dialoguerdv : public QDialog
{
    Q_OBJECT
public:
    dialoguerdv(LDC_personne *d_ldc_personnes, LDC_RDV* ldc_rdv=nullptr, QWidget *parent = nullptr);
private:
    LDC_RDV *d_ldcRdv;
    LDC_personne *d_ldc_personnes;
    void creeInterface();
    void mettreAJourListRdv();
    QTableWidget* d_tbRdv;
    QComboBox *ListeDeroulante;
    QLineEdit *barreRecherche;
    QCheckBox *DateEtHeure;// ce chack box c'est pour savoir si l'utilsateur veut determiner si une personne a un rendez vous
    QLineEdit *Date;
    QLineEdit *Horaire;
    QPushButton* d_boutonSupprimer;
    QPushButton* d_boutonModifier;
    QPushButton* d_boutonAjouter;
    void afficherLdcRdv(LDC_RDV* ldc);
private slots:
    void onDateEtHeureCoche(bool checked); //Si la QCheckBox DateEtHeure est cochée ou pas
    void onListeDeroulanteChangee(int index);// si l'element selectionner est changer
    void onSupprime();
    void onRechercher();
    void onReset();
    void onModifier();
    void onAjouter();

};

#endif // DIALOGUERDV_H
