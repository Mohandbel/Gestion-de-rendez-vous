#include "dialoguerdv.h"
#include "include/LDC_RDV.h"
#include "ajouterrdv.h"
#include "dialoguemodifierrdv.h"
#include"include/rendez_vous.h"
#include<QVBoxLayout>
#include<QTableWidget>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QDate>
#include<QMessageBox>


dialoguerdv::dialoguerdv( LDC_personne *ldc_personnes,LDC_RDV* ldc_rdv, QWidget *parent)
    : d_ldc_personnes{ldc_personnes}, QDialog{parent}, d_ldcRdv{ldc_rdv}
{
    creeInterface();
    afficherLdcRdv(d_ldcRdv);

}
void dialoguerdv::creeInterface()
{
    setMinimumSize(650,500);
    auto layoutPrincipal {new QVBoxLayout{this}};
    auto layoutBarreHaut {new QHBoxLayout{}};
    layoutPrincipal->addLayout(layoutBarreHaut);
    // preparation composant barre haute
    ListeDeroulante =new QComboBox{};
    ListeDeroulante->addItem("Personne");
    ListeDeroulante->addItem("Date");
    layoutBarreHaut->addWidget(new QLabel("Filter par :"), 0, Qt::AlignLeft | Qt::AlignTop);
    layoutBarreHaut->addWidget(ListeDeroulante, Qt::AlignLeft | Qt::AlignTop);
    barreRecherche = new QLineEdit{};
    barreRecherche->setPlaceholderText("Nom Prénom");
    layoutBarreHaut->addWidget(barreRecherche, 0, Qt::AlignRight | Qt::AlignTop);
    auto boutonrecherche = new QPushButton{"Rechercher"};
    layoutBarreHaut->addWidget(boutonrecherche,0,Qt::AlignRight|Qt::AlignTop);
    auto layoutcheckbox {new QHBoxLayout{}};
    layoutPrincipal->addLayout(layoutcheckbox);
    DateEtHeure= new QCheckBox{tr("Recherche par date et horaire")};
    Date = new QLineEdit{};
    Date->setPlaceholderText("dd/mm/yyyy");
    Horaire =new QLineEdit{};
    Horaire->setPlaceholderText("HH:MM");
    auto boutonReset = new QPushButton{"Reset"};
    layoutcheckbox->addWidget(DateEtHeure);  // Checkbox à gauche
    layoutcheckbox->addWidget(Date);         // Juste après la checkbox
    layoutcheckbox->addWidget(Horaire);
    layoutcheckbox->addStretch();
    layoutcheckbox->addWidget(boutonReset,0,Qt::AlignRight);
    d_tbRdv = new QTableWidget(this);


    d_tbRdv->setColumnCount(5);
    d_tbRdv->setHorizontalHeaderLabels({"Intitulé", "Date", "Heure Debut","Heure Fin", "Nombre de personnes"});
    d_tbRdv->setColumnWidth(0, 180);  // Intitulé
    d_tbRdv->setColumnWidth(1, 130);  // Date
    d_tbRdv->setColumnWidth(2, 100);  // Heure Début
    d_tbRdv->setColumnWidth(3, 100);  // Heure Fin
    d_tbRdv->setColumnWidth(4, 140);
    d_tbRdv->setEditTriggers(QAbstractItemView::NoEditTriggers);
    d_tbRdv->setSelectionBehavior(QAbstractItemView::SelectRows);
    d_tbRdv->setSelectionMode(QAbstractItemView::SingleSelection);
    layoutPrincipal->addWidget(d_tbRdv);
    auto layoutBouton {new QHBoxLayout{}};
    layoutPrincipal->addLayout(layoutBouton);
    d_boutonAjouter= new QPushButton{"Ajouter RDV"};
    d_boutonModifier = new QPushButton{"Modifier"};
    d_boutonSupprimer = new QPushButton{"Supprimer"};
    layoutBouton->addWidget(d_boutonAjouter, 0, Qt::AlignLeft | Qt::AlignTop);
    layoutBouton->addWidget(d_boutonModifier, 0, Qt::AlignLeft | Qt::AlignTop);
    layoutBouton->addStretch(1);
    layoutBouton->addWidget(d_boutonSupprimer, 0, Qt::AlignLeft | Qt::AlignTop);
    setLayout(layoutPrincipal);
    DateEtHeure->setChecked(true);
    Date->setEnabled(true);
    Horaire->setEnabled(true);

    d_boutonAjouter->setDefault(true);

    connect(DateEtHeure, &QCheckBox::toggled, this, &dialoguerdv::onDateEtHeureCoche);
    connect(ListeDeroulante, &QComboBox::currentIndexChanged, this, &dialoguerdv::onListeDeroulanteChangee);
    connect(boutonrecherche, &QPushButton::clicked, this, &dialoguerdv::onRechercher);
    connect(boutonReset, &QPushButton::clicked,this,&dialoguerdv::onReset);
    connect(d_boutonSupprimer,&QPushButton::clicked,this,&dialoguerdv::onSupprime);
    connect(d_boutonModifier,&QPushButton::clicked,this,&dialoguerdv::onModifier);
    connect(d_boutonAjouter,&QPushButton::clicked,this,&dialoguerdv::onAjouter);


}
void dialoguerdv::onDateEtHeureCoche(bool checked)
{
    Date->setEnabled(checked);
    Horaire->setEnabled(checked);
}

