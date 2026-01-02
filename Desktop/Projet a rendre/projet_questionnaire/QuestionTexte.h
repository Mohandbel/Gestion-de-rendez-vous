#ifndef QUESTION_TEXTE_H
#define QUESTION_TEXTE_H

#include "Question.h"
#include<string>
#include<memory>

class QuestionTexte : public Question {
public:
    QuestionTexte(const std::string& intitule,
         const std::string& texte,
         const std::string& bonneReponse);

     void AfficherQuestion()const  override;
     bool verifierReponse(const std::string& reponseUtilisateur) const override;
     void AfficherReponse() const override;
     void ecrire(std::ostream& os)const override;
     std::string bonneReponse() const;
     std::unique_ptr<Question> clone() const override;

private:
    std::string d_bonneReponse;
};

#endif