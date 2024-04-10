// Autor: Adam Czubak
// Utworzenie pliku nagłówkowego klasy Investment.
// Definicja klasy, jej atrybutów, metod i operatorów.

#ifndef INVESTMENT_H
#define INVESTMENT_H
#include <iostream>

class Investment
{
    // Klasa "Investment" reprezentująca lej i jego atrybuty.
    private:
        double funds;
        double interest_rate;
        unsigned int years;
        bool tax_state;
        unsigned int tax_rate;
        unsigned int capitalization_number_per_year;
        std::string investment_current;
    public:
        // Konstruktor klasy (dwa ostatnie parametry: kapitalizacja w ciągu roku i waluta mają przypisane parametry domyślne):
        Investment(double funds = 0,
                   double interest_rate = 0,
                   unsigned int years = 0,
                   bool tax_state = false,
                   unsigned int tax_rate = 0,
                   unsigned int capitalization_number_per_year = 1,
                   std::string investment_current = "PLN");
        // Zwraca ilość środków:
        double check_funds();
        // Ustawia ilość środków:
        void change_account_state(const double new_funds);
        // Dodaje (lub odejmuje) dodatkowe środki do stanu konta:
        void add_funds(const double new_funds);
        // Zwraca oprocentowanie lokaty:
        double get_interest_rate();
        // Ustawia oprocentowanie lokaty:
        void change_interest_rate(const double new_interest_rate);
        // Zwraca liczbę lat, na które została założona lokata:
        unsigned int get_years();
        // Ustawia liczbę lat, na które została założona lokata:
        void set_years(const unsigned int new_years);
        // Zwraca informacje czy uwzględniamy podatek w lokacie:
        bool get_tax_state();
        // Ustawia stan uwzględniający podatek w lokacie: true - uwzględniamy; false - nieuwzględniamy:
        void set_tax_state(const bool new_tax_state);
        // Zwraca procentową wartość podatku:
        unsigned int get_tax_rate();
        // Ustawia procentową wartość podatku:
        void set_tax_rate(const unsigned int new_tax_rate);
        // Zwraca liczbę kapitalizacji w ciągu roku:
        unsigned int get_capitalization_number_per_year();
        // Ustawia liczbę kapitalizacji w ciągu roku:
        void set_capitalization_number_per_year(const unsigned int new_capitalization_number);
        // Zwraca walutę, na której aktualnie operujemy:
        std::string get_investment_current();
        // Ustawia walutę, na której chcemy operować:
        void set_investment_current(std::string new_investment_current);
        // Szacuje zysk uwzględniając oprocentowanie, kapitalizację, liczbę lat, podatek:
        double estimate_profits(const double rate_of_interest, const unsigned int years_number, const bool taxes_state, unsigned int taxes_rate, const unsigned int capitalization);
        // Przekonwertowanie środków na koncie na żądaną walutę:
        double convert_current(std::string new_current,const double current_conversion_rate);
        // Poniższe operatory poza == i != operują na atrybutach liczbowych!
        // Zwiększenie środków o 100 złotych:
        Investment& operator++(int);
        // Zmniejszenie środków o 100 złotych:
        Investment& operator--(int);
        // Dodawanie obiektów z przypisaniem:
        Investment& operator+=(const Investment& second_investment);
        // Odejmowanie obiektów z przypisaniem:
        Investment& operator-=(const Investment& second_investment);
        // Mnożenie obiektów z przypisaniem
        Investment& operator*=(const Investment& second_investment);
        // Dzielenie obiektów z przypisaniem:
        Investment& operator/=(const Investment& second_investment);
        // Dodawanie obiektów:
        Investment operator+(const Investment& second_investment) const;
        // Odejmowanie obiektów:
        Investment operator-(const Investment& second_investment) const;
        // Mnożenie obiektów:
        Investment operator*(const Investment& second_investment) const;
        // Dzielenie obiektów:
        Investment operator/(const Investment& second_investment) const;
        // Sprawdzenie identyczności obiektów:
        bool operator==(const Investment& investment_to_check) const;
        // Sprawdzenie nieidentyczności obiektów:
        bool operator!=(const Investment& investment_to_check) const;
        // Sprawdzenie mniejszości pierwszego obiektu:
        bool operator<(const Investment& investment_to_check) const;
        // Sprawdzenie większości pierwszego obiektu:
        bool operator>(const Investment& investment_to_check) const;
        // Sprawdzenie mniejszości lub równości pierwszego obiektu:
        bool operator<=(const Investment& investment_to_check) const;
        // Sprawdzenie większości lub równości drugiego obiektu:
        bool operator>=(const Investment& investment_to_check) const;
        // Wypisanie właściwości lokaty:
        friend std::ostream& operator<<(std::ostream& os,Investment& investment);
};
std::ostream& operator<<(std::ostream& os,Investment& investment);
#endif