#include "QuestionQCM.h"
#include <cstdlib>
#include <vector>
#include <iostream>

QuestionQCM::QuestionQCM(const std::string& intitule,
    const std::string& texte,
    const std::vector<std::string>& propositions,
    int bonneReponse)
    : Question(intitule, texte),
    d_propositions(propositions),
    d_bonneReponse(bonneReponse-1)
{
}

bool QuestionQCM::verifierReponse( const std::string& rep) const {
    try {
        int valeur = std::stoi(rep);
        return (valeur-1) == d_bonneReponse;
    }
    catch (...) {
        return false;
    }
}

void QuestionQCM::AfficherQuestion() const {
    Question::AfficherQuestion();
    for (size_t i = 0; i < d_propositions.size(); ++i) {
        std::cout << (i + 1) << ". " << d_propositions[i] << std::endl;
    }
}
void QuestionQCM::AfficherReponse() const
{
    std::cout << "La r�ponse est" << d_propositions[d_bonneReponse ] << std::endl;
}
void QuestionQCM::ecrire(std::ostream& os) const
{
    
    os << "QCM" << "\n";

    
    os << d_intitule << "\n"<< d_texte << "\n"<< (d_bonneReponse+1) << "\n" << d_propositions.size() << "\n";

    
    for (const auto& choix : d_propositions) {
        os << choix << "\n";
    }
}
const std::vector<std::string>& QuestionQCM::propositions() const 
{
    return d_propositions; 
}

int QuestionQCM::bonneReponse() const
{
    return d_bonneReponse; 
}
std::unique_ptr<Question> QuestionQCM::clone() const {
    return std::make_unique<QuestionQCM>(*this); // Utilise le constructeur de copie par d�faut
}