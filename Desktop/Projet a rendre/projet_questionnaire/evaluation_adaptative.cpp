#include "evaluation_adaptative.h"

EvaluationAdaptative::EvaluationAdaptative(std::vector<std::unique_ptr<Question>> questions)
    : Evaluation(std::move(questions)),
    d_dernierReponseCorrecte(false)
{
    std::random_device rd; // std::random_device : source d’aléatoire du système
    std::mt19937 rng(rd()); // std::mt19937 : moteur aléatoire moderne (Mersenne Twister)On utilise ce moteur pour bien mélanger
    std::shuffle(d_listeQuestions.begin(), d_listeQuestions.end(), rng);// Mélange toutes les questions au hasard
}

bool EvaluationAdaptative::repondre(const std::string& reponseUtilisateur,
    bool& afficherBonneReponse)
{
    d_nbEssais++;

    Question* q = questionCourante();
    if (!q) {
        afficherBonneReponse = false;
        return false;
    }

    bool correcte = q->verifierReponse(reponseUtilisateur); 
    d_dernierReponseCorrecte = correcte;

    if (correcte) {
        d_nbBonnesReponses++;
        afficherBonneReponse = false;  
    }
    else {
        // Déplacer la question incorrecte à la fin
        std::unique_ptr<Question> aReposer = std::move(d_listeQuestions[d_indiceCourant]);
        d_listeQuestions.erase(d_listeQuestions.begin() + d_indiceCourant);
        d_listeQuestions.push_back(std::move(aReposer));

        // On peut afficher la bonne réponse, selon  notre choix 
        afficherBonneReponse = true;
    }

    return correcte;
}

void EvaluationAdaptative::questionSuivante()
{
    // Si la dernière réponse était correcte, on avance
    // Sinon, la question a été déplacée et la suivante est déjà en place
    if (d_dernierReponseCorrecte && aEncoreQuestions()) {
        d_indiceCourant++;
    }
}
