#include "QuestionNumerique.h"
#include <cstdlib> 
#include <stdexcept>
#include <iostream>

QuestionNumerique::QuestionNumerique(const std::string& intitule,
    const std::string& texte,
    int bonneReponse,
    int min,
    int max)
    : Question(intitule, texte),
    d_bonneReponse(bonneReponse),
    d_min(min),
    d_max(max)
{
}

bool QuestionNumerique::verifierReponse(const std::string & reponseUtilisateur) const {
    try {
        int valeur = std::stoi(reponseUtilisateur);

        if (valeur < d_min || valeur > d_max)
            return false;

        return valeur == d_bonneReponse;
    }
    catch (...) {
        return false;
    }
}

void QuestionNumerique::AfficherQuestion() const {
    Question::AfficherQuestion();
    std::cout << "(R�ponse attendue entre " << d_min
        << " et " << d_max << ")" << std::endl;
}

void QuestionNumerique::AfficherReponse() const
{
    std::cout << "La reponse est :" << d_bonneReponse << std::endl;
}

int QuestionNumerique::max()const
{
    return d_max;
}

int QuestionNumerique::min() const
{
    return d_min;
}

void QuestionNumerique::ecrire(std::ostream& os)const
{
    os << "N" << "\n" << d_intitule << "\n" << d_texte << "\n" << d_bonneReponse << "\n" << d_min << "\n" << d_max << std::endl;
}

int QuestionNumerique::bonneReponse() const 
{ 
    return d_bonneReponse;
}

std::unique_ptr<Question> QuestionNumerique::clone() const {
    return std::make_unique<QuestionNumerique>(*this); // Utilise le constructeur de copie par d�faut
}