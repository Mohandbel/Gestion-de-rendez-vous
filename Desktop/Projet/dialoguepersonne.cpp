#include "dialoguepersonne.h"
#include "ajouterpersonnedialogue.h"
#include "include/ldc_personne.h"
#include"include/LDC_RDV.h"
#include "modifierpersonnedialogue.h"
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>

dialoguePersonne::dialoguePersonne(LDC_RDV* ldc_rdv,LDC_personne* personnes, QWidget *parent)
    : d_ldcrdv{ldc_rdv},d_personnes{personnes}, QDialog{parent}
{
    creeInterface();
    mettreAjourListePersonne();
}

void dialoguePersonne::creeInterface()
{
    setMinimumSize(560,400);
    auto layoutPrincipal {new QVBoxLayout{this}};
    d_table = new QTableWidget{};
    layoutPrincipal->addWidget(d_table);


    d_table->setColumnCount(4);
    d_table->setHorizontalHeaderLabels({"Nom", "Prénom", "Numéro", "Adresse mail"});
    d_table->setColumnWidth(0, 120);
    d_table->setColumnWidth(1, 120);
    d_table->setColumnWidth(2, 120);
    d_table->setColumnWidth(3, 150);
    d_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    d_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    d_table->setSelectionMode(QAbstractItemView::SingleSelection);


    auto layoutBoutons {new QHBoxLayout{}};
    layoutPrincipal->addLayout(layoutBoutons);
    auto boutonAjouter {new QPushButton{tr("Ajouter")}};
    d_boutonModifier = new QPushButton{tr("Modifier")};
    d_boutonSupprimer = new QPushButton{tr("Supprimer")};
    layoutBoutons->addWidget(boutonAjouter, 0, Qt::AlignBottom|Qt::AlignLeft);
    layoutBoutons->addWidget(d_boutonModifier, 0, Qt::AlignBottom|Qt::AlignLeft);
    layoutBoutons->addWidget(d_boutonSupprimer, 0, Qt::AlignBottom|Qt::AlignRight);
    d_boutonSupprimer->setEnabled(false);
    d_boutonModifier->setEnabled(false);

    boutonAjouter->setDefault(true);
    connect(d_boutonSupprimer, &QPushButton::clicked, this, &dialoguePersonne::onSupprimer);
    connect(boutonAjouter, &QPushButton::clicked, this, &dialoguePersonne::onAjouter);
    connect(d_boutonModifier, &QPushButton::clicked, this, &dialoguePersonne::onModifier);
}

void dialoguePersonne::mettreAjourListePersonne()
{
    if(!d_table || !d_personnes)
    {
        return;
        d_boutonSupprimer->setEnabled(false);
    }
    d_table->clearContents();
    d_table->setRowCount(0);

    ChainonDC *crt = d_personnes->d_tete;
    int ligne=0;
    while(crt!=nullptr)
    {
        personne p{crt->d_personne};
        d_table->insertRow(ligne);
        d_table->setItem(ligne, 0, new QTableWidgetItem(QString::fromStdString(p.nomDeFamille())));
        d_table->setItem(ligne, 1, new QTableWidgetItem(QString::fromStdString(p.prenom())));
        d_table->setItem(ligne, 2, new QTableWidgetItem(QString::fromStdString(p.numeroTel())));
        d_table->setItem(ligne, 3, new QTableWidgetItem(QString::fromStdString(p.adresseMail())));
        crt=crt->d_suiv;
        ++ligne;
    }
    d_table->resizeColumnToContents(3);
    if(ligne>0)
    {
        d_boutonSupprimer->setEnabled(true);
        d_boutonModifier->setEnabled(true);
        d_table->selectRow(0);
    }
    else{
        d_boutonSupprimer->setEnabled(false);
        d_boutonModifier->setEnabled(false);
    }
}


