#include "Execute.h"
#include "QuestionTexte.h"
#include "QuestionNumerique.h"
#include "QuestionQCM.h"
#include <iostream>
#include <vector>
#include <limits> 
#include<string>

Execute::Execute() : d_questionnaire(nullptr) , d_nomFichierCourant("") {
}

void Execute::lancer() {
    std::cout << "" << std::endl;
    std::cout << "   SYSTEME DE GESTION DE QUESTIONNAIRE  " << std::endl;
    std::cout << "" << std::endl;
    std::cout << std::endl;

    bool continuer = true;
    while (continuer) {
        afficherMenuPrincipal();
        int choix = lireChoix(1, 9);

        switch (choix) {
        case 1:
            creerQuestionnaire();
            break;
        case 2:
            if (d_questionnaire) {
                ajouterQuestion();
            }
            else {
                std::cout << "Veuillez d'abord creer un questionnaire (option 1)." << std::endl;
                attendreEntree();
            }
            break;
        case 3:
            if (d_questionnaire) {
                afficherQuestionnaire();
            }
            else {
                std::cout << "Aucun questionnaire disponible." << std::endl;
                attendreEntree();
            }
            break;
        case 4:
            if (d_questionnaire) {
                lancerApprentissage();
            }
            else {
                std::cout << "Aucun questionnaire disponible." << std::endl;
                attendreEntree();
            }
            break;
        case 5:
            if (d_questionnaire) {
                lancerEvaluation();
            }
            else {
                std::cout << "Aucun questionnaire disponible." << std::endl;
                attendreEntree();
            }
            break;
        case 6:
            if (d_questionnaire) {
                sauvegarderQuestionnaire();
            }
            else {
                std::cout << "Aucun questionnaire disponible." << std::endl;
                attendreEntree();
            }
            break;
        case 7:
            chargerQuestionnaire();
            break;
        case 8:
            if (d_questionnaire) {
                std::cout << "Nombre de questions dans le questionnaire: "
                    << d_questionnaire->nombreQuestions() << std::endl;
                attendreEntree();
            }
            else {
                std::cout << "Aucun questionnaire disponible." << std::endl;
                attendreEntree();
            }
            break;
        case 9:
            std::cout << "Au revoir !" << std::endl;
            continuer = false;
            break;
        }
    }
}

void Execute::afficherMenuPrincipal() {
    std::cout << "" << std::endl;
    std::cout << "            MENU PRINCIPAL" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "1. Creer un nouveau questionnaire" << std::endl;
    std::cout << "2. Ajouter une question" << std::endl;
    std::cout << "3. Afficher le questionnaire" << std::endl;
    std::cout << "4. Lancer l'apprentissage" << std::endl;
    std::cout << "5. Lancer une evaluation" << std::endl;
    std::cout << "6. Sauvegarder le questionnaire" << std::endl;
    std::cout << "7. Charger un questionnaire" << std::endl;
    std::cout << "8. Afficher le nombre de questions" << std::endl;
    std::cout << "9. Quitter" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Votre choix (1-9): ";
}

int Execute::lireChoix(int min, int max) {
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore();
    }
    std::string input;
    while (true) {
        std::getline(std::cin, input);
        if (input.empty()) {
            std::cout << "Votre choix : ";
            continue;
        }

        try {
            int choix = std::stoi(input);
            if (choix >= min && choix <= max) {
                return choix; 
            }
            std::cout << ">> Erreur : Le nombre doit etre entre " << min << " et " << max << "." << std::endl;
        }
        catch (...) {
            std::cout << ">> Erreur : Ceci n'est pas un nombre." << std::endl;
        }
        std::cout << "Votre choix : ";
    }
}


void Execute::attendreEntree() {
    std::cout << "\nAppuyez sur Entree pour continuer...";
    std::cin.ignore();
}

void Execute::creerQuestionnaire() {
    std::string titre;
    std::cout << "Entrez le titre du questionnaire: ";
    std::getline(std::cin, titre);
    d_questionnaire = std::make_unique<Questionnaire>(titre);
    std::cout << "Questionnaire cree avec succes !" << std::endl;
    attendreEntree();
}

