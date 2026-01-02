
#include"doctest.h"
#include"QuestionNumerique.h"
TEST_CASE("test de la class Question Numerique")
{
    QuestionNumerique q("QuestionNumerique", "3+4", 7, 0, 10);
    SUBCASE("Le constructeur focntionne")
    {
        CHECK(q.getIntitule() == "QuestionNumerique");
        CHECK(q.getTexte() == "3+4");
    }
    SUBCASE("Verification des bornes")
    {
        REQUIRE_EQ(q.max(),10);
        REQUIRE_EQ(q.min(),0);
    }
    SUBCASE("Gestion des reponse") {
        REQUIRE_UNARY(q.verifierReponse("7")); //ok
        REQUIRE_UNARY_FALSE(q.verifierReponse("8")); // ofcrs wrong
        REQUIRE_UNARY_FALSE(q.verifierReponse("-1"));  // hors limite
        REQUIRE_UNARY_FALSE(q.verifierReponse("abc")); // not even a number
    }
}