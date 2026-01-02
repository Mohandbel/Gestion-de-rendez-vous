
#ifndef EVALUATION_ADAPTATIVE_H
#define EVALUATION_ADAPTATIVE_H

#include "evaluation.h"
#include <random>
#include <algorithm>

class EvaluationAdaptative : public Evaluation {
private:
    bool d_dernierReponseCorrecte; // Pour savoir si on doit avancer l'indice

public:
    explicit EvaluationAdaptative(std::vector<std::unique_ptr<Question>> questions);

    bool repondre(const std::string& reponseUtilisateur,
        bool& afficherBonneReponse) override;

    void questionSuivante() override;
};

#endif
