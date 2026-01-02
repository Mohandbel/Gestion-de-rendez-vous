#include "evaluation.h"


Evaluation::Evaluation(std::vector<std::unique_ptr<Question>> questions)
    : d_listeQuestions(std::move(questions)),
    d_indiceCourant(0),
    d_nbEssais(0),
    d_nbBonnesReponses(0)
{

}


bool Evaluation::aEncoreQuestions() const {

    return d_indiceCourant < static_cast<int>(d_listeQuestions.size());
}

Question* Evaluation::questionCourante() const {
    return aEncoreQuestions() ? d_listeQuestions[d_indiceCourant].get() : nullptr;
}

void Evaluation::questionSuivante() {
    // Vérifie qu'il reste des questions avant d'incrémenter
    if (aEncoreQuestions()) {
        d_indiceCourant++;
    }
}


int Evaluation::nombreQuestions() const {

    return static_cast<int>(d_listeQuestions.size());
}


int Evaluation::nombreEssais() const {
    return d_nbEssais;
}


int Evaluation::nombreBonnesReponses() const {
    return d_nbBonnesReponses;
}
