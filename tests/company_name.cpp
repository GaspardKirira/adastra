#include <iostream>
#include <regex>
#include <string>

bool validateCompanyName(const std::string &companyName)
{
    std::regex pattern("^[A-Za-z0-9À-ÿ'\\s-]+(?:[,.&]?[A-Za-z0-9À-ÿ'\\s-]+)*$");
    return std::regex_match(companyName, pattern);
}

int main()
{
    std::string companyName1 = "Tech Solutions Inc.";
    std::string companyName2 = "John's Auto Repair";
    std::string companyName3 = "Super-Global Enterprises LLC";
    std::string companyName4 = "ABC123, LLC";
    std::string companyName5 = "Invalid@Company";

    if (validateCompanyName(companyName1))
    {
        std::cout << "Nom d'entreprise valide: " << companyName1 << std::endl;
    }
    else
    {
        std::cout << "Nom d'entreprise invalide: " << companyName1 << std::endl;
    }

    if (validateCompanyName(companyName2))
    {
        std::cout << "Nom d'entreprise valide: " << companyName2 << std::endl;
    }
    else
    {
        std::cout << "Nom d'entreprise invalide: " << companyName2 << std::endl;
    }

    if (validateCompanyName(companyName3))
    {
        std::cout << "Nom d'entreprise valide: " << companyName3 << std::endl;
    }
    else
    {
        std::cout << "Nom d'entreprise invalide: " << companyName3 << std::endl;
    }

    if (validateCompanyName(companyName4))
    {
        std::cout << "Nom d'entreprise valide: " << companyName4 << std::endl;
    }
    else
    {
        std::cout << "Nom d'entreprise invalide: " << companyName4 << std::endl;
    }

    if (validateCompanyName(companyName5))
    {
        std::cout << "Nom d'entreprise valide: " << companyName5 << std::endl;
    }
    else
    {
        std::cout << "Nom d'entreprise invalide: " << companyName5 << std::endl;
    }

    return 0;
}
