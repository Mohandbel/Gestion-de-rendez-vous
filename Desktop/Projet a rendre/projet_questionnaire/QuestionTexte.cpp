#include "QuestionTexte.h"
#include<string>
#include<iostream>

QuestionTexte::QuestionTexte(const std::string& intitule,
    const std::string& texte,
    const std::string& bonneReponse)
    : Question(intitule, texte),
    d_bonneReponse(bonneReponse)
{
}

bool QuestionTexte::verifierReponse(const std::string& reponseUtilisateur) const {
    return reponseUtilisateur == d_bonneReponse;
}

void QuestionTexte::AfficherQuestion() const{
    Question::AfficherQuestion();

}
std::string QuestionTexte::bonneReponse() const 
{ 
    return d_bonneReponse; 
}
void QuestionTexte::AfficherReponse() const
{
    std::cout << "La r�ponse est :" << d_bonneReponse << std::endl;
}
void QuestionTexte::ecrire(std::ostream& os) const
{
    os << "T" << "\n" << d_intitule << "\n" << d_texte << "\n" << d_bonneReponse << std::endl;
}
std::unique_ptr<Question> QuestionTexte::clone() const  {
    return std::make_unique<QuestionTexte>(*this); // Utilise le constructeur de copie par d�faut
}
