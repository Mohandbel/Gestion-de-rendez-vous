#ifndef MODIFIERPERSONNEDIALOGUE_H
#define MODIFIERPERSONNEDIALOGUE_H

#include "include/ldc_personne.h"
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class ModifierPersonneDialogue : public QDialog
{
    Q_OBJECT

public:
    ModifierPersonneDialogue(LDC_personne* personnes = nullptr, const QString& nom = "", const QString& prenom = "", const QString& tel = "", const QString& email = "", QWidget *parent = nullptr);

    QString getNouveauTel() const;
    QString getNouveauEmail() const;

private:
    LDC_personne* d_personnes;

    QLabel* d_SonNom;
    QLabel* d_SonPrenom;

    QLineEdit* d_EditTel;
    QLineEdit* d_EditEmail;

    QPushButton* d_boutonConfirmer;

    void creeInterface();

};

#endif // MODIFIERPERSONNEDIALOGUE_H
