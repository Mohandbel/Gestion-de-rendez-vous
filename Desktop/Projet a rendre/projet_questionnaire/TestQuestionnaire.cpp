#include "doctest.h"
#include "Questionnaire.h"
#include "QuestionTexte.h"
#include "QuestionNumerique.h"
#include "QuestionQCM.h"

#include <memory>
#include <sstream>
#include <vector>
#include <iostream>

TEST_CASE("Questionnaire - État initial")
{
    Questionnaire questionnaire{ "Quiz de test" };

    SUBCASE("Un questionnaire vide n'a pas de questions") {
        REQUIRE_EQ(questionnaire.nombreQuestions(), 0);
        REQUIRE_UNARY(questionnaire.estVide());
    }

    SUBCASE("Le titre est correct") {
        REQUIRE_EQ(questionnaire.titre(), "Quiz de test");
    }
}

TEST_CASE("Questionnaire - Ajout de questions")
{
    Questionnaire questionnaire{ "Quiz" };

    questionnaire.ajouterQuestion(
        std::make_unique<QuestionTexte>("Q1", "Quelle est la capitale de la France ?", "Paris")
    );
    questionnaire.ajouterQuestion(
        std::make_unique<QuestionNumerique>("Q2", "Combien font 2+2 ?", 4, 0, 10)
    );

    std::vector<std::string> propositions{ "Rouge", "Bleu", "Vert", "Jaune" };
    questionnaire.ajouterQuestion(
        std::make_unique<QuestionQCM>("Q3", "De quelle couleur est le ciel ?", propositions, 2)
    );

    SUBCASE("Le nombre de questions est correct") {
        REQUIRE_EQ(questionnaire.nombreQuestions(), 3);
        REQUIRE_UNARY_FALSE(questionnaire.estVide());
    }

    SUBCASE("Les questions sont accessibles") {
        REQUIRE_EQ(questionnaire.question(0).Intitule(), "Q1");
        REQUIRE_EQ(questionnaire.question(1).Intitule(), "Q2");
        REQUIRE_EQ(questionnaire.question(2).Intitule(), "Q3");
    }
}

TEST_CASE("Questionnaire - Accès invalide")
{
    Questionnaire questionnaire{ "Quiz" };

    SUBCASE("Accéder à une question inexistante lance une exception") {
        REQUIRE_THROWS(questionnaire.question(0));
        REQUIRE_THROWS(questionnaire.question(10));
    }
}

TEST_CASE("Questionnaire - Sauvegarde")
{
    Questionnaire questionnaire{ "Quiz de géographie" };
    questionnaire.ajouterQuestion(
        std::make_unique<QuestionTexte>("Capitale", "Capitale de la France ?", "Paris")
    );

    std::ostringstream flux;
    questionnaire.ecrire(flux);

    std::string contenu = flux.str();

    SUBCASE("Le titre est présent dans la sauvegarde") {
        REQUIRE_UNARY(contenu.find("Quiz de géographie") != std::string::npos);
    }

    SUBCASE("Le nombre de questions est présent") {
        REQUIRE_UNARY(contenu.find("1") != std::string::npos);
    }
}

TEST_CASE("Questionnaire - Sauvegarde et chargement")
{
    Questionnaire questionnaireOriginal{ "Mon Quiz" };

    questionnaireOriginal.ajouterQuestion(
        std::make_unique<QuestionTexte>("Q1", "Capitale ?", "Paris")
    );

    std::vector<std::string> propositions{ "Rouge", "Bleu", "Vert", "Jaune" };
    questionnaireOriginal.ajouterQuestion(
        std::make_unique<QuestionQCM>("Q2", "Couleur du ciel ?", propositions, 2)
    );

    SUBCASE("Le questionnaire chargé est identique à l'original") {
        std::ostringstream fluxSortie;
        questionnaireOriginal.ecrire(fluxSortie);

        Questionnaire questionnaireCharge;
        std::istringstream fluxEntree{ fluxSortie.str() };
        questionnaireCharge.lire(fluxEntree);

        REQUIRE_EQ(questionnaireCharge.titre(), "Mon Quiz");
        REQUIRE_EQ(questionnaireCharge.nombreQuestions(), 2);
        REQUIRE_EQ(questionnaireCharge.question(0).Intitule(), "Q1");
        REQUIRE_EQ(questionnaireCharge.question(1).Intitule(), "Q2");
    }
}

TEST_CASE("Questionnaire - Modification du titre")
{
    Questionnaire questionnaire{ "Titre initial" };

    SUBCASE("Le titre peut être modifié") {
        questionnaire.setTitre("Nouveau titre");
        REQUIRE_EQ(questionnaire.titre(), "Nouveau titre");
    }
}


