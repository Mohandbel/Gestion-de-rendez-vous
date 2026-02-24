#include "fenetreprincipale.h"
#include "dialoguepersonne.h"


#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

fenetrePrincipale::fenetrePrincipale(LDC_personne* LDC_p, LDC_RDV *LDC_rdv, QWidget *parent)
    : d_LDC_p{LDC_p}, dialogue_p{nullptr}, d_LDC_RDV{LDC_rdv}, dialogue_rdv{nullptr}, QWidget{parent}
{

    creeInterface();
}

void fenetrePrincipale::creeInterface()
{
    auto layoutPrincipal {new QVBoxLayout{this}};
    setMinimumSize(350,330);
    auto CarnetDeRDV {new QLabel{tr("Carnet de rendez-vous")}};
    CarnetDeRDV->setStyleSheet("font-size:25px");
    layoutPrincipal->addWidget(CarnetDeRDV, 0, Qt::AlignHCenter | Qt::AlignTop);
    auto boutonPersonne {new QPushButton{tr("Personne")}};
    boutonPersonne->setMinimumSize(200, 50);
    layoutPrincipal->addWidget(boutonPersonne, 0, Qt::AlignHCenter | Qt::AlignTop);

    auto boutonRDV {new QPushButton{tr("Rendez-vous")}};
    boutonRDV->setMinimumSize(200, 50);
    layoutPrincipal->addWidget(boutonRDV, 0, Qt::AlignHCenter | Qt::AlignTop);

    auto boutonQuitter {new QPushButton{tr("Quitter")}};
    boutonQuitter->setMinimumSize(200, 50);
    layoutPrincipal->addWidget(boutonQuitter, 0, Qt::AlignHCenter | Qt::AlignTop);

    connect(boutonQuitter, &QPushButton::clicked, this, &fenetrePrincipale::onQuitter);
    connect(boutonPersonne, &QPushButton::clicked, this, &fenetrePrincipale::onPersonne);
    connect(boutonRDV, &QPushButton::clicked, this, &fenetrePrincipale::onRendezVous);
}

void fenetrePrincipale::onQuitter()
{
    close();
}

void fenetrePrincipale::onPersonne()
{
    if(d_LDC_p==nullptr)
    {
        d_LDC_p = new LDC_personne{};
    }
    if(dialogue_p!=nullptr)
        dialogue_p->close();
    dialogue_p = new dialoguePersonne{d_LDC_RDV,d_LDC_p};
    dialogue_p->show();
}

void fenetrePrincipale::onRendezVous()
{
    if(d_LDC_RDV==nullptr)
    {
        d_LDC_RDV= new LDC_RDV{};
    }
    if(dialogue_rdv!=nullptr)
        dialogue_rdv->close();
    dialogue_rdv= new dialoguerdv{d_LDC_p,d_LDC_RDV};
    dialogue_rdv->show();
}
