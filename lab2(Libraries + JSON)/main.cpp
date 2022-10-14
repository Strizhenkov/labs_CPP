#include <iostream>
#include <conio.h>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "Request.h"
#include "Entities.h"
#include "CurrenciesMath.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");

    CurrenciesMath currenciesMath;

    while (!kbhit()) {
        string jsonString;
        if(!Request::getUrl("https://www.cbr-xml-daily.ru/daily_json.js", jsonString)) {
            std::cout << "ERROR curl unable to get url" << std::endl;
            return 1;
        }

        nlohmann::json json_data = nlohmann::json::parse(jsonString);
        DailyQuotes quotes = json_data.get<DailyQuotes>();

        OutputQuotes(quotes);
        currenciesMath.add(quotes);

        Sleep(1000);
    }

    cout << "\n\n\n";
    currenciesMath.Output();

    system("pause");
    return 0;
}