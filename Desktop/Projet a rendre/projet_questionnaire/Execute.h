#ifndef EXECUTE_H
#define EXECUTE_H

#include "Questionnaire.h"
#include "evaluation.h"
#include "evaluation_test.h"
#include "evaluation_adaptative.h"
#include "evaluation_deuxieme_chance.h"
#include <memory>
#include <string>
#include <fstream>

class Execute {
public:
    Execute();
    ~Execute() = default;
    void lancer();
private:
    void afficherMenuPrincipal();
    int lireChoix(int min, int max);
    void creerQuestionnaire();
    void ajouterQuestion();
    void afficherQuestionnaire();
    void sauvegarderQuestionnaire();
    void chargerQuestionnaire();
    void lancerApprentissage();
    void lancerEvaluation();
    void lancerEvaluationTest();
    void lancerEvaluationAdaptative();
    void lancerEvaluationDeuxiemeChance();
    void executerEvaluation(Evaluation& evaluation);
    void attendreEntree();
    std::vector<std::unique_ptr<Question>> creerCopiesQuestions();
    std::unique_ptr<Questionnaire> d_questionnaire;
    std::string d_nomFichierCourant;
};

#endif // EXECUTE_H

