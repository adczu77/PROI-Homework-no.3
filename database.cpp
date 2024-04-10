// Autor: Adam Czubak
// Implementacja metod i operatorów klasy.

#include "/home/adamczubak/Zad2/investment.h"
#include "database.h"
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <sstream>
#include <ctime>

Database::Database(std::vector<Investment> database) : database(database){}

std::vector<Investment> Database::get_list()
{
    return database;
}

void Database::set_list(std::vector<Investment> new_database)
{
    database = new_database;
}

unsigned int Database::get_number_of_investments()
{
    return database.size();
}

void Database::clear_list()
{
    database.clear();
}

void Database::add_investment(const Investment new_investment)
{
    database.push_back(new_investment);
}

void Database::remove_investment(const Investment investment_to_remove)
{
    auto found_investment_to_remove = std::find(database.begin(), database.end(), investment_to_remove);
    if (found_investment_to_remove != database.end())
        database.erase(found_investment_to_remove);
    else
       throw std::logic_error("There is no such investment here!");
}

int Database::search_investment(const Investment investment_to_search)
{
    auto found_investment = std::find(database.begin(), database.end(), investment_to_search);
    if (found_investment != database.end())
    {
        int position = found_investment - database.begin() + 1;
        return position;
    }
    else
        throw std::invalid_argument("There is no such investment in the database!");
}

void Database::sort_list_by_number_attribute(const std::string attribute, std::string direction)
{
    std::vector<std::string> attributes = {"funds", "interest_rate", "years", "tax_rate", "capitalization_number_per_year"};
    auto found_attribute = std::find(attributes.begin(), attributes.end(), attribute);
    int index = found_attribute - attributes.begin();
    enum Attribute{funds = 0, interest_rate = 1, years = 2, tax_rate = 3, capitalization_number_per_year = 4};
    switch(index)
    {
        case funds:
            std::sort(database.begin(), database.end(), [ ](Investment& first_investment, Investment& second_investment)
            {
                return first_investment.check_funds() < second_investment.check_funds();
            });
            break;
        case interest_rate:
            std::sort(database.begin(), database.end(), [ ](Investment& first_investment, Investment& second_investment)
            {
                return first_investment.get_interest_rate() < second_investment.get_interest_rate();
            });
            break;
        case years:
            std::sort(database.begin(), database.end(), [ ](Investment& first_investment, Investment& second_investment)
            {
                return first_investment.get_years() < second_investment.get_years();
            });
            break;
        case tax_rate:
            std::sort(database.begin(), database.end(), [ ](Investment& first_investment, Investment& second_investment)
            {
                return first_investment.get_tax_rate() < second_investment.get_tax_rate();
            });
            break;
        case capitalization_number_per_year:
            std::sort(database.begin(), database.end(), [ ](Investment& first_investment, Investment& second_investment)
            {
                return first_investment.get_capitalization_number_per_year() < second_investment.get_capitalization_number_per_year();
            });
            break;
        default:
            throw std::invalid_argument("Investment does not have that property!");
            break;
    }
    if (direction == "-")
        std::reverse(database.begin(), database.end());
    else if(direction == "+")
        direction = "+";
    else
        throw std::invalid_argument("Wrong direction!");
}

unsigned int Database::number_of_investment_by_funds(const double funds, const std::string relationship)
{
    unsigned int number;
    if (relationship == ">")
    {
        number = std::count_if(database.begin(), database.end(), [funds](Investment& investment){return investment.check_funds() > funds;});
        return number;
    }    
    else if (relationship == "<")
    {
        number = std::count_if(database.begin(), database.end(), [funds](Investment& investment){return investment.check_funds() < funds;});
        return number;
    }    
    else if (relationship == "=")
    {
        number = std::count_if(database.begin(), database.end(), [funds](Investment& investment){return investment.check_funds() == funds;});
        return number;
    }    
    else
        throw std::invalid_argument("Wrong relationship!");
}

unsigned int Database::number_of_investment_by_interest_rate(const double interest_rate, const std::string relationship)
{
    unsigned int number;
    if (relationship == ">")
    {
        number = std::count_if(database.begin(), database.end(), [interest_rate](Investment& investment){return investment.get_interest_rate() > interest_rate;});
        return number;
    }    
    else if (relationship == "<")
    {
        number = std::count_if(database.begin(), database.end(), [interest_rate](Investment& investment){return investment.get_interest_rate() < interest_rate;});
        return number;
    }
    else if (relationship == "=")
    {
        number = std::count_if(database.begin(), database.end(), [interest_rate](Investment& investment){return investment.get_interest_rate() == interest_rate;});
        return number;
    }
    else
        throw std::invalid_argument("Wrong relationship!");
}

unsigned int Database::number_of_investment_by_years(const unsigned int years, const std::string relationship)
{
    unsigned int number;
    if (relationship == ">")
    {
        number = std::count_if(database.begin(), database.end(), [years](Investment& investment){return investment.get_years() > years;});
        return number;
    }
    else if (relationship == "<")
    {
        number = std::count_if(database.begin(), database.end(), [years](Investment& investment){return investment.get_years() < years;});
        return number;
    }
    else if (relationship == "=")
    {
        number = std::count_if(database.begin(), database.end(), [years](Investment& investment){return investment.get_years() == years;});
        return number;
    }
    else
        throw std::invalid_argument("Wrong relationship!");
}