void Execute::ajouterQuestion() {
    std::cout << "" << std::endl;
    std::cout << "      TYPE DE QUESTION A AJOUTER" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "1. Question texte" << std::endl;
    std::cout << "2. Question numerique" << std::endl;
    std::cout << "3. Question QCM" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Votre choix (1-3): ";

    int type = lireChoix(1, 3);
    std::string intitule, texte;

    std::cout << "Entrez l'intitule de la question: ";
    std::getline(std::cin, intitule);
    std::cout << "Entrez le texte de la question: ";
    std::getline(std::cin, texte);

    std::unique_ptr<Question> question;

    switch (type) {
    case 1: { // Question texte
        std::string bonneReponse;
        std::cout << "Entrez la bonne reponse: ";
        std::getline(std::cin, bonneReponse);
        question = std::make_unique<QuestionTexte>(intitule, texte, bonneReponse);
        break;
    }
    case 2: { // Question numerique
        int bonneReponse, min, max;
        std::cout << "Entrez la bonne reponse (nombre entier): ";
        std::cin >> bonneReponse;
        std::cout << "Entrez la valeur minimum: ";
        std::cin >> min;
        std::cout << "Entrez la valeur maximum: ";
        std::cin >> max;
        std::cin.ignore();
        question = std::make_unique<QuestionNumerique>(intitule, texte, bonneReponse, min, max);
        break;
    }
    case 3: { // Question QCM
        std::vector<std::string> propositions;
        std::cout << "Entrez 4 propositions:" << std::endl;
        for (int i = 1; i <= 4; ++i) {
            std::string prop;
            std::cout << "Proposition " << i << ": ";
            std::getline(std::cin, prop);
            propositions.push_back(prop);
        }
        int bonneReponse;
        std::cout << "Entrez le numero de la bonne reponse (1-4): ";
        std::cin >> bonneReponse;
        std::cin.ignore();
        if (bonneReponse < 1 || bonneReponse > 4) {
            std::cout << "Numero invalide. Utilisation de 1 par defaut." << std::endl;
            bonneReponse = 1;
        }
        question = std::make_unique<QuestionQCM>(intitule, texte, propositions, bonneReponse);
        break;
    }
    }

    d_questionnaire->ajouterQuestion(std::move(question));
    std::cout << "Question ajoutee avec succes !" << std::endl;
    if (!d_nomFichierCourant.empty()) {
        std::cout << "Sauvegarde automatique..." << std::endl;
        sauvegarderQuestionnaire(); 
    }
    attendreEntree();
}

void Execute::afficherQuestionnaire() {
    std::cout << std::endl;
    d_questionnaire->afficher();
    attendreEntree();
}

void Execute::sauvegarderQuestionnaire() {
    if (d_nomFichierCourant.empty()) {
        std::cout << "Entrez le nom du fichier pour sauvegarder: ";
        std::getline(std::cin, d_nomFichierCourant);
    }
    std::ofstream fichier(d_nomFichierCourant);

    if (!fichier.is_open()) {
        std::cout << "Erreur: Impossible d'ouvrir le fichier pour ecriture." << std::endl;
        d_nomFichierCourant.clear();
        attendreEntree();
        return;
    }
    d_questionnaire->ecrire(fichier);
    fichier.close();
    std::cout << "Questionnaire sauvegarde dans '" << d_nomFichierCourant << "'" << std::endl;
}

void Execute::chargerQuestionnaire() {
    std::string nomFichier;
    std::cout << "Entrez le nom du fichier a charger: ";
    std::getline(std::cin, nomFichier);
    std::ifstream fichier(nomFichier);
    if (!fichier.is_open()) {
        std::cout << "Erreur: Impossible d'ouvrir le fichier " << nomFichier << std::endl;
        attendreEntree();
        return;
    }
    try {
        d_questionnaire = std::make_unique<Questionnaire>();
        d_questionnaire->lire(fichier);
        fichier.close();
        d_nomFichierCourant = nomFichier;
        std::cout << "Questionnaire charge avec succes !" << std::endl;
        std::cout << "Titre: " << d_questionnaire->titre() << std::endl;
        std::cout << "Nombre de questions: " << d_questionnaire->nombreQuestions() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Erreur lors du chargement: " << e.what() << std::endl;
        d_questionnaire.reset(); 
    }

    attendreEntree();
}