void dialoguerdv::onListeDeroulanteChangee(int index)
{
    if (index == 0) // "Personne" est sélectionné
    {
        DateEtHeure->setEnabled(true);
        barreRecherche->setPlaceholderText("Nom Prénom");
    }
    else // "Date" est sélectionné
    {
        DateEtHeure->setEnabled(false);
        DateEtHeure->setChecked(false);
        onDateEtHeureCoche(false); // Désactive aussi les champs Date et Horaire
        barreRecherche->setPlaceholderText("dd/mm/yyyy");
    }
}
void dialoguerdv::onRechercher()
{
    // Vérifier si la recherche est par personne
    if (ListeDeroulante->currentIndex() == 0 && !DateEtHeure->isChecked() )  // "Personne" sélectionnée
    {
        QString recherche = barreRecherche->text().trimmed();
        // Vérifier si on a bien deux mots séparés par un espace
        QStringList nomPrenom = recherche.split(" ", Qt::SkipEmptyParts);

        if (nomPrenom.size() != 2)
        {
            QMessageBox::warning(this, "Erreur",
                                 "Veuillez saisir un nom et un prénom séparés par un espace.");
            return;
        }

        QString  nom = nomPrenom[0].toUpper();
        QString prenom = nomPrenom[1].toLower();


        // Appel à la méthode de recherche par personne
        LDC_RDV* result = d_ldcRdv->rechercheRendezVousParPersonne(nom.toStdString(), prenom.toStdString());
        afficherLdcRdv(result);
    }
    // Vérifier si la recherche est par date
    else if (ListeDeroulante->currentIndex() == 1)  // "Date" sélectionnée
    {
        QString dateStr = barreRecherche->text().trimmed();
        QDate date = QDate::fromString(dateStr, "dd/MM/yyyy");

        if (!date.isValid())
        {
            QMessageBox::warning(this, "Erreur", "Veuillez saisir une date valide au format dd/MM/yyyy.");
            return;
        }

        int annee = date.year();
        int mois = date.month();
        int jour = date.day();

        // Appel à la méthode de recherche par date
        LDC_RDV* result = d_ldcRdv->rechercheParDate(annee, mois, jour);
        afficherLdcRdv(result);
    }
    // Vérifier si la recherche est par date et heure et personne  (checkbox cochée)
    else if (DateEtHeure->isChecked())
    {
        // 1. Vérifier le champ nom/prénom
        QString recherche = barreRecherche->text().trimmed();
        QStringList nomPrenom = recherche.split(" ", Qt::SkipEmptyParts);
        if (nomPrenom.size() != 2)
        {
            QMessageBox::warning(this, "Erreur",
                                 "Veuillez saisir un nom et un prénom séparés par un espace.");
            return;
        }
        QString nom = nomPrenom[0].toUpper();
        QString prenom = nomPrenom[1].toLower();

        // 2. Vérifier que la date est saisie et valide
        QString dateStr = Date->text().trimmed();
        QDate date = QDate::fromString(dateStr, "dd/MM/yyyy");
        if (!date.isValid() )
        {
            QMessageBox::warning(this, "Erreur",
                                 "Veuillez saisir une date valide au format dd/MM/yyyy.");
            return;
        }

        // 3. Vérifier que l'heure est saisie et valide
        QString heureStr = Horaire->text().trimmed();
        QTime heure = QTime::fromString(heureStr, "HH:mm");
        if (!heure.isValid())
        {
            QMessageBox::warning(this, "Erreur",
                                 "Veuillez saisir une heure valide au format HH:mm.");
            return;
        }

        // Extraction des composantes de la date
        int annee = date.year();
        int mois = date.month();
        int jour = date.day();

        // Extraction de  horaire pour la recherche
        Heure heureDebut((heure.hour()),
                         (heure.minute()));

        // Appel à la méthode de recherche par personne, date et heure
        LDC_RDV* result = d_ldcRdv->rechercheRendezVousParPersonne(nom.toStdString(), prenom.toStdString(),
                                                                   annee, mois, jour,
                                                                   heureDebut);
        // Affichage des résultats
        afficherLdcRdv(result);
    }
    //else
    //{
    // Si le mode "Date et Heure" n'est pas activé, on peut afficher une information ou gérer un autre cas
    //  QMessageBox::information(this, "Info", "Veuillez cocher le mode de recherche par Date et Heure.");
    //}
}

