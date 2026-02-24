#ifndef PERSONNE_H
#define PERSONNE_H
#include<string>
#include <cctype>

class personne
{

public:
    personne(const std::string& nom, const std::string& prenom, const std::string& numero, const std::string& adresseMail);
    std::string nomDeFamille() const;
    std::string prenom() const;
    std::string numeroTel() const;
    std::string adresseMail() const;
    bool setNum(const std::string& numero);
    bool setAdresseMail(const std::string& adresseMail);
    bool personneValide();
    bool operator==(const personne& autre) const {
        return (d_nomDeFamille == autre.nomDeFamille() && d_prenom == autre.prenom());
    }
    std::string formaterNomPrenom(const std::string& input);
private:
    std::string d_nomDeFamille;
    std::string d_prenom;
    std::string d_numeroDeTel;
    std::string d_adresseMail;
    std::string verifierValidite(const std::string& nom, const std::string& prenom, const std::string& numero, const std::string& adresseMail);
};

#endif // PERSONNE_H
