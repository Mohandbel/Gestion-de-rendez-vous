#include "doctest.h"
#include "evaluation_adaptative.h"
#include "QuestionTexte.h"
#include "QuestionNumerique.h"
#include <memory>
#include <vector>



TEST_CASE("EvaluationAdaptative - Construction") {
    std::vector<std::unique_ptr<Question>> questions;
    questions.push_back(std::make_unique<QuestionTexte>(
        "Q1", "Question 1?", "rep1"));
    questions.push_back(std::make_unique<QuestionTexte>(
        "Q2", "Question 2?", "rep2"));

    EvaluationAdaptative eval(std::move(questions));

    CHECK(eval.nombreQuestions() == 2);
    CHECK(eval.nombreEssais() == 0);
    CHECK(eval.nombreBonnesReponses() == 0);
    CHECK(eval.aEncoreQuestions() == true);
}

TEST_CASE("EvaluationAdaptative - Affichage après erreur") {
    std::vector<std::unique_ptr<Question>> questions;
    questions.push_back(std::make_unique<QuestionTexte>(
        "Q1", "Question?", "bonne_reponse"));

    EvaluationAdaptative eval(std::move(questions));

    bool afficherBonneReponse = false;
    bool resultat = eval.repondre("mauvaise_reponse", afficherBonneReponse);

    CHECK(resultat == false);
    CHECK(afficherBonneReponse == true);  // Doit afficher en mode adaptatif
}

TEST_CASE("EvaluationAdaptative - Pas d'affichage si correct") {
    std::vector<std::unique_ptr<Question>> questions;
    questions.push_back(std::make_unique<QuestionTexte>(
        "Q1", "Question?", "bonne_reponse"));

    EvaluationAdaptative eval(std::move(questions));

    bool afficherBonneReponse = true;
    bool resultat = eval.repondre("bonne_reponse", afficherBonneReponse);

    CHECK(resultat == true);
    CHECK(afficherBonneReponse == false);  // Pas d'affichage si correct
}

TEST_CASE("EvaluationAdaptative - Repositionnement après erreur") {
    std::vector<std::unique_ptr<Question>> questions;
    questions.push_back(std::make_unique<QuestionTexte>("Q1", "Question 1?", "r1"));
    questions.push_back(std::make_unique<QuestionTexte>("Q2", "Question 2?", "r2"));
    questions.push_back(std::make_unique<QuestionTexte>("Q3", "Question 3?", "r3"));

    EvaluationAdaptative eval(std::move(questions));

    bool afficher;

    // Récupérer la première question
    Question* q1 = eval.questionCourante();
    std::string intitule1 = q1->Intitule();

    // Répondre incorrectement
    eval.repondre("mauvaise", afficher);
    eval.questionSuivante();

    // La question courante ne devrait PAS être la même qu'avant
    Question* q2 = eval.questionCourante();
    CHECK(q1 != q2);

    // La question mal répondue devrait être repositionnée
    CHECK(eval.nombreQuestions() == 3);  // Toujours 3 questions
}

TEST_CASE("EvaluationAdaptative - Questions mélangées au départ") {
    // On ne peut pas tester directement l'aléatoire, 
    // mais on peut vérifier que toutes les questions sont présentes
    std::vector<std::unique_ptr<Question>> questions;
    questions.push_back(std::make_unique<QuestionTexte>("Q1", "Q1?", "r1"));
    questions.push_back(std::make_unique<QuestionTexte>("Q2", "Q2?", "r2"));
    questions.push_back(std::make_unique<QuestionTexte>("Q3", "Q3?", "r3"));

    EvaluationAdaptative eval(std::move(questions));

    // Vérifier que le nombre de questions est correct
    CHECK(eval.nombreQuestions() == 3);
    CHECK(eval.aEncoreQuestions() == true);
}

TEST_CASE("EvaluationAdaptative - Statistiques avec repositionnement") {
    std::vector<std::unique_ptr<Question>> questions;
    questions.push_back(std::make_unique<QuestionTexte>("Q1", "Q1?", "r1"));
    questions.push_back(std::make_unique<QuestionTexte>("Q2", "Q2?", "r2"));

    EvaluationAdaptative eval(std::move(questions));

    bool afficher;

    // Première question - mauvaise réponse
    eval.repondre("mauvaise", afficher);
    eval.questionSuivante();

    // Deuxième question - bonne réponse
    eval.repondre("r2", afficher);
    eval.questionSuivante();

    CHECK(eval.nombreEssais() == 2);
    CHECK(eval.nombreBonnesReponses() == 1);
}

