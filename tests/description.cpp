#include <iostream>
#include <regex>
#include <string>

// Fonction de validation pour les descriptions (entreprise ou produit)
bool validateDescription(const std::string &description)
{
    // La regex permet les lettres, chiffres, espaces, apostrophes, tirets, virgules, points
    std::regex pattern("^[A-Za-z0-9À-ÿ'\\s,.-]*$");
    return std::regex_match(description, pattern);
}

// Fonction pour récupérer une description avec une valeur par défaut si vide
std::string getDescriptionOrDefault(const std::string &description, const std::string &defaultDescription)
{
    if (description.empty())
    {
        return defaultDescription; // Retourne la description par défaut si la chaîne est vide
    }
    return description;
}

int main()
{
    // Description d'entreprise
    std::string companyDescription = ""; // Vide, sera remplacée par la valeur par défaut
    std::string defaultCompanyDescription = "Description de l'entreprise non fournie";

    // Description de produit
    std::string productDescription = "Produit innovant pour améliorer votre expérience"; // Exemple valide
    std::string defaultProductDescription = "Description du produit non fournie";

    // Validation et remplacement avec des valeurs par défaut si nécessaire
    if (validateDescription(companyDescription))
    {
        companyDescription = getDescriptionOrDefault(companyDescription, defaultCompanyDescription);
        std::cout << "Description de l'entreprise: " << companyDescription << std::endl;
    }
    else
    {
        std::cout << "Description d'entreprise invalide" << std::endl;
    }

    if (validateDescription(productDescription))
    {
        productDescription = getDescriptionOrDefault(productDescription, defaultProductDescription);
        std::cout << "Description du produit: " << productDescription << std::endl;
    }
    else
    {
        std::cout << "Description de produit invalide" << std::endl;
    }

    return 0;
}
