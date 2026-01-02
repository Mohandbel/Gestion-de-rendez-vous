

#ifndef EVALUATION_H
#define EVALUATION_H

#include <vector>
#include <memory>
#include <string>
#include "Question.h"

class Evaluation {
protected:

    std::vector<std::unique_ptr<Question>> d_listeQuestions;


    int d_indiceCourant;


    int d_nbEssais;


    int d_nbBonnesReponses;

public:

    explicit Evaluation(std::vector<std::unique_ptr<Question>> questions);


    virtual ~Evaluation() = default;

    bool aEncoreQuestions() const;


    Question* questionCourante() const;


    virtual bool repondre(const std::string& reponseUtilisateur, bool& afficherBonneReponse) = 0;


    virtual void questionSuivante();


    int nombreQuestions() const;

    int nombreEssais() const;


    int nombreBonnesReponses() const;
};

#endif // EVALUATION_H
