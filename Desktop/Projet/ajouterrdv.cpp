#include "ajouterrdv.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QChar>

ajouterrdv::ajouterrdv(LDC_personne *listePersonnes, LDC_RDV *listeRDV, QWidget* parent)
    : QDialog{parent}, d_listePersonnes{listePersonnes} ,d_listeRDV{listeRDV}
{
    creeInterface();
    actualiserListePersonnes();
}

void ajouterrdv::creeInterface()
{
    setWindowTitle("Ajouter un rendez-vous");
    setMinimumSize(560,400);
    auto layoutPrincipal {new QVBoxLayout{this}};
    auto layoutNom= new QHBoxLayout{};
    auto layoutdate= new QHBoxLayout{};
    auto layoutheure= new QHBoxLayout{};
    auto layoutpersonne= new QHBoxLayout{};
    auto tablelayout = new QHBoxLayout;
    auto layoutBouton= new QHBoxLayout{};
    layoutPrincipal->addLayout(layoutNom);
    layoutPrincipal->addLayout(layoutdate);
    layoutPrincipal->addLayout(layoutheure);
    layoutPrincipal->addLayout(layoutpersonne);
    layoutPrincipal->addLayout(tablelayout);
    layoutPrincipal->addStretch(1);
    layoutPrincipal->addLayout(layoutBouton);


    auto TXTNom = new QLabel{tr("Nom de rendez-vous : ")};
    d_EditNom = new QLineEdit{};
    layoutNom->addWidget(TXTNom, 0,Qt::AlignLeft | Qt::AlignTop);
    layoutNom->addWidget(d_EditNom, Qt::AlignRight | Qt::AlignTop);

    auto TXTDate = new QLabel{tr("Date : ")};
    d_EditDate = new QLineEdit{};
    d_EditDate->setPlaceholderText("dd/MM/yyyy") ;
    layoutdate->addWidget(TXTDate, 0, Qt::AlignLeft);
    layoutdate->addWidget(d_EditDate, Qt::AlignRight);

    auto TXTheuredebut = new QLabel{tr("Heure début : ")};
    d_EditHeureDebut = new QLineEdit{};
    d_EditHeureDebut->setPlaceholderText("HH:mm") ;

    auto TXTheurefin = new QLabel{tr("Heure Fin : ")};
    d_EditHeureFin = new QLineEdit{};
    d_EditHeureFin->setPlaceholderText("HH:mm") ;

    layoutheure->addWidget(TXTheuredebut, 0, Qt::AlignLeft);
    layoutheure->addWidget(d_EditHeureDebut, 0, Qt::AlignRight);
    layoutheure->addWidget(TXTheurefin, 0, Qt::AlignLeft);
    layoutheure->addWidget(d_EditHeureFin, 0, Qt::AlignRight);

    auto TXTPersonne = new QLabel(tr("Personnes :"));
    layoutpersonne->addWidget(TXTPersonne, 0, Qt::AlignLeft);

    comboPersonnes = new QComboBox{};
    tableParticipants = new QTableWidget{};
    tableParticipants->setColumnCount(4);
    tableParticipants->setHorizontalHeaderLabels({"Nom", "Prénom","Numéro","Adresse Mail"});
    tableParticipants->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableParticipants->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableParticipants->setSelectionMode(QAbstractItemView::SingleSelection);
    tableParticipants->setColumnWidth(0, 120);
    tableParticipants->setColumnWidth(1, 120);
    tableParticipants->setColumnWidth(2, 120);
    tableParticipants->setColumnWidth(3, 160);
    layoutpersonne->addWidget(comboPersonnes, 0, Qt::AlignLeft);
    tablelayout->addWidget(tableParticipants);
    btnAjouter = new QPushButton{tr("Ajouter")};
    btnSupprimer = new QPushButton{tr("Supprimer")};
    layoutpersonne->addWidget(btnAjouter, 0, Qt::AlignLeft);
    layoutpersonne->addWidget(btnSupprimer, 0, Qt::AlignRight) ;

    btnValider = new QPushButton{tr("Valider")};
    auto boutonAnnuler {new QPushButton{tr("Annuler")}};
    layoutBouton->addWidget(btnValider, 0, Qt::AlignLeft);
    layoutBouton->addWidget(boutonAnnuler, 0, Qt::AlignRight);

    btnValider->setDefault(true);

    connect(btnValider, &QPushButton::clicked, this, &QDialog::accept);
    connect(boutonAnnuler, &QPushButton::clicked, this, &QDialog::reject);
    connect(btnAjouter, &QPushButton::clicked, this, &ajouterrdv::onAjouterParticipant);
    connect(btnSupprimer, &QPushButton::clicked, this, &ajouterrdv::onSupprimerParticipant);

}


void ajouterrdv::actualiserListePersonnes()
{
    comboPersonnes->clear();
    if(d_listePersonnes==nullptr)
        return;

    ChainonDC* courant=d_listePersonnes->getTete();
    while(courant!=nullptr) {
        comboPersonnes->addItem(QString::fromStdString(courant->getPersonne().nomDeFamille() + " " + courant->getPersonne().prenom()));
        courant=courant->getSuivant();
    }
}

void ajouterrdv::onAjouterParticipant()
{
    if (comboPersonnes->currentIndex() != -1) {
        QString NomPrenom = comboPersonnes->currentText();
        QStringList noms = NomPrenom.split(' ');

        QString nom = noms[0];
        QString prenom = noms[1];

        ChainonDC* personne = d_listePersonnes->trouverPersonne(nom.toStdString(), prenom.toStdString());

        // Vérifier si la personne est déjà présente
        int rowCount = tableParticipants->rowCount();
        for (int row = 0; row < rowCount; ++row) {
            if (tableParticipants->item(row, 0)->text() == nom &&
                tableParticipants->item(row, 1)->text() == prenom) {
                QMessageBox Erreur{QMessageBox::Critical, tr("Erreur"), tr("Une personne ne peut pas être inserée deux fois"), QMessageBox::Ok};
                Erreur.exec();
                return; // La personne est déjà présente, on ne l'ajoute pas
            }
        }

        // Ajouter la personne si elle n'est pas déjà présente
        tableParticipants->insertRow(rowCount);
        tableParticipants->setItem(rowCount, 0, new QTableWidgetItem(QString::fromStdString(personne->getPersonne().nomDeFamille())));  // Nom
        tableParticipants->setItem(rowCount, 1, new QTableWidgetItem(QString::fromStdString(personne->getPersonne().prenom())));        // Prénom
        tableParticipants->setItem(rowCount, 2, new QTableWidgetItem(QString::fromStdString(personne->getPersonne().numeroTel())));
        tableParticipants->setItem(rowCount, 3, new QTableWidgetItem(QString::fromStdString(personne->getPersonne().adresseMail())));
    }
}


void ajouterrdv::onSupprimerParticipant()
{
    int row = tableParticipants->currentRow();
    if (row != -1) {
        tableParticipants->removeRow(row);
    }
}
