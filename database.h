// Autor: Adam Czubak
// Utworzenie pliku nagłówkowego klasy Database.
// Definicja klasy, jej atrybutów, metod i operatorów.

#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <algorithm>
#include <vector>
#include "/home/adamczubak/Zad2/investment.h"

class Database
{
    private:
    // Klasa "Investment" reprezentująca lej i jego atrybuty.
        std::vector<Investment> database;
    public:
    // Konstruktor klasy: domyślnie lista jest pusta:
        Database(std::vector<Investment> database = {});
    // Pobiera bazę danych:
        std::vector<Investment> get_list();
    // Ustawia nową bazę danych:
        void set_list(std::vector<Investment> new_database);
    // Pobiera liczbę lokat w bazie danych:
        unsigned int get_number_of_investments();
    // Czyści bazę danych:
        void clear_list();
    // Dodaje lokatę do bazy danych:
        void add_investment(const Investment investment);
    // Usuwa lokatę z bazy danych:
        void remove_investment(const Investment investment);
    // Wyszukuje lokatę w bazie i zwraca jej pozycję:
        int search_investment(const Investment investment_to_search);
    // Sortuje bazę danych według danego atrybutu rosnąco lub malejąco:
        void sort_list_by_number_attribute(const std::string attribute, std::string direction="+");
    // Zwraca liczbę lokat w bazie na podstawie środków spełniających daną relację między środkami a wartością odniesienia:
        unsigned int number_of_investment_by_funds(const double funds, const std::string relationship);
    // Zwraca liczbę lokat w bazie na podstawie oprocentowania spełniających daną relację między oprocentowaniem a wartością odniesienia:
        unsigned int number_of_investment_by_interest_rate(const double interest_rate, const std::string relationship);
    // Zwraca liczbę lokat w bazie na podstawie lat spełniających daną relację między latami a wartością odniesienia:
        unsigned int number_of_investment_by_years(const unsigned int years, const std::string relationship);
    // Zwraca liczbę lokat w bazie na podstawie stanu podatku:
        unsigned int number_of_investment_by_tax_state(const bool tax_state);
    // Zwraca liczbę lokat w bazie na podstawie procentowej wartości podatku spełniających daną relację między środkami a wartością odniesienia:
        unsigned int number_of_investment_by_tax_rate(const unsigned int tax_rate, const std::string relationship);
    // Zwraca liczbę lokat w bazie na podstawie rocznej kapitalizacji spełniających daną relację między liczbą rocznych kapitalizacji a wartością odniesienia:
        unsigned int number_of_investment_by_capitalization(const unsigned int capitalization, const std::string relationship);
    // Zwraca liczbę lokat w bazie na podstawie waluty lokaty:
        unsigned int number_of_investment_by_certain_current(const std::string current);
    // Zapisuje bazę danych do pliku i zwraca ilość linijek w pliku do którego zapisujemy bazę:
        unsigned int save_database(const std::string path_file);
    // Ładuję bazę z pliku do obiektu klasy Database:
        void load_database(const std::string path_file);
    // Sprawdzanie równości dwóch baz danych:
        bool operator==(const Database& database_parameter) const;
    // Sprawdzanie różności dwóch baz danych:
        bool operator!=(const Database& database_parameter) const;
    // Dodawanie obiektu z jednej bazy do drugiej bazy:
        Database& operator+=(Database& database_parameter);
};
#endif