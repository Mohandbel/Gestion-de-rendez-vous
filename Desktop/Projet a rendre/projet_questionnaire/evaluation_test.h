
#ifndef EVALUATION_TEST_H
#define EVALUATION_TEST_H

#include "evaluation.h"



//Chaque question est posée une seule fois dans l'ordre
 //Les bonnes réponses ne sont jamais affichées


class EvaluationTest : public Evaluation {
public:

    explicit EvaluationTest(std::vector<std::unique_ptr<Question>> questions);


    bool repondre(const std::string& reponseUtilisateur,
        bool& afficherBonneReponse) override;
};

#endif 

