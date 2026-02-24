#include "../include/personne.h"
#include <algorithm>

personne::personne(const std::string& nom, const std::string& prenom, const std::string& numero, const std::string& adresseMail)
{
    std::string erreur = verifierValidite(nom, prenom, numero, adresseMail);
    if (erreur.empty()) {  // Si aucune erreur, on assigne les valeurs
        this->d_nomDeFamille = nom;
        this->d_prenom = prenom;
        this->d_numeroDeTel = numero;
        this->d_adresseMail = adresseMail;
    }
}

std::string personne::verifierValidite(const std::string& nom, const std::string& prenom, const std::string& numero, const std::string& adresseMail)
{
    if(nom.empty())
        return "Le nom ne peut pas être vide.";
    if (prenom.empty())
        return "Le prénom ne peut pas être vide.";
    if (numero.size() != 10)
        return "Le numéro doit contenir 10 chiffres.";
    if (!std::all_of(numero.begin(), numero.end(), ::isdigit)) {
        return "Le numéro de téléphone doit contenir uniquement des chiffres.";
    }
    if (adresseMail.find('@') == std::string::npos)
        return "Adresse email invalide.";
    return "";
}

std::string personne::nomDeFamille() const
{
    return d_nomDeFamille;
}

std::string personne::prenom() const
{
    return d_prenom;
}

std::string personne::numeroTel() const
{
    return d_numeroDeTel;
}

std::string personne::adresseMail() const
{
    return d_adresseMail;
}

bool personne::setNum(const std::string& numero)
{
    if (std::all_of(numero.begin(), numero.end(), ::isdigit))
    {
        d_numeroDeTel=numero;
        return true;
    }
    return false;
}

bool personne::setAdresseMail(const std::string& adresseMail)
{
    if(adresseMail.find('@') != std::string::npos)
    {
        d_adresseMail=adresseMail;
        return true;
    }
    return false;
}

bool personne::personneValide()
{
    if(this->verifierValidite(this->nomDeFamille(), this->prenom(), this->numeroTel(), this->adresseMail())=="")
    {
        return true;
    }
    else
        return false;
}
std::string personne::formaterNomPrenom(const std::string& input) {
    if (input.empty()) return input; // Vérifier si le champ est vide

    std::string output = input;

    // Tout convertir en minuscule
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);

    // Mettre la première lettre en majuscule
    output[0] = std::toupper(output[0]);

    return output;
}

