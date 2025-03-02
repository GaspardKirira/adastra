#include <iostream>
#include <string>
#include <regex>

class Validator
{
private:
    // Expressions régulières statiques pour éviter de les recompiler à chaque appel
    static const std::regex firstNamePattern;
    static const std::regex lastNamePattern;
    static const std::regex usernamePattern;
    static const std::regex fullNamePattern;
    static const std::regex emailPattern;
    static const std::regex phonePattern;
    static const std::regex companyNamePattern;
    static const std::regex descriptionPattern;

    // Méthode générique pour valider avec une expression régulière
    static bool validateWithPattern(const std::string &input, const std::regex &pattern)
    {
        return std::regex_match(input, pattern);
    }

public:
    static bool validateFirstName(const std::string &firstName)
    {
        return validateWithPattern(firstName, firstNamePattern);
    }

    static bool validateLastName(const std::string &lastName)
    {
        return validateWithPattern(lastName, lastNamePattern);
    }

    static bool validateUsername(const std::string &username)
    {
        return validateWithPattern(username, usernamePattern);
    }

    static bool validateFullName(const std::string &fullName)
    {
        return validateWithPattern(fullName, fullNamePattern);
    }

    static bool validateEmail(const std::string &email)
    {
        return validateWithPattern(email, emailPattern);
    }

    static bool validatePhoneNumber(const std::string &phoneNumber)
    {
        return validateWithPattern(phoneNumber, phonePattern);
    }

    static bool validateCompanyName(const std::string &companyName)
    {
        return validateWithPattern(companyName, companyNamePattern);
    }

    static bool validateDescription(const std::string &description)
    {
        return validateWithPattern(description, descriptionPattern);
    }

    static std::string getDescriptionOrDefault(const std::string &description, const std::string &defaultDescription)
    {
        return description.empty() ? defaultDescription : description;
    }
};

// Définition des expressions régulières statiques
const std::regex Validator::firstNamePattern("^[A-Za-zÀ-ÿ]+(?:[-'\\s][A-Za-zÀ-ÿ]+)*$");
const std::regex Validator::lastNamePattern("^[A-Za-zÀ-ÿ]+(?:[-'\\s][A-Za-zÀ-ÿ]+)*$");
const std::regex Validator::usernamePattern("^[A-Za-z0-9](?:[A-Za-z0-9_-]{1,18}[A-Za-z0-9])?$");
const std::regex Validator::fullNamePattern("^[A-Za-zÀ-ÿ]+(?:[-'\\s][A-Za-zÀ-ÿ]+)+$");
const std::regex Validator::emailPattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
const std::regex Validator::phonePattern("^\\+([1-9][0-9]{0,3})\\s?[0-9]{4,14}$");
const std::regex Validator::companyNamePattern("^[A-Za-z0-9À-ÿ'\\s-]+(?:[,.&]?[A-Za-z0-9À-ÿ'\\s-]+)*$");
const std::regex Validator::descriptionPattern("^[A-Za-z0-9À-ÿ'\\s,.-]*$");

int main()
{
    // Exemple d'utilisation
    std::string email = "example@domain.com";
    if (Validator::validateEmail(email))
    {
        std::cout << "Email valide !" << std::endl;
    }
    else
    {
        std::cout << "Email invalide !" << std::endl;
    }

    std::string phone = "+123 456789012";
    if (Validator::validatePhoneNumber(phone))
    {
        std::cout << "Numéro de téléphone valide !" << std::endl;
    }
    else
    {
        std::cout << "Numéro de téléphone invalide !" << std::endl;
    }

    return 0;
}
