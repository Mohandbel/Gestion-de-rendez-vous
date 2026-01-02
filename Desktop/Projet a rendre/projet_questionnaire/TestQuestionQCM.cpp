#include"doctest.h"
#include"QuestionQCM.h"
#include<vector>
#include <stdexcept>
// test QCM : je verifie juste si ça prend le bon numero
TEST_CASE("QuestionQCM : petit test") {

    std::vector<std::string> propositions{
        "Rouge", "Bleu", "Vert", "Jaune"
    };

    QuestionQCM q("QuestionQCM", "Quelle est la couleur du ciel ?", propositions, 2);
    SUBCASE("Verification de constructeur")
    {
        CHECK(q.getIntitule() == "QuestionQCM");
        CHECK(q.getTexte() == "Quelle est la couleur du ciel ?");
    }
    SUBCASE("Verification de reponse")
    {
        REQUIRE_UNARY(q.verifierReponse("2")); //bon
        REQUIRE_UNARY_FALSE(q.verifierReponse("1")); // non
        REQUIRE_UNARY_FALSE(q.verifierReponse("5")); // hors props
        REQUIRE_UNARY_FALSE(q.verifierReponse("abc")); // also not a number
    }
    SUBCASE("Le constructeur rejette nombre pas bon de choix")
    {
        std::vector<std::string>troisChoix={ "A","B","C" };
        CHECK_THROWS_AS(QuestionQCM("Titre", "Texte", troisChoix, 1), std::invalid_argument);
    }
}