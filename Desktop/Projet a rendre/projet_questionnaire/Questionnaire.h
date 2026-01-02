
#ifndef QUESTIONNAIRE_H
#define QUESTIONNAIRE_H

#include <vector>
#include <memory>
#include <string>
#include <ostream>
#include <istream>

#include "Question.h"

class Questionnaire
{
public:
   
    explicit Questionnaire(const std::string& titre = "");

   
    std::string titre() const;
    void setTitre(const std::string& titre);

    
    std::size_t nombreQuestions() const;
    bool estVide() const;

    
    void ajouterQuestion(std::unique_ptr<Question> question);

    Question& question(std::size_t index);
    const Question& question(std::size_t index) const;

    
    void afficher() const;

   
    void ecrire(std::ostream& flux) const;
    void lire(std::istream& flux);

private:
    void validerIndex(std::size_t index) const;

    std::string d_titre;
    std::vector<std::unique_ptr<Question>> d_questions;
};

#endif // QUESTIONNAIRE_H