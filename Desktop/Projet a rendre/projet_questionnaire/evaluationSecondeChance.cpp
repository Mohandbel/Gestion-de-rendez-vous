#include "EvaluationSecondeChance.h"
EvaluationSecondeChance::EvaluationSecondeChance(std::vector<std::unique_ptr<Question>> questions)
    : Evaluation(std::move(questions)), d_deuxiemeEssai(false)
{}
bool EvaluationSecondeChance::repondre(const std::string& reponseUtilisateur, bool& afficherBonneReponse) {
    Question* q = questionCourante();
    if (!q) return false;
    bool estCorrecte = q->verifierReponse(reponseUtilisateur);
    d_nbEssais++;

    if (estCorrecte) {
        d_nbBonnesReponses++;
        d_deuxiemeEssai = false;
        afficherBonneReponse = false;
        return true;
    } else {
        if (!d_deuxiemeEssai) {
            d_deuxiemeEssai = true;
            afficherBonneReponse = false;
            return false;
        } else {
            d_deuxiemeEssai = false;
            afficherBonneReponse = true;
            return false;
        }
    }
}

void EvaluationSecondeChance::questionSuivante() {
    Evaluation::questionSuivante();
    d_deuxiemeEssai = false;
}
