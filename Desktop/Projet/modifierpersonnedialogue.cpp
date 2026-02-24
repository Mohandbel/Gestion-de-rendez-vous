#include "modifierpersonnedialogue.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>

ModifierPersonneDialogue::ModifierPersonneDialogue(LDC_personne* personnes, const QString& nom, const QString& prenom, const QString& tel, const QString& email, QWidget *parent)
    : QDialog{parent}, d_personnes{personnes}, d_SonNom{new QLabel{nom}}, d_SonPrenom{new QLabel{prenom}}, d_EditTel{new QLineEdit{tel}}, d_EditEmail{new QLineEdit{email}}
{
    creeInterface();
}

void ModifierPersonneDialogue::creeInterface()
{
    setMinimumSize(300,200);
    setMaximumSize(300,200);
    auto layoutPrincipal {new QVBoxLayout{this}};

    auto layoutNom= new QHBoxLayout{};
    auto layoutPrenom= new QHBoxLayout{};
    auto layoutTel= new QHBoxLayout{};
    auto layoutEmail= new QHBoxLayout{};
    auto layoutBas= new QHBoxLayout{};
    layoutPrincipal->addLayout(layoutNom);
    layoutPrincipal->addLayout(layoutPrenom);
    layoutPrincipal->addLayout(layoutTel);
    layoutPrincipal->addLayout(layoutEmail);
    layoutPrincipal->addLayout(layoutBas);


    auto TXTNom = new QLabel{tr("Nom : ")};
    auto LeNom = new QLabel{d_SonNom->text()};
    layoutNom->addWidget(TXTNom, 0,Qt::AlignLeft | Qt::AlignTop);
    layoutNom->addWidget(LeNom, 0, Qt::AlignTop);

    auto TXTPrenom = new QLabel{tr("Prénom : ")};
    auto LePrenom = new QLabel{d_SonPrenom->text()};
    layoutPrenom->addWidget(TXTPrenom, 0,Qt::AlignLeft | Qt::AlignTop);
    layoutPrenom->addWidget(LePrenom, 0,Qt::AlignTop);

    auto TXTTel = new QLabel{tr("Nouveau Numéro : ")};
    d_EditTel->setMinimumSize(150, 25);
    layoutTel->addWidget(TXTTel, 0,Qt::AlignLeft);
    layoutTel->addWidget(d_EditTel, 0,Qt::AlignRight);

    auto TXTEmail = new QLabel{tr("Nouvel Email : ")};
    d_EditEmail->setMinimumSize(150, 25);
    layoutEmail->addWidget(TXTEmail, 0,Qt::AlignLeft);
    layoutEmail->addWidget(d_EditEmail, 0,Qt::AlignRight);

    d_boutonConfirmer = new QPushButton{tr("Confirmer")};
    auto boutonAnnuler {new QPushButton{tr("Annuler")}};
    layoutBas->addWidget(boutonAnnuler, 0, Qt::AlignBottom|Qt::AlignLeft);
    layoutBas->addWidget(d_boutonConfirmer, 0, Qt::AlignBottom|Qt::AlignRight);
    d_boutonConfirmer->setDefault(true);

    connect(d_boutonConfirmer, &QPushButton::clicked, this, &QDialog::accept);
    connect(boutonAnnuler, &QPushButton::clicked, this, &QDialog::reject);

}
QString ModifierPersonneDialogue::getNouveauTel() const
{
    return d_EditTel->text();
}

QString ModifierPersonneDialogue::getNouveauEmail() const
{
    return d_EditEmail->text();
}
