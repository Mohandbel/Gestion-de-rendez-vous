#pragma once
#ifndef EVALUATIONSECONDECHANCE_H
#define EVALUATIONSECONDECHANCE_H

#include "evaluation.h"

class EvaluationSecondeChance : public Evaluation {
private:
    bool d_deuxiemeEssai = false; // indique si on est sur la 2e tentative

public:
    EvaluationSecondeChance(std::vector<std::unique_ptr<Question>> questions);

    bool repondre(const std::string& reponseUtilisateur,
                  bool& afficherBonneReponse) override;

    void questionSuivante() override;
};



#endif // DEUXEMMECHANCE_H_INCLUDED
