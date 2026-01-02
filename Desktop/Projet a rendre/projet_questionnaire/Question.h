#ifndef QUESTION_H
#define QUESTION_H
#include <string>
#include<memory>
class Question
{
public:
	Question(  std::string intitule, std::string texte);
	virtual ~Question() = default;
	std::string Intitule()const;
	std::string Texte()const;
	virtual void AfficherQuestion()const;
	virtual bool verifierReponse( const std::string& reponseUtilisateur) const = 0;
	virtual void AfficherReponse() const = 0;
	virtual void ecrire(std::ostream& os)const = 0;
	// utiliser dans Executer pour copie de question inteligent
	virtual std::unique_ptr<Question> clone() const = 0;



protected:
	std::string d_intitule;
	std::string d_texte;

};
#endif //QUESTION_H