TEST_CASE("EvaluationAdaptative - Réponse correcte avance normalement") {
    std::vector<std::unique_ptr<Question>> questions;
    questions.push_back(std::make_unique<QuestionTexte>("Q1", "Q1?", "r1"));
    questions.push_back(std::make_unique<QuestionTexte>("Q2", "Q2?", "r2"));

    EvaluationAdaptative eval(std::move(questions));

    bool afficher;

    // Bonne réponse à la première question
    CHECK(eval.repondre("r1", afficher) == true);
    CHECK(afficher == false);

    eval.questionSuivante();

    // On doit avoir avancé
    CHECK(eval.aEncoreQuestions() == true);
}

TEST_CASE("EvaluationAdaptative - Avec questions numériques") {
    std::vector<std::unique_ptr<Question>> questions;
    questions.push_back(std::make_unique<QuestionNumerique>(
        "QNum1", "10 + 5 = ?", 15, 0, 100));
    questions.push_back(std::make_unique<QuestionTexte>(
        "QTxt1", "Capitale France?", "Paris"));

    EvaluationAdaptative eval(std::move(questions));

    bool afficher;

    // Tester avec différents types de questions
    Question* q = eval.questionCourante();

    if (q->Intitule() == "QNum1") {
        CHECK(eval.repondre("15", afficher) == true);
    }
    else {
        CHECK(eval.repondre("Paris", afficher) == true);
    }

    CHECK(afficher == false);  // Pas d'affichage si correct
}

TEST_CASE("EvaluationAdaptative - Plusieurs erreurs consécutives") {
    std::vector<std::unique_ptr<Question>> questions;
    questions.push_back(std::make_unique<QuestionTexte>("Q1", "Q1?", "r1"));
    questions.push_back(std::make_unique<QuestionTexte>("Q2", "Q2?", "r2"));
    questions.push_back(std::make_unique<QuestionTexte>("Q3", "Q3?", "r3"));

    EvaluationAdaptative eval(std::move(questions));

    bool afficher;

    // Trois mauvaises réponses
    eval.repondre("mauvaise1", afficher);
    CHECK(afficher == true);
    eval.questionSuivante();

    eval.repondre("mauvaise2", afficher);
    CHECK(afficher == true);
    eval.questionSuivante();

    eval.repondre("mauvaise3", afficher);
    CHECK(afficher == true);
    eval.questionSuivante();

    // Toutes les questions doivent être repositionnées
    CHECK(eval.nombreEssais() == 3);
    CHECK(eval.nombreBonnesReponses() == 0);
    CHECK(eval.aEncoreQuestions() == true);  // Il reste des questions
}

TEST_CASE("EvaluationAdaptative - Toutes les questions finalement correctes") {
    std::vector<std::unique_ptr<Question>> questions;
    questions.push_back(std::make_unique<QuestionTexte>("Q1", "Q1?", "r1"));

    EvaluationAdaptative eval(std::move(questions));

    bool afficher;

    // Première tentative - mauvaise
    eval.repondre("mauvaise", afficher);
    eval.questionSuivante();

    // La question est repositionnée, on peut la réessayer
    CHECK(eval.aEncoreQuestions() == true);

    // Deuxième tentative - bonne
    eval.repondre("r1", afficher);
    eval.questionSuivante();

    CHECK(eval.nombreEssais() == 2);
    CHECK(eval.nombreBonnesReponses() == 1);
}

TEST_CASE("EvaluationAdaptative - Comparaison avec EvaluationTest") {
    // Test pour montrer la différence de comportement
    std::vector<std::unique_ptr<Question>> questions1;
    questions1.push_back(std::make_unique<QuestionTexte>("Q1", "Q?", "rep"));

    EvaluationAdaptative evalAdapt(std::move(questions1));

    bool afficher;

    // En mode adaptatif, mauvaise réponse = affichage
    evalAdapt.repondre("mauvaise", afficher);
    CHECK(afficher == true);  // Différence clé avec EvaluationTest
}