void dialoguerdv::afficherLdcRdv(LDC_RDV* ldc)
{

    // Vérifier si la liste de rendez-vous est vide
    if (!ldc || !ldc->d_tete)
    {
        //d_boutonSupprimer->setEnabled(false);
        //d_boutonModifier->setEnabled(false);
        //return;
    }

    // Vider le tableau avant de le remplir avec les nouveaux résultats
    d_tbRdv->clearContents();
    d_tbRdv->setRowCount(0);

    // Parcourir les éléments de la liste des rendez-vous et les afficher dans le tableau
    ChainonRDV* crt = ldc->d_tete;
    int ligne = 0;

    while (crt != nullptr)
    {
        // Insérer une nouvelle ligne dans le tableau
        d_tbRdv->insertRow(ligne);

        // Insérer les données des rendez-vous dans les colonnes
        d_tbRdv->setItem(ligne, 0, new QTableWidgetItem(QString::fromStdString(crt->d_Rdv.getnomrdv())));

        // Formater et insérer la date du rendez-vous (jour/mois/année)
        QString dateStr = QString("%1/%2/%3")
                              .arg(crt->d_Rdv.getjours(), 2, 10, QChar('0'))  // Jour sur 2 chiffres
                              .arg(crt->d_Rdv.getmois(), 2, 10, QChar('0'))   // Mois sur 2 chiffres
                              .arg(crt->d_Rdv.getannee(), 4, 10, QChar('0')); // Année sur 4 chiffres
        d_tbRdv->setItem(ligne, 1, new QTableWidgetItem(dateStr));

        // Formater et insérer l'heure du rendez-vous (heure:minute)
        QString heureStrDb = QString("%1:%2")
                                 .arg(crt->d_Rdv.getHeureDebut().heure, 2, 10, QChar('0'))
                                 .arg(crt->d_Rdv.getHeureDebut().minute, 2, 10, QChar('0'));
        d_tbRdv->setItem(ligne, 2, new QTableWidgetItem(heureStrDb));

        QString heureStrFn = QString("%1:%2")
                                 .arg(crt->d_Rdv.getHeureFin().heure, 2, 10, QChar('0'))
                                 .arg(crt->d_Rdv.getHeureFin().minute, 2, 10, QChar('0'));
        d_tbRdv->setItem(ligne, 3, new QTableWidgetItem(heureStrFn));
        // Insérer le nombre de personnes dans le rendez-vous
        d_tbRdv->setItem(ligne, 4, new QTableWidgetItem(QString::number(crt->d_Rdv.retournerNbTb())));

        // Passer au suivant dans la liste
        crt = crt->d_suiv;
        ++ligne;
    }

    // Ajuster les colonnes pour s'adapter au contenu
    d_tbRdv->resizeColumnToContents(3);

    // Activer ou désactiver les boutons en fonction du nombre de résultats
    if (ligne > 0)
    {
        d_boutonSupprimer->setEnabled(true);
        d_boutonModifier->setEnabled(true);
        d_tbRdv->selectRow(0);  // Sélectionner la première ligne par défaut
    }
    else
    {
        d_boutonSupprimer->setEnabled(false);
        d_boutonModifier->setEnabled(false);
    }
}
void dialoguerdv::onReset()
{
    afficherLdcRdv(d_ldcRdv);

}
void dialoguerdv::onSupprime()
{
    QMessageBox Confirmation{QMessageBox::Question, tr("Confirmation"), tr("Êtes-vous sûr de vouloir supprimer ce rendez-vous ?"), QMessageBox::Yes | QMessageBox::No};
    if(Confirmation.exec()==QMessageBox::Yes)
    {
        int ligne = d_tbRdv->selectedItems().first()->row();
        QString nom = d_tbRdv->item(ligne, 0)->text();
        d_ldcRdv->SupprimerRDV(nom.toStdString());
        QMessageBox Supprimee{QMessageBox::Information, tr("Réussite"), tr("Le rendez-vous a bien été supprimée"), QMessageBox::Ok};
        Supprimee.exec();
        afficherLdcRdv(d_ldcRdv);
    }
}
void dialoguerdv::onModifier()
{
    int row = d_tbRdv->currentRow(); // Obtenir l’index de la ligne sélectionnée
    if (row == -1) {
        QMessageBox::warning(this, "Sélection requise", "Veuillez sélectionner une ligne.");
        return;
    }

    // Récupérer la valeur de la première colonne (colonne 0)
    QString nomRDV = d_tbRdv->item(row, 0)->text();
    ChainonRDV* rendezvous= d_ldcRdv->RechercheRDV(nomRDV.toStdString());
    LDC_personne* listvalide = new LDC_personne();
    ChainonDC* tmp=d_ldc_personnes->getTete();
    int i=0;
    while(i<rendezvous->d_Rdv.retournerNbTb())
    {
        listvalide->ajouterPersonne(rendezvous->d_Rdv.retournerValeurTab(i)->getPersonne());
        i++;
    }
    while (tmp != nullptr)
    {
        // Vérifier si la personne est libre à l'heure du rendez-vous
        if (d_ldcRdv->verificationdePersonneEstLibre(tmp->getPersonne().nomDeFamille(), tmp->getPersonne().prenom(),
                                                     rendezvous->d_Rdv.getannee(), rendezvous->d_Rdv.getmois(), rendezvous->d_Rdv.getjours(),
                                                     rendezvous->d_Rdv.getHeureDebut(),rendezvous->d_Rdv.getHeureFin()))
        {
            listvalide->ajouterPersonne(tmp->getPersonne());
        }
        tmp = tmp->getSuivant();
    }
    dialogueModifierRdv dlg{rendezvous,listvalide};
    if(dlg.exec()==QDialog::Accepted)
    {

        QString dateStr = dlg.d_EditDate->text().trimmed();
        QDate date = QDate::fromString(dateStr, "dd/MM/yyyy");

        QString heureDebutStr = dlg.d_EditHeureDebut->text().trimmed();
        QTime heureD = QTime::fromString(heureDebutStr, "HH:mm");

        QString heureFinStr = dlg.d_EditHeureFin->text().trimmed();
        QTime heureF = QTime::fromString(heureFinStr, "HH:mm");

        QTime heureMin(8,0);
        QTime heureMax(18,0);
        bool validInput = true;

        if (dateStr.isEmpty() || !date.isValid()) {
            QMessageBox Erreur(QMessageBox::Critical, tr("Erreur"), tr("La date doit être valide."), QMessageBox::Ok);
            Erreur.exec();
            validInput = false;
        }

        else if (heureDebutStr.isEmpty() || !heureD.isValid()) {
            QMessageBox Erreur(QMessageBox::Critical, tr("Erreur"), tr("L'heure de début doit être valide et respecter le format HH:mm."), QMessageBox::Ok);
            Erreur.exec();
        }
        else if (heureFinStr.isEmpty() || !heureF.isValid()) {
            QMessageBox Erreur(QMessageBox::Critical, tr("Erreur"), tr("L'heure de fin doit être valide et respecter le format HH:mm."), QMessageBox::Ok);
            Erreur.exec();
            validInput = false;
        }

        else if (heureD >= heureF) {
            QMessageBox Erreur(QMessageBox::Critical, tr("Erreur"), tr("L'horaire de début doit être avant l'horaire de fin."), QMessageBox::Ok);
            Erreur.exec();
        }

        else if (heureD < heureMin || heureF > heureMax) {
            QMessageBox Erreur(QMessageBox::Critical, tr("Erreur"), tr("La plage horaire doit être comprise entre 8h et 18h."), QMessageBox::Ok);
            Erreur.exec();
            validInput = false;
        }

        else if (dlg.tableParticipants->rowCount() < 2) {
            QMessageBox Erreur(QMessageBox::Critical, tr("Erreur"), tr("Le rendez-vous doit contenir au moins deux personnes."), QMessageBox::Ok);
            Erreur.exec();
            validInput = false;
        }
        if(validInput)
        {
            rendezvous->d_Rdv.setDate(date.year(), date.month(), date.day());
            Heure heureDebut((heureD.hour()), (heureD.minute()));
            Heure heureFin((heureF.hour()),(heureF.minute()));
            rendezvous->d_Rdv.setHeureDebut(heureDebut);
            rendezvous->d_Rdv.setHeureFin(heureFin);
            //mettre a jour les donnée
            rendezvous->d_Rdv.viderParticipants();
            for (int row = 0; row < dlg.tableParticipants->rowCount(); ++row) {
                QString nom = dlg.tableParticipants->item(row, 0)->text();
                QString prenom = dlg.tableParticipants->item(row, 1)->text();

                // Trouver la personne dans la liste des personnes
                ChainonDC* personneChainon = d_ldc_personnes->trouverPersonne(nom.toStdString(), prenom.toStdString());
                if (personneChainon) {
                    personne p = personneChainon->getPersonne();
                    rendezvous->d_Rdv.ajouterParticipant(&p);
                }
            }

            QMessageBox Information(QMessageBox::Information,
                                    tr("Modification"),
                                    tr("Le rendez-vous a été modifié avec succès."),
                                    QMessageBox::Ok);
            Information.exec();


            afficherLdcRdv(d_ldcRdv);
        }

    }
}
void dialoguerdv::onAjouter()
{
    ajouterrdv dAjoutRDV(d_ldc_personnes, d_ldcRdv);
    if(dAjoutRDV.exec() == QDialog::Accepted)
    {
        QString nomStr = dAjoutRDV.d_EditNom->text().trimmed();

        QString dateStr = dAjoutRDV.d_EditDate->text().trimmed();
        QDate date = QDate::fromString(dateStr, "dd/MM/yyyy");

        QString heureDebutStr = dAjoutRDV.d_EditHeureDebut->text().trimmed();
        QTime heureD = QTime::fromString(heureDebutStr, "HH:mm");

        QString heureFinStr = dAjoutRDV.d_EditHeureFin->text().trimmed();
        QTime heureF = QTime::fromString(heureFinStr, "HH:mm");

        QTime heureMin(8,0);
        QTime heureMax(18,0);

        if (nomStr.isEmpty()) {
            QMessageBox Erreur(QMessageBox::Critical, tr("Erreur"), tr("Le nom ne doit pas être vide."), QMessageBox::Ok);
            Erreur.exec();
        }

        else if (dateStr.isEmpty() || !date.isValid()) {
            QMessageBox Erreur(QMessageBox::Critical, tr("Erreur"), tr("La date doit être valide."), QMessageBox::Ok);
            Erreur.exec();
        }

        else if (heureDebutStr.isEmpty() || !heureD.isValid()) {
            QMessageBox Erreur(QMessageBox::Critical, tr("Erreur"), tr("L'heure de début doit être valide et respecter le format HH:mm."), QMessageBox::Ok);
            Erreur.exec();
        }

        else if (heureFinStr.isEmpty() || !heureF.isValid()) {
            QMessageBox Erreur(QMessageBox::Critical, tr("Erreur"), tr("L'heure de fin doit être valide et respecter le format HH:mm."), QMessageBox::Ok);
            Erreur.exec();
        }

        else if (heureD >= heureF) {
            QMessageBox Erreur(QMessageBox::Critical, tr("Erreur"), tr("L'horaire de début doit être avant l'horaire de fin."), QMessageBox::Ok);
            Erreur.exec();
        }

        else if (heureD < heureMin || heureF > heureMax) {
            QMessageBox Erreur(QMessageBox::Critical, tr("Erreur"), tr("La plage horaire doit être comprise entre 8h et 18h."), QMessageBox::Ok);
            Erreur.exec();
        }

        else if (dAjoutRDV.tableParticipants->rowCount() < 2) {
            QMessageBox Erreur(QMessageBox::Critical, tr("Erreur"), tr("Le rendez-vous doit contenir au moins deux personnes."), QMessageBox::Ok);
            Erreur.exec();
        }
        else
        {
            int annee = date.year();
            int mois = date.month();
            int jour = date.day();

            Heure heureDebut{heureD.hour(), heureD.minute()};

            Heure heureFin{heureF.hour(), heureF.minute()};

            ChainonDC** listePersonnes = new ChainonDC*[dAjoutRDV.tableParticipants->rowCount()+1];

            Rendez_Vous nvRendezVous{dAjoutRDV.d_EditNom->text().toStdString(), annee, mois, jour, heureDebut, heureFin, listePersonnes};

            d_ldcRdv->AjoutRDV(nvRendezVous);

            int rowCount = dAjoutRDV.tableParticipants->rowCount();
            for (int row = 0; row < rowCount; row++)
            {
                QTableWidgetItem* itemNom = dAjoutRDV.tableParticipants->item(row, 0);
                QTableWidgetItem* itemPrenom = dAjoutRDV.tableParticipants->item(row, 1);

                std::string nom = itemNom->text().toStdString();
                std::string prenom = itemPrenom->text().toStdString();

                ChainonDC* personne = d_ldc_personnes->trouverPersonne(nom, prenom);
                d_ldcRdv->ajouterARdv(personne, dAjoutRDV.d_EditNom->text().toStdString());
            }
            afficherLdcRdv(d_ldcRdv);
        }

    }

}






