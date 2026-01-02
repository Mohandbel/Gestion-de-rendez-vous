#include "doctest.h"
#include "Evaluation.h"
#include "EvaluationTest.h"
#include "QuestionTexte.h"
#include "QuestionNumerique.h"
#include <memory>
#include <vector>

// Tests pour EvaluationTest

TEST_CASE("EvaluationTest - Construction avec plusieurs questions") {
    std::vector<std::unique_ptr<Question>> questions;
    questions.push_back(std::make_unique<QuestionTexte>(
        "Q1", "Capitale de la France?", "Paris"));
    questions.push_back(std::make_unique<QuestionTexte>(
        "Q2", "Capitale de l'Italie?", "Rome"));

    EvaluationTest eval(std::move(questions));

    CHECK(eval.nombreQuestions() == 2);
    CHECK(eval.nombreEssais() == 0);
    CHECK(eval.nombreBonnesReponses() == 0);
    CHECK(eval.aEncoreQuestions() == true);
}

TEST_CASE("EvaluationTest - Réponse correcte") {
    std::vector<std::unique_ptr<Question>> questions;
    questions.push_back(std::make_unique<QuestionTexte>(
        "Q1", "Test question?", "reponse_correcte"));

    EvaluationTest eval(std::move(questions));

    bool afficherBonneReponse = true;
    bool resultat = eval.repondre("reponse_correcte", afficherBonneReponse);

    CHECK(resultat == true);
    CHECK(afficherBonneReponse == false);  // Jamais d'affichage en mode test
    CHECK(eval.nombreEssais() == 1);
    CHECK(eval.nombreBonnesReponses() == 1);
}

TEST_CASE("EvaluationTest - Réponse incorrecte") {
    std::vector<std::unique_ptr<Question>> questions;
    questions.push_back(std::make_unique<QuestionTexte>(
        "Q1", "Question?", "bonne_reponse"));

    EvaluationTest eval(std::move(questions));

    bool afficherBonneReponse = true;
    bool resultat = eval.repondre("mauvaise_reponse", afficherBonneReponse);

    CHECK(resultat == false);
    CHECK(afficherBonneReponse == false);  // Toujours false en mode test
    CHECK(eval.nombreEssais() == 1);
    CHECK(eval.nombreBonnesReponses() == 0);
}

TEST_CASE("EvaluationTest - Ordre des questions préservé") {
    std::vector<std::unique_ptr<Question>> questions;
    questions.push_back(std::make_unique<QuestionTexte>("Q1", "Question 1?", "r1"));
    questions.push_back(std::make_unique<QuestionTexte>("Q2", "Question 2?", "r2"));
    questions.push_back(std::make_unique<QuestionTexte>("Q3", "Question 3?", "r3"));

    EvaluationTest eval(std::move(questions));

    // Vérifier l'ordre
    CHECK(eval.questionCourante()->intitule() == "Q1");
    eval.questionSuivante();

    CHECK(eval.questionCourante()->intitule() == "Q2");
    eval.questionSuivante();

    CHECK(eval.questionCourante()->intitule() == "Q3");
}

TEST_CASE("EvaluationTest - Navigation complète") {
    std::vector<std::unique_ptr<Question>> questions;
    for (int i = 1; i <= 5; ++i) {
        questions.push_back(std::make_unique<QuestionTexte>(
            "Q" + std::to_string(i),
            "Question " + std::to_string(i) + "?",
            "rep" + std::to_string(i)));
    }

    EvaluationTest eval(std::move(questions));

    int compteur = 0;
    while (eval.aEncoreQuestions()) {
        compteur++;
        eval.questionSuivante();
    }

    CHECK(compteur == 5);
    CHECK(eval.questionCourante() == nullptr);
}

TEST_CASE("EvaluationTest - Statistiques après plusieurs réponses") {
    std::vector<std::unique_ptr<Question>> questions;
    questions.push_back(std::make_unique<QuestionTexte>("Q1", "Q1?", "r1"));
    questions.push_back(std::make_unique<QuestionTexte>("Q2", "Q2?", "r2"));
    questions.push_back(std::make_unique<QuestionTexte>("Q3", "Q3?", "r3"));
    questions.push_back(std::make_unique<QuestionTexte>("Q4", "Q4?", "r4"));

    EvaluationTest eval(std::move(questions));

    bool afficher;

    // Q1: correcte
    eval.repondre("r1", afficher);
    eval.questionSuivante();

    // Q2: incorrecte
    eval.repondre("mauvaise", afficher);
    eval.questionSuivante();

    // Q3: correcte
    eval.repondre("r3", afficher);
    eval.questionSuivante();

    // Q4: incorrecte
    eval.repondre("mauvaise", afficher);
    eval.questionSuivante();

    CHECK(eval.nombreQuestions() == 4);
    CHECK(eval.nombreEssais() == 4);
    CHECK(eval.nombreBonnesReponses() == 2);
}

TEST_CASE("EvaluationTest - Avec questions numériques") {
    std::vector<std::unique_ptr<Question>> questions;
    questions.push_back(std::make_unique<QuestionNumerique>(
        "Q1", "2 + 2 = ?", 4, 0, 10));
    questions.push_back(std::make_unique<QuestionNumerique>(
        "Q2", "5 * 3 = ?", 15, 0, 100));

    EvaluationTest eval(std::move(questions));

    bool afficher;

    // Bonne réponse
    CHECK(eval.repondre("4", afficher) == true);
    CHECK(afficher == false);
    eval.questionSuivante();

    // Mauvaise réponse
    CHECK(eval.repondre("20", afficher) == false);
    CHECK(afficher == false);

    CHECK(eval.nombreBonnesReponses() == 1);
}

TEST_CASE("EvaluationTest - Évaluation vide") {
    std::vector<std::unique_ptr<Question>> questions;

    EvaluationTest eval(std::move(questions));

    CHECK(eval.nombreQuestions() == 0);
    CHECK(eval.aEncoreQuestions() == false);
    CHECK(eval.questionCourante() == nullptr);
}

TEST_CASE("EvaluationTest - Score parfait") {
    std::vector<std::unique_ptr<Question>> questions;
    questions.push_back(std::make_unique<QuestionTexte>("Q1", "Q1?", "r1"));
    questions.push_back(std::make_unique<QuestionTexte>("Q2", "Q2?", "r2"));
    questions.push_back(std::make_unique<QuestionTexte>("Q3", "Q3?", "r3"));

    EvaluationTest eval(std::move(questions));

    bool afficher;
    eval.repondre("r1", afficher);
    eval.questionSuivante();

    eval.repondre("r2", afficher);
    eval.questionSuivante();

    eval.repondre("r3", afficher);
    eval.questionSuivante();

    CHECK(eval.nombreBonnesReponses() == 3);
    CHECK(eval.nombreEssais() == 3);
}

TEST_CASE("EvaluationTest - Score nul") {
    std::vector<std::unique_ptr<Question>> questions;
    questions.push_back(std::make_unique<QuestionTexte>("Q1", "Q1?", "r1"));
    questions.push_back(std::make_unique<QuestionTexte>("Q2", "Q2?", "r2"));

    EvaluationTest eval(std::move(questions));

    bool afficher;
    eval.repondre("mauvaise1", afficher);
    eval.questionSuivante();

    eval.repondre("mauvaise2", afficher);
    eval.questionSuivante();

    CHECK(eval.nombreBonnesReponses() == 0);
    CHECK(eval.nombreEssais() == 2);
}