unsigned int Database::number_of_investment_by_tax_state(const bool tax_state)
{
    unsigned int number;
    if (tax_state == true)
    {
        number = std::count_if(database.begin(), database.end(), [tax_state](Investment& investment){return investment.get_tax_state() == tax_state;});
        return number;
    }
    else
    {
        number = std::count_if(database.begin(), database.end(), [tax_state](Investment& investment){return investment.get_tax_state() == tax_state;});
        return number;
    }
}

unsigned int Database::number_of_investment_by_tax_rate(const unsigned int tax_rate, const std::string relationship)
{
    unsigned int number;
    if (relationship == ">")
    {
        number = std::count_if(database.begin(), database.end(), [tax_rate](Investment& investment){return investment.get_tax_rate() > tax_rate;});
        return number;
    }
    else if (relationship == "<")
    {
        number = std::count_if(database.begin(), database.end(), [tax_rate](Investment& investment){return investment.get_tax_rate() < tax_rate;});
        return number;
    }
    else if (relationship == "=")
    {
        number = std::count_if(database.begin(), database.end(), [tax_rate](Investment& investment){return investment.get_tax_rate() == tax_rate;});
        return number;
    }
    else
        throw std::invalid_argument("Wrong relationship!");
}

unsigned int Database::number_of_investment_by_capitalization(const unsigned int capitalization, const std::string relationship)
{
    unsigned int number;
    if (relationship == ">")
    {
        number = std::count_if(database.begin(), database.end(), [capitalization](Investment& investment){return investment.get_capitalization_number_per_year() > capitalization;});
        return number;
    }
    else if (relationship == "<")
    {
        number = std::count_if(database.begin(), database.end(), [capitalization](Investment& investment){return investment.get_capitalization_number_per_year() < capitalization;});
        return number;
    }
    else if (relationship == "=")
    {
        number = std::count_if(database.begin(), database.end(), [capitalization](Investment& investment){return investment.get_capitalization_number_per_year() == capitalization;});
        return number;
    }
    else
        throw std::invalid_argument("Wrong relationship!");
}

unsigned int Database::number_of_investment_by_certain_current(const std::string current)
{
    unsigned int number;
    number = std::count_if(database.begin(), database.end(), [current](Investment& investment){return investment.get_investment_current() == current;});
    return number;
}

unsigned int Database::save_database(const std::string path_file)
{
    unsigned int lines_number = 0;
    auto start = std::chrono::system_clock::now();
    std::vector<Investment>::iterator investment;
    std::fstream file;
    file.open(path_file, std::ios::out);
    if (file.good() == false)
    {
        throw std::invalid_argument("File does not exist!");
    }
    else
    {
        file<<"funds, interest_rate, years, tax_state, tax_rate, capitalization_number_per_year, investment_current"<<std::endl;
        lines_number++;
        for (investment = database.begin(); investment != database.end(); investment++)
        {
            file<<(*investment).check_funds()<<", ";
            file<<(*investment).get_interest_rate()<<", ";
            file<<(*investment).get_years()<<", ";
            file<<(*investment).get_tax_state()<<", ";
            file<<(*investment).get_tax_rate()<<", ";
            file<<(*investment).get_capitalization_number_per_year()<<", ";
            file<<(*investment).get_investment_current()<<", ";
            file<<"\n";
            lines_number++;
        }
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> seconds = end - start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        file<<std::ctime(&end_time);
        file<<seconds.count();
        lines_number +=2;
        file.close();
    }
    return lines_number;
}

void Database::load_database(const std::string path_file)
{
    std::fstream file;
    file.open(path_file, std::ios::in);
    if (file.good() == false)
    {
        throw std::invalid_argument("File does not exist!");
    }
    else
    {
        std::string line;
        std::string delimiter = ", ";
        int line_number=1;
        int total_lines=0;
        while (getline(file, line))
        {
            total_lines++;
        }
        file.close();
        file.open(path_file, std::ios::in);
        while(getline(file, line))
        {
            if (line_number == 1)
            {
                line_number++;
                continue;
            }
            else
            {
                if(line_number <= total_lines-2)
                {
                    size_t position = 0; 
                    std::string attribute;
                    std::vector<std::string> object_properties;
                    Investment investment;
                    while ((position = line.find(delimiter)) != std::string::npos)
                    {
                        attribute = line.substr(0, position);
                        object_properties.push_back(attribute);
                        line.erase(0, position + delimiter.length());
                    }
                    investment.change_account_state(std::stod(object_properties[0]));
                    investment.change_interest_rate(std::stod(object_properties[1]));
                    investment.set_years(std::stoi(object_properties[2]));
                    bool tax_state;
                    std::istringstream(object_properties[3]) >> tax_state;
                    investment.set_tax_state(tax_state);
                    investment.set_tax_rate(std::stoi(object_properties[4]));
                    investment.set_capitalization_number_per_year(std::stoi(object_properties[5]));
                    investment.set_investment_current(object_properties[6]);
                    database.push_back(investment);
                    line_number++;
                }
            }
        }
    }
}

bool Database::operator==(const Database& database_parameter) const
{
    return (this->database == database_parameter.database);
}

bool Database::operator!=(const Database& database_parameter) const
{
    return !(*this == database_parameter);
}

Database& Database::operator+=(Database& database_parameter)
{
    std::vector<Investment> database_to_add = database_parameter.get_list();
    std::vector<Investment> converted_database = this->get_list();
    converted_database.insert(converted_database.end(), database_to_add.begin(), database_to_add.end());
    this->set_list(converted_database);
    return *this;
}