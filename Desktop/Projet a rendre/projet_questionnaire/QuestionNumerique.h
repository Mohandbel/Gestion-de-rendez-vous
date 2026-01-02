#ifndef QUESTIONNUMERIQUE_H
#define QUESTIONNUMERIQUE_H
#include"Question.h"
#include<memory>
class QuestionNumerique :public Question
{
public:
    QuestionNumerique(const std::string& intitule,
        const std::string& texte,
        int bonneReponse,
        int min,
        int max);
    int max() const;
    int min()const;

    bool verifierReponse(const std::string &reponseUtilisateur) const override;
    void AfficherQuestion() const override;
    void AfficherReponse() const override;
    void ecrire(std::ostream& os) const override;
    int bonneReponse() const;
    std::unique_ptr<Question> clone() const override;

private:
    int d_bonneReponse;
    int d_min;
    int d_max;
};
#endif //QUESTIONNUMERIQUE_H
