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
        static const std::regex firstNamePattern;
        static const std::regex lastNamePattern;
        static const std::regex usernamePattern;
        static const std::regex fullNamePattern;
        static const std::regex emailPattern;
        static const std::regex phonePattern;
        static const std::regex companyNamePattern;
        static const std::regex descriptionPattern;

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

    const std::regex Validator::firstNamePattern("^[A-Za-zÀ-ÿ]+(?:[-'\\s][A-Za-zÀ-ÿ]+)*$");
    const std::regex Validator::lastNamePattern("^[A-Za-zÀ-ÿ]+(?:[-'\\s][A-Za-zÀ-ÿ]+)*$");
    const std::regex Validator::usernamePattern("^[A-Za-z0-9](?:[A-Za-z0-9_-]{1,18}[A-Za-z0-9])?$");
    const std::regex Validator::fullNamePattern("^[A-Za-zÀ-ÿ]+(?:[-'\\s][A-Za-zÀ-ÿ]+)+$");
    const std::regex Validator::emailPattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    const std::regex Validator::phonePattern("^\\+([1-9][0-9]{0,3})\\s?[0-9]{4,14}$");
    const std::regex Validator::companyNamePattern("^[A-Za-z0-9À-ÿ'\\s-]+(?:[,.&]?[A-Za-z0-9À-ÿ'\\s-]+)*$");
    const std::regex Validator::descriptionPattern("^[A-Za-z0-9À-ÿ'\\s,.-]*$");
} // namespace Adastra

#endif