void dialoguePersonne::onSupprimer()
{
    if(d_table->selectedItems().isEmpty())
    {
        QMessageBox Impossible{QMessageBox::Information, tr("Erreur"), tr("Suppression impossible, veuillez séléctionner une personne."), QMessageBox::Ok};
        Impossible.exec();
    }
    else{
        QMessageBox Confirmation{QMessageBox::Question, tr("Confirmation"), tr("Êtes-vous sûr de vouloir supprimer cette personne ?"), QMessageBox::Yes | QMessageBox::No};
        if(Confirmation.exec()==QMessageBox::Yes)
        {
            int ligne = d_table->selectedItems().first()->row();
            QString nom = d_table->item(ligne, 0)->text();
            QString prenom = d_table->item(ligne, 1)->text();
            if (!d_personnes->supprimablePersonne(d_ldcrdv, nom.toStdString(), prenom.toStdString()))
            {
                QMessageBox Impossible{QMessageBox::Warning, tr("Erreur"), tr("Suppression impossible : cette personne a des rendez-vous."), QMessageBox::Ok};
                Impossible.exec();
                return;
            }


            d_personnes->supprimerPersonne(nom.toStdString(), prenom.toStdString());
            QMessageBox Supprimee{QMessageBox::Information, tr("Réussite"), tr("La personne a bien été supprimée"), QMessageBox::Ok};
            Supprimee.exec();
            mettreAjourListePersonne();
        }
    }
}

void dialoguePersonne::onAjouter()
{
    AjouterPersonneDialogue dAjoutPersonne{};
    if(dAjoutPersonne.exec() == QDialog::Accepted)
    {
        QString nom = dAjoutPersonne.d_EditNom->text().toUpper();
        QString prenom = dAjoutPersonne.d_EditPrenom->text().toLower();

        personne nvlPersonne{nom.toStdString(), prenom.toStdString(),
                             dAjoutPersonne.d_EditTel->text().toStdString(),
                             dAjoutPersonne.d_EditEmail->text().toStdString()};
        if(nvlPersonne.personneValide()==true)
        {
            d_personnes->ajouterPersonne(nvlPersonne);
            mettreAjourListePersonne();
        }
        else{
            QMessageBox Erreur{QMessageBox::Critical, tr("Erreur"), tr("Veuillez respecter les conditions ci-dessous :\nLe nom et le prénom doivent être composés uniquement de lettres\nLe numéro doit être composé uniquement de chiffres et ne peut dépasser 10\nL'adresse email doit être correcte"), QMessageBox::Ok};
            Erreur.exec();
        }
    }
}

void dialoguePersonne::onModifier()
{
    if(d_table->selectedItems().isEmpty())
    {
        d_boutonModifier->setEnabled(false);
    }
    else{
        int ligne = d_table->selectedItems().first()->row();
        QString SonNom = d_table->item(ligne, 0)->text();
        QString SonPrenom = d_table->item(ligne, 1)->text();
        QString SonTel = d_table->item(ligne, 2)->text();
        QString SonEmail = d_table->item(ligne, 3)->text();

        ModifierPersonneDialogue dModif{d_personnes, SonNom, SonPrenom, SonTel, SonEmail};

        if (dModif.exec() == QDialog::Accepted)
        {
            QString nouveauTel = dModif.getNouveauTel();
            QString nouveauEmail = dModif.getNouveauEmail();
            if(personne{SonNom.toStdString(), SonPrenom.toStdString(), nouveauTel.toStdString(), nouveauEmail.toStdString()}.personneValide()==true)
            {
                d_personnes->modifierPersonne(SonNom.toStdString(), SonPrenom.toStdString(), nouveauTel.toStdString(), nouveauEmail.toStdString());
                mettreAjourListePersonne();
            }
            else{
                QMessageBox Erreur{QMessageBox::Critical, tr("Erreur"), tr("Veuillez respecter les conditions ci-dessous :\nLe numéro doit être composé uniquement de chiffres et ne peut dépasser 10\nL'adresse email doit être correcte"), QMessageBox::Ok};
                Erreur.exec();
            }
        }
    }
}
