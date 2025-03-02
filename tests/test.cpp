#include <iostream>
#include <string>
#include <regex>

bool validateFirstName(const std::string &firstName)
{
    // Permet les lettres, accents, apostrophes et tirets
    std::regex pattern("^[A-Za-zÀ-ÿ]+(?:[-'\\s][A-Za-zÀ-ÿ]+)*$");
    return std::regex_match(firstName, pattern);
}

bool validateLastName(const std::string &lastName)
{
    // Permet les lettres, accents, apostrophes et tirets
    std::regex pattern("^[A-Za-zÀ-ÿ]+(?:[-'\\s][A-Za-zÀ-ÿ]+)*$");
    return std::regex_match(lastName, pattern);
}

bool validateUsername(const std::string &username)
{
    // Nom d'utilisateur entre 3 et 20 caractères, avec lettres, chiffres, tirets et underscores, sans débuter ou finir par des caractères spéciaux
    std::regex pattern("^[A-Za-z0-9](?:[A-Za-z0-9_-]{1,18}[A-Za-z0-9])?$");
    return std::regex_match(username, pattern);
}

bool validateFullName(const std::string &fullName)
{
    // Permet un prénom et un nom, gère également les prénoms ou noms multiples
    std::regex pattern("^[A-Za-zÀ-ÿ]+(?:[-'\\s][A-Za-zÀ-ÿ]+)+$");
    return std::regex_match(fullName, pattern);
}

bool validateEmail(const std::string &email)
{
    // Regex pour valider un email selon les normes classiques, y compris Gmail
    std::regex pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return std::regex_match(email, pattern);
}

bool validatePhoneNumber(const std::string &phoneNumber)
{
    // Regex pour valider un numéro de téléphone international
    std::regex pattern("^\\+([1-9][0-9]{0,3})\\s?[0-9]{4,14}$");
    return std::regex_match(phoneNumber, pattern);
}

bool validateCompanyName(const std::string &companyName)
{
    // Regex pour valider un nom d'entreprise
    // Permet les lettres, chiffres, apostrophes, tirets et espaces.
    // Autorise les suffixes comme 'Inc.', 'LLC', 'S.A.', etc.
    std::regex pattern("^[A-Za-z0-9À-ÿ'\\s-]+(?:[,.&]?[A-Za-z0-9À-ÿ'\\s-]+)*$");
    return std::regex_match(companyName, pattern);
}

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
    std::string firstName, lastName, username, fullName;

    // Validation du prénom
    while (true)
    {
        std::cout << "Entrez votre prénom: ";
        std::getline(std::cin, firstName);
        if (validateFirstName(firstName))
        {
            break;
        }
        else
        {
            std::cerr << "Prénom invalide ! Il doit contenir uniquement des lettres (accents autorisés) et des espaces." << std::endl;
        }
    }

    // Validation du nom de famille
    while (true)
    {
        std::cout << "Entrez votre nom de famille: ";
        std::getline(std::cin, lastName);
        if (validateLastName(lastName))
        {
            break;
        }
        else
        {
            std::cerr << "Nom de famille invalide ! Il doit contenir uniquement des lettres (accents autorisés) et des espaces." << std::endl;
        }
    }

    // Validation du nom d'utilisateur
    while (true)
    {
        std::cout << "Entrez votre nom d'utilisateur (3-20 caractères, lettres, chiffres, tirets et underscores autorisés) : ";
        std::getline(std::cin, username);
        if (validateUsername(username))
        {
            break;
        }
        else
        {
            std::cerr << "Nom d'utilisateur invalide ! Il doit être composé de lettres, chiffres, tirets ou underscores, et ne doit pas commencer ni finir par un tiret ou un underscore." << std::endl;
        }
    }

    // Validation du nom complet
    while (true)
    {
        std::cout << "Entrez votre nom complet (prénom et nom de famille séparés par un espace) : ";
        std::getline(std::cin, fullName);
        if (validateFullName(fullName))
        {
            break;
        }
        else
        {
            std::cerr << "Nom complet invalide ! Il doit contenir un prénom et un nom de famille, séparés par un espace, et respecter les règles de prénom et nom de famille." << std::endl;
        }
    }

    // Affichage des résultats
    std::cout << "Validation réussie !\n"
              << "Prénom : " << firstName << "\n"
              << "Nom de famille : " << lastName << "\n"
              << "Nom d'utilisateur : " << username << "\n"
              << "Nom complet : " << fullName << std::endl;

    return 0;
}
