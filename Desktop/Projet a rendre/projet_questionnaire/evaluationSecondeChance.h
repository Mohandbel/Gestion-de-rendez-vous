#ifndef EVALUATIONSECONDECHANCE_H
#define EVALUATIONSECONDECHANCE_H
#include "Evaluation.h"
#include <vector>
#include <memory>
#include <string>
class EvaluationSecondeChance : public Evaluation {
public:
    EvaluationSecondeChance(std::vector<std::unique_ptr<Question>> questions);
    bool repondre(const std::string& reponseUtilisateur, bool& afficherBonneReponse) override;
    void questionSuivante() override;

private:
    bool d_deuxiemeEssai;
};

#endif
