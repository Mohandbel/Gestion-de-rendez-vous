#ifndef AJOUTERPERSONNEDIALOGUE_H
#define AJOUTERPERSONNEDIALOGUE_H
#include "include/ldc_personne.h"
#include <QTableWidget>
#include <QPushButton>
#include <QWidget>
#include <QDialog>

class AjouterPersonneDialogue : public QDialog
{
    Q_OBJECT
    friend class dialoguePersonne;
public:
    AjouterPersonneDialogue(LDC_personne* personnes=nullptr, QWidget *parent = nullptr);
private:
    LDC_personne* d_personnes;

    QLineEdit *d_EditNom;
    QLineEdit *d_EditPrenom;
    QLineEdit *d_EditTel;
    QLineEdit *d_EditEmail;

    QPushButton* d_boutonConfirmer;

    void creeInterface();
    void mettreAjourListePersonne();
signals:
};

#endif // AJOUTERPERSONNEDIALOGUE_H
