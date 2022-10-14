#ifndef UNTITLED2_CURRENCIESMATH_H
#define UNTITLED2_CURRENCIESMATH_H

#include "Entities.h"
#include <vector>
#include <algorithm>

using namespace std;

class CurrenciesMath {
private:
    struct CurrencyMathValues {
        string CharCode;
        int Count;
        double Sum;
        vector<double> SortedValues;

        double average() const {
            return Sum / Count;
        }
        double median() {
            sort(SortedValues.begin(), SortedValues.end());
            auto middle = SortedValues.size() / 2;
            return (SortedValues.size() % 2 != 0)
                ? SortedValues[middle]
                : (SortedValues[middle] + SortedValues[middle + 1]) / 2;
        }
    };

public:
    void add(const DailyQuotes &quotes) {
        for(const auto & Currencie : quotes.Currencies)
            addCurrency(Currencie.second);
    }

    void Output() {
        for(auto & _currencie : _currencies)
            OutputCurrency(_currencie.second);
    }

private:
    map<string, CurrencyMathValues> _currencies;

    void addCurrency(const Currency &currency) {
        auto it = _currencies.find(currency.CharCode);
        if(it == _currencies.end()) {
            _currencies[currency.CharCode] = {currency.CharCode, 0, 0};
            it = _currencies.find(currency.CharCode);
        }

        it->second.Count++;
        it->second.Sum += currency.Value;
        it->second.SortedValues.push_back(currency.Value);
    }

    static void OutputCurrency(CurrencyMathValues &currency) {
        cout << currency.CharCode << " " << "Average : " << currency.average() << " Mid: " << currency.median() << '\n';
    }
};

#endif //UNTITLED2_CURRENCIESMATH_H
