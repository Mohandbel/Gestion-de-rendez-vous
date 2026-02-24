#include<QVBoxLayout>
#include<QLabel>
#include<QMessageBox>
#include"dialoguemodifierrdv.h"


dialogueModifierRdv::dialogueModifierRdv( ChainonRDV* rdv,LDC_personne* ldc_personne,QWidget *parent)
    : d_rdvModifier{rdv},d_ldc_personne{ldc_personne} ,QDialog{parent}
{
    creeInterface();
    mettreAJourList();
}
void dialogueModifierRdv::creeInterface()
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
    auto TXTNom = new QLabel{tr("Nom de rendez-vous :")  };
    d_EditNom = new QLineEdit{QString::fromStdString( d_rdvModifier->d_Rdv.getnomrdv())};
    d_EditNom->setDisabled(true);
    layoutNom->addWidget(TXTNom, 0,Qt::AlignLeft | Qt::AlignTop);
    layoutNom->addWidget(d_EditNom, Qt::AlignRight | Qt::AlignTop);

    auto TXTDate = new QLabel{tr("Date : ")};
    d_EditDate = new QLineEdit{QString("%1/%2/%3")
                                   .arg(d_rdvModifier->d_Rdv.getjours(), 2, 10, QChar('0'))
                                   .arg(d_rdvModifier->d_Rdv.getmois(), 2, 10, QChar('0'))
                                   .arg(d_rdvModifier->d_Rdv.getannee(), 4, 10, QChar('0'))};
    d_EditDate->setPlaceholderText("dd-MM-yyyy") ;
    layoutdate->addWidget(TXTDate, 0, Qt::AlignLeft);
    layoutdate->addWidget(d_EditDate, Qt::AlignRight);

    auto TXTheuredebut = new QLabel{tr("Heure début : ")};
    d_EditHeureDebut = new QLineEdit{QString::number(d_rdvModifier->d_Rdv.getHeureDebut().heure) + ":" + QString::number(d_rdvModifier->d_Rdv.getHeureDebut().minute)};
    d_EditHeureDebut->setPlaceholderText("HH:mm");

    auto TXTheurefin = new QLabel{tr("Heure Fin : ")};
    d_EditHeureFin = new QLineEdit{QString::number(d_rdvModifier->d_Rdv.getHeureFin().heure) + ":" + QString::number(d_rdvModifier->d_Rdv.getHeureFin().minute)};
    d_EditHeureFin->setPlaceholderText("HH:mm");

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
    tableParticipants->clearContents();
    tableParticipants->setRowCount(0);
    tableParticipants->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableParticipants->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableParticipants->setSelectionMode(QAbstractItemView::SingleSelection);
    tableParticipants->setColumnWidth(0, 120);
    tableParticipants->setColumnWidth(1, 120);
    tableParticipants->setColumnWidth(2, 120);
    tableParticipants->setColumnWidth(3, 160);

    if (d_rdvModifier)
    {
    int nbParticipants = d_rdvModifier->d_Rdv.retournerNbTb();

    for (int i = 0; i < nbParticipants; ++i)
    {
        personne p = d_rdvModifier->d_Rdv.retournerValeurTab(i)->getPersonne();

        int rowCount = tableParticipants->rowCount();
        tableParticipants->insertRow(rowCount);
        tableParticipants->setItem(rowCount, 0, new QTableWidgetItem(QString::fromStdString(p.nomDeFamille())));
        tableParticipants->setItem(rowCount, 1, new QTableWidgetItem(QString::fromStdString(p.prenom())));
         tableParticipants->setItem(rowCount, 2, new QTableWidgetItem(QString::fromStdString(p.numeroTel())));
         tableParticipants->setItem(rowCount, 3, new QTableWidgetItem(QString::fromStdString(p.adresseMail())));
    }
    }
    layoutpersonne->addWidget(comboPersonnes, 0, Qt::AlignLeft);
    tablelayout->addWidget(tableParticipants);
    btnAjouter = new QPushButton{tr("Ajouter")};
    btnSupprimer = new QPushButton{tr("Supprimer")};
    layoutpersonne->addWidget(btnAjouter, 0, Qt::AlignRight);
    layoutpersonne->addWidget(btnSupprimer, 0, Qt::AlignRight) ;

    btnValider = new QPushButton{tr("Valider")};
    auto boutonAnnuler {new QPushButton{tr("Annuler")}};
    layoutBouton->addWidget(btnValider, 0, Qt::AlignLeft);
    layoutBouton->addWidget(boutonAnnuler, 0, Qt::AlignRight);

    btnValider->setDefault(true);

    connect(btnAjouter,&QPushButton::clicked,this,&dialogueModifierRdv::onAjouter);
    connect(btnSupprimer,&QPushButton::clicked,this,&dialogueModifierRdv::onSupprimer);

    connect(btnValider,&QPushButton::clicked,this,&QDialog::accept);
    connect(boutonAnnuler,&QPushButton::clicked,this,&QDialog::reject);

}
void dialogueModifierRdv::mettreAJourList()
{
    comboPersonnes->clear();
    if(d_ldc_personne==nullptr)
        return;

    ChainonDC* courant=d_ldc_personne->getTete();
    while(courant!=nullptr) {
        comboPersonnes->addItem(QString::fromStdString(courant->getPersonne().nomDeFamille() + " " + courant->getPersonne().prenom()));
        courant=courant->getSuivant();
    }
}
void dialogueModifierRdv::onSupprimer()
{
    int row = tableParticipants->currentRow();
    if (row != -1) {
        tableParticipants->removeRow(row);
    }
}
void dialogueModifierRdv::onAjouter()
{
    if (comboPersonnes->currentIndex() != -1) {
        QString personne = comboPersonnes->currentText();
        QStringList noms = personne.split(' ');

        QString nom = noms[0];
        QString prenom = noms[1];

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
        tableParticipants->setItem(rowCount, 0, new QTableWidgetItem(nom));  // Nom
        tableParticipants->setItem(rowCount, 1, new QTableWidgetItem(prenom)); // Prénom
    }
}

