#ifndef UNTITLED2_ENTITIES_H
#define UNTITLED2_ENTITIES_H

#include <string>
#include <map>

using namespace std;

struct Currency {
    string CharCode;
    string Name;
    double Value;
};

struct DailyQuotes {
    map<string, Currency> Currencies;
};


//  map json to our structures

void from_json(const nlohmann::json& j, Currency& p) {
    j.at("CharCode").get_to(p.CharCode);
    j.at("Name").get_to(p.Name);
    j.at("Value").get_to(p.Value);
}

void from_json(const nlohmann::json& j, DailyQuotes& p) {
    j.at("Valute").get_to(p.Currencies);
}

//  output functions

void OutputCurrency(const Currency &c)
{
    std::cout << c.Name << " : " << c.Value << '\n';
}

void OutputQuotes(const DailyQuotes &quotes)
{
    for(auto it = quotes.Currencies.begin(); it != quotes.Currencies.end(); it++)
        OutputCurrency(it->second);
}

#endif //UNTITLED2_ENTITIES_H