void Execute::lancerApprentissage() {
    if (d_questionnaire->estVide()) {
        std::cout << "Le questionnaire est vide. Ajoutez des questions d'abord." << std::endl;
        attendreEntree();
        return;
    }

    std::cout << "" << std::endl;
    std::cout << "         MODE APPRENTISSAGE" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Titre du questionnaire: " << d_questionnaire->titre() << std::endl;
    std::cout << std::endl;

    for (std::size_t i = 0; i < d_questionnaire->nombreQuestions(); ++i) {
        const Question& question = d_questionnaire->question(i);


        std::cout << "Question " << (i + 1) << " sur "
            << d_questionnaire->nombreQuestions() << std::endl;
        question.AfficherQuestion();
        std::cout << std::endl;
        std::cout << "Reponse: ";
        question.AfficherReponse();
        std::cout << std::endl;
        if (i < d_questionnaire->nombreQuestions() - 1) {
            attendreEntree();
        }
    }
    std::cout << "" << std::endl;
    std::cout << "     FIN DE L'APPRENTISSAGE" << std::endl;
    std::cout << "" << std::endl;
    attendreEntree();
}

void Execute::lancerEvaluation() {
    if (d_questionnaire->estVide()) {
        std::cout << "Le questionnaire est vide. Ajoutez des questions d'abord." << std::endl;
        attendreEntree();
        return;
    }
    std::cout << "" << std::endl;
    std::cout << "      TYPE D'EVALUATION" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "1. Evaluation Test (une seule tentative)" << std::endl;
    std::cout << "2. Evaluation Adaptative" << std::endl;
    std::cout << "3. Evaluation Deuxieme Chance" << std::endl;
    std::cout << "Votre choix (1-3): ";

    int type = lireChoix(1, 3);

    switch (type) {
    case 1:
        lancerEvaluationTest();
        break;
    case 2:
        lancerEvaluationAdaptative();
        break;
    case 3:
        lancerEvaluationDeuxiemeChance();
        break;
    }
}

std::vector<std::unique_ptr<Question>> Execute::creerCopiesQuestions() {
    std::vector<std::unique_ptr<Question>> copies;
    for (std::size_t i = 0; i < d_questionnaire->nombreQuestions(); ++i) {
        copies.push_back(d_questionnaire->question(i).clone());
    }
    return copies;
}

void Execute::lancerEvaluationTest() {
    std::vector<std::unique_ptr<Question>> questions = creerCopiesQuestions();
    EvaluationTest evaluation(std::move(questions));
    executerEvaluation(evaluation);
}

void Execute::lancerEvaluationAdaptative() {
    std::vector<std::unique_ptr<Question>> questions = creerCopiesQuestions();
    EvaluationAdaptative evaluation(std::move(questions));
    executerEvaluation(evaluation);
}

void Execute::lancerEvaluationDeuxiemeChance() {
    std::vector<std::unique_ptr<Question>> questions = creerCopiesQuestions();
    EvaluationSecondeChance evaluation(std::move(questions));
    executerEvaluation(evaluation);
}

void Execute::executerEvaluation(Evaluation& evaluation) {
    std::cout << "" << std::endl;
    std::cout << "          DEBUT DE L'EVALUATION" << std::endl;
    std::cout << "" << std::endl;
    std::cout << std::endl;

    int numeroQuestion = 1;

    while (evaluation.aEncoreQuestions()) {
        Question* question = evaluation.questionCourante();
        if (!question) break;

        std::cout << "Question " << numeroQuestion
            << " sur " << evaluation.nombreQuestions() << std::endl;
        question->AfficherQuestion();
        std::cout << std::endl;

        std::string reponse;

        if (std::cin.fail()) { std::cin.clear(); std::cin.ignore(); }
        std::getline(std::cin, reponse);

        bool afficherBonneReponse = false;
        bool correcte = evaluation.repondre(reponse, afficherBonneReponse);

        if (correcte) {
            std::cout << "Bravo ! Bonne reponse !" << std::endl;
            evaluation.questionSuivante();
            numeroQuestion++;
        }
        else {
            std::cout << "Mauvaise reponse." << std::endl;

            if (afficherBonneReponse) {
                question->AfficherReponse();
                evaluation.questionSuivante();
                numeroQuestion++;
            }
            else {
                std::cout << ">> Retentez votre chance !" << std::endl;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "          FIN DE L'EVALUATION" << std::endl;
    std::cout << "Nombre de bonnes reponses: " << evaluation.nombreBonnesReponses()
        << " / " << evaluation.nombreQuestions() << std::endl;
    std::cout << "Nombre total d'essais: " << evaluation.nombreEssais() << std::endl;
    double pourcentage = (evaluation.nombreQuestions() > 0) ?
        (100.0 * evaluation.nombreBonnesReponses() / evaluation.nombreQuestions()) : 0.0;
    std::cout << "Score: " << pourcentage << "%" << std::endl;

    attendreEntree();
}

