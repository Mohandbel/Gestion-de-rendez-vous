#include "doctest.h"
#include "EvaluationSecondeChance.h"
#include "QuestionTexte.h"
TEST_CASE("gestion du premier echec") {
    std::vector<std::unique_ptr<Question>> questions;
    questions.push_back(std::make_unique<QuestionTexte>("q1", "paris?", "paris"));
    EvaluationSecondeChance eval(std::move(questions));
    bool afficher = false;
    CHECK(eval.repondre("lyon", afficher) == false);
    CHECK(afficher == false);
    CHECK(eval.nombreEssais() == 1);
}
TEST_CASE("reussite au deuxieme essai") {
    std::vector<std::unique_ptr<Question>> questions;
    questions.push_back(std::make_unique<QuestionTexte>("q1", "paris?", "paris"));
    EvaluationSecondeChance eval(std::move(questions));
    bool afficher;
    eval.repondre("lyon", afficher);
    bool resultat = eval.repondre("paris", afficher);
    CHECK(resultat == true);
    CHECK(eval.nombreBonnesReponses() == 1);
    CHECK(eval.nombreEssais() == 2);
}

TEST_CASE("echec définitif apres deux essais") {
    std::vector<std::unique_ptr<Question>> questions;
    questions.push_back(std::make_unique<QuestionTexte>("q1", "paris?", "paris"));
    EvaluationSecondeChance eval(std::move(questions));
    bool afficher;
    eval.repondre("erreur 1", afficher);
    bool resultatFinal = eval.repondre("erreur 2", afficher);
    CHECK(resultatFinal == false);
    CHECK(afficher == true);
}
