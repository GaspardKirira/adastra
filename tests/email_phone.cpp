#include <iostream>
#include <regex>
#include <string>

bool validateEmail(const std::string &email)
{
    std::regex pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return std::regex_match(email, pattern);
}

bool validatePhoneNumber(const std::string &phoneNumber)
{
    std::regex pattern("^\\+([1-9][0-9]{0,3})\\s?[0-9]{4,14}$");
    return std::regex_match(phoneNumber, pattern);
}

int main()
{
    // Test email validation
    std::string email = "example@gmail.com";
    if (validateEmail(email))
    {
        std::cout << "Email valide: " << email << std::endl;
    }
    else
    {
        std::cout << "Email invalide: " << email << std::endl;
    }

    // Test numéro de téléphone validation
    std::string phoneNumber1 = "+256783345232";
    std::string phoneNumber2 = "+243991324430";
    if (validatePhoneNumber(phoneNumber1))
    {
        std::cout << "Numéro de téléphone valide: " << phoneNumber1 << std::endl;
    }
    else
    {
        std::cout << "Numéro de téléphone invalide: " << phoneNumber1 << std::endl;
    }

    if (validatePhoneNumber(phoneNumber2))
    {
        std::cout << "Numéro de téléphone valide: " << phoneNumber2 << std::endl;
    }
    else
    {
        std::cout << "Numéro de téléphone invalide: " << phoneNumber2 << std::endl;
    }

    return 0;
}
