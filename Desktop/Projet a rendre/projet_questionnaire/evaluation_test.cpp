#include "evaluation_test.h"

EvaluationTest::EvaluationTest(std::vector<std::unique_ptr<Question>> questions)
    : Evaluation(std::move(questions))
{

}

bool EvaluationTest::repondre(const std::string& reponseUtilisateur,
    bool& afficherBonneReponse)
{

    d_nbEssais++;

    Question* q = questionCourante();

    // Vérification de sécurité
    if (!q) {
        afficherBonneReponse = false;
        return false;
    }

    // Vérifier la réponse via la méthode de la classe Question
    bool correcte = q->verifierReponse(reponseUtilisateur);

    // Si correcte, incrémenter le compteur
    if (correcte) {
        d_nbBonnesReponses++;
        afficherBonneReponse = false;
    }
    else
    {
        //  on n'affiche JAMAIS la bonne réponse
        afficherBonneReponse = true;
    }

    return correcte;
}


