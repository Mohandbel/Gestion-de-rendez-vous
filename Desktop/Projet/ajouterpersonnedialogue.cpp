#include "ajouterpersonnedialogue.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>

    AjouterPersonneDialogue::AjouterPersonneDialogue(LDC_personne* personnes, QWidget *parent)
    : d_personnes{personnes}, QDialog{parent}
{
    creeInterface();
}

void AjouterPersonneDialogue::creeInterface()
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
    d_EditNom = new QLineEdit{};
    d_EditNom->setMinimumSize(150, 25);
    layoutNom->addWidget(TXTNom, 0,Qt::AlignRight);
    layoutNom->addWidget(d_EditNom, 0,Qt::AlignLeft);

    auto TXTPrenom = new QLabel{tr("Prenom : ")};
    d_EditPrenom = new QLineEdit{};
    d_EditPrenom->setMinimumSize(150, 25);
    layoutPrenom->addWidget(TXTPrenom, 0,Qt::AlignRight);
    layoutPrenom->addWidget(d_EditPrenom, 0,Qt::AlignLeft);

    auto TXTTel = new QLabel{tr("Numero Tel : ")};
    d_EditTel = new QLineEdit{};
    d_EditTel->setMinimumSize(150, 25);
    layoutTel->addWidget(TXTTel, 0,Qt::AlignRight);
    layoutTel->addWidget(d_EditTel, 0,Qt::AlignLeft);

    auto TXTEmail = new QLabel{tr("Email : ")};
    d_EditEmail = new QLineEdit{};
    d_EditEmail->setMinimumSize(150, 25);
    layoutEmail->addWidget(TXTEmail, 0,Qt::AlignRight);
    layoutEmail->addWidget(d_EditEmail, 0,Qt::AlignLeft);

    d_boutonConfirmer = new QPushButton{tr("Confirmer")};
    auto boutonAnnuler {new QPushButton{tr("Annuler")}};
    layoutBas->addWidget(boutonAnnuler, 0, Qt::AlignBottom|Qt::AlignLeft);
    layoutBas->addWidget(d_boutonConfirmer, 0, Qt::AlignBottom|Qt::AlignRight);
    d_boutonConfirmer->setDefault(true);

    connect(d_boutonConfirmer, &QPushButton::clicked, this, &QDialog::accept);
    connect(boutonAnnuler, &QPushButton::clicked, this, &QDialog::reject);

}
