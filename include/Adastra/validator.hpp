#ifndef ADASTRA_VALIDATOR_HPP
#define ADASTRA_VALIDATOR_HPP

#include <iostream>
#include <string>
#include <regex>

namespace Adastra
{
    class Validator
    {
    private:
        // Supprimer les regex statiques
        static bool validateWithPattern(const std::string &input, const std::regex &pattern)
        {
            return std::regex_match(input, pattern);
        }

    public:
        static bool validateFirstName(const std::string &firstName)
        {
            // Déclarer les regex localement pour éviter les fuites
            const std::regex firstNamePattern("^[A-Za-zÀ-ÿ]+(?:[-'\\s][A-Za-zÀ-ÿ]+)*$");
            return validateWithPattern(firstName, firstNamePattern);
        }

        static bool validateLastName(const std::string &lastName)
        {
            const std::regex lastNamePattern("^[A-Za-zÀ-ÿ]+(?:[-'\\s][A-Za-zÀ-ÿ]+)*$");
            return validateWithPattern(lastName, lastNamePattern);
        }

        static bool validateUsername(const std::string &username)
        {
            const std::regex usernamePattern("^[A-Za-z0-9](?:[A-Za-z0-9_-]{1,18}[A-Za-z0-9])?$");
            return validateWithPattern(username, usernamePattern);
        }

        static bool validateFullName(const std::string &fullName)
        {
            if (fullName.empty())
            {
                return false;
            }
            const std::regex fullNamePattern("^[a-zA-Z]+(?:[a-zA-Z\\'-]*[a-zA-Z]+)*$");
            return validateWithPattern(fullName, fullNamePattern);
        }

        static bool validateEmail(const std::string &email)
        {
            const std::regex emailPattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
            return validateWithPattern(email, emailPattern);
        }

        static bool validatePhoneNumber(const std::string &phoneNumber)
        {
            const std::regex phonePattern("^\\+([1-9][0-9]{0,3})\\s?[0-9]{4,14}$");
            return validateWithPattern(phoneNumber, phonePattern);
        }

        static bool validateCompanyName(const std::string &companyName)
        {
            const std::regex companyNamePattern("^[A-Za-z0-9À-ÿ'\\s-]+(?:[,.&]?[A-Za-z0-9À-ÿ'\\s-]+)*$");
            return validateWithPattern(companyName, companyNamePattern);
        }

        static bool validateDescription(const std::string &description)
        {
            const std::regex descriptionPattern("^[A-Za-z0-9À-ÿ'\\s,.-]*$");
            return validateWithPattern(description, descriptionPattern);
        }

        static std::string getDescriptionOrDefault(const std::string &description, const std::string &defaultDescription)
        {
            return description.empty() ? defaultDescription : description;
        }
    };
} // namespace Adastra

#endif
