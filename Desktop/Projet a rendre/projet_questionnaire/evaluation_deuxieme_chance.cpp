#include "evaluation_deuxieme_chance.h"

EvaluationSecondeChance::EvaluationSecondeChance(
        std::vector<std::unique_ptr<Question>> questions)
    : Evaluation(std::move(questions)) {}

bool EvaluationSecondeChance::repondre(const std::string& reponseUtilisateur,
                                       bool& afficherBonneReponse)
{
    d_nbEssais++;

    Question* q = questionCourante();
    if (!q) {
        afficherBonneReponse = false;
        return false;
    }

    bool correcte = q->verifierReponse(reponseUtilisateur);

    if (correcte) {
        d_nbBonnesReponses++;
        afficherBonneReponse = false;
        d_deuxiemeEssai = false;
        return true;
    }

    // Réponse mauvaise
    if (!d_deuxiemeEssai) {
        // On accorde une seconde tentative
        d_deuxiemeEssai = true;
        afficherBonneReponse = false;
        return false;
    }

    // Deuxième essai raté → on affiche la bonne réponse
    afficherBonneReponse = true;
    d_deuxiemeEssai = false;
    return false;
}

void EvaluationSecondeChance::questionSuivante() {
    d_indiceCourant++;
    d_deuxiemeEssai = false; // reset
}
