#include "Questionnaire.h"
#include "QuestionTexte.h"
#include "QuestionNumerique.h"
#include "QuestionQCM.h"

#include <iostream>
#include <string>
#include <stdexcept>


namespace {
    std::string lireLigne(std::istream& flux, const std::string& messageErreur)
    {
        std::string ligne;
        if (!std::getline(flux, ligne)) {
            throw std::runtime_error(messageErreur);
        }
        return ligne;
    }

    int lireEntier(std::istream& flux, const std::string& messageErreur)
    {
        std::string ligne = lireLigne(flux, messageErreur);
        return std::stoi(ligne);
    }
}


Questionnaire::Questionnaire(const std::string& titre)
    : d_titre(titre)
{
}



std::string Questionnaire::titre() const {
    return d_titre;
}

void Questionnaire::setTitre(const std::string& titre) {
    d_titre = titre;
}

std::size_t Questionnaire::nombreQuestions() const {
    return d_questions.size();
}

bool Questionnaire::estVide() const {
    return d_questions.empty();
}



void Questionnaire::ajouterQuestion(std::unique_ptr<Question> question) {
    if (!question) {
        throw std::invalid_argument("Impossible d'ajouter une question nulle");
    }
    d_questions.push_back(std::move(question));
}

void Questionnaire::validerIndex(std::size_t index) const {
    if (index >= d_questions.size()) {
        throw std::out_of_range("Index de question invalide: " +
            std::to_string(index));
    }
}

Question& Questionnaire::question(std::size_t index) {
    validerIndex(index);
    return *d_questions[index];
}

const Question& Questionnaire::question(std::size_t index) const {
    validerIndex(index);
    return *d_questions[index];
}


void Questionnaire::afficher() const {
    std::cout << "=== " << d_titre << " ===" << std::endl;
    std::cout << std::endl;

    for (std::size_t i = 0; i < d_questions.size(); ++i) {
        std::cout << "Question " << (i + 1) << ": ";
        d_questions[i]->AfficherQuestion();
        std::cout << std::endl;
    }
}



void Questionnaire::ecrire(std::ostream& flux) const {
    flux << d_titre << std::endl;
    flux << d_questions.size() << std::endl;

    for (const auto& question : d_questions) {
        question->ecrire(flux);
    }
}



namespace {
    std::unique_ptr<Question> creerQuestionTexte(std::istream& flux)
    {
        std::string intitule = lireLigne(flux, "Intitulé de question texte manquant");
        std::string texte = lireLigne(flux, "Texte de question texte manquant");
        std::string bonneReponse = lireLigne(flux, "Bonne réponse texte manquante");

        return std::make_unique<QuestionTexte>(intitule, texte, bonneReponse);
    }

    std::unique_ptr<Question> creerQuestionNumerique(std::istream& flux)
    {
        std::string intitule = lireLigne(flux, "Intitulé de question numérique manquant");
        std::string texte = lireLigne(flux, "Texte de question numérique manquant");
        int bonneReponse = lireEntier(flux, "Bonne réponse numérique manquante");
        int minimum = lireEntier(flux, "Minimum de question numérique manquant");
        int maximum = lireEntier(flux, "Maximum de question numérique manquant");

        return std::make_unique<QuestionNumerique>(intitule, texte,
            bonneReponse, minimum, maximum);
    }

    std::unique_ptr<Question> creerQuestionQCM(std::istream& flux)
    {
        constexpr int NOMBRE_PROPOSITIONS = 4;

        std::string intitule = lireLigne(flux, "Intitulé de question QCM manquant");
        std::string texte = lireLigne(flux, "Texte de question QCM manquant");
        int bonneReponse = lireEntier(flux, "Numéro de bonne réponse QCM manquant");

        int nombrePropositions = lireEntier(flux, "Nombre de propositions QCM manquant");
        if (nombrePropositions != NOMBRE_PROPOSITIONS) {
            throw std::runtime_error("Une question QCM doit avoir exactement " +
                std::to_string(NOMBRE_PROPOSITIONS) +
                " propositions");
        }

        std::vector<std::string> propositions;
        propositions.reserve(NOMBRE_PROPOSITIONS);
        for (int i = 0; i < NOMBRE_PROPOSITIONS; ++i) {
            propositions.push_back(
                lireLigne(flux, "Proposition QCM " + std::to_string(i + 1) + " manquante")
            );
        }

        return std::make_unique<QuestionQCM>(intitule, texte, propositions, bonneReponse);
    }

    std::unique_ptr<Question> creerQuestion(const std::string& type, std::istream& flux)
    {
        if (type == "T") {
            return creerQuestionTexte(flux);
        }
        else if (type == "N") {
            return creerQuestionNumerique(flux);
        }
        else if (type == "QCM") {
            return creerQuestionQCM(flux);
        }
        else {
            throw std::runtime_error("Type de question inconnu: " + type);
        }
    }
}


void Questionnaire::lire(std::istream& flux)
{
    d_questions.clear();

    d_titre = lireLigne(flux, "Titre du questionnaire manquant");

    int nombreQuestions = lireEntier(flux, "Nombre de questions manquant");
    if (nombreQuestions < 0) {
        throw std::runtime_error("Le nombre de questions ne peut pas être négatif");
    }

    for (int i = 0; i < nombreQuestions; ++i) {
        std::string type = lireLigne(flux, "Type de question manquant");
        std::unique_ptr<Question> question = creerQuestion(type, flux);
        ajouterQuestion(std::move(question));
    }
}