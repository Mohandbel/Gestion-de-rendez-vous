
#include"doctest.h"
#include"QuestionTexte.h"
TEST_CASE("test de la class question texte")
{
    QuestionTexte q1("Capitale", "Quelle est la capitale de la France", "Paris");
    SUBCASE("Le constructeur fonctionne")
        {
    CHECK(q1.getIntitule() == "Capitale");
    CHECK(q1.getTexte() == "Quelle est la capitale de la France");
        }
    SUBCASE("La verification de la reponse fonctionne")
        {
        REQUIRE_UNARY(q1.verifierReponse("Paris"));
        REQUIRE_UNARY_FALSE(q1.verifierReponse("Berlin"));
        }
}