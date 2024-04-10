// Autor: Adam Czubak
// Testy jednostkowe metod i operatorów zawartych w klasie.

#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include "/home/adamczubak/Zad2/investment.h"
#include "/home/adamczubak/Zad2/investment.cpp"
#include "database.h"

TEST_CASE("Getting list.")
{
    Investment investment1(35.45, 23, 2, false, 4);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 45);
    Investment investment4(123.23, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    std::vector<Investment> given_result = database.get_list();
    std::vector<Investment> expected_result = {investment1, investment2, investment3, investment4};
    REQUIRE(given_result == expected_result);
}

TEST_CASE("Setting list.")
{
    Investment investment1(35.45, 23, 2, false, 4);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 45);
    Investment investment4(123.23, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    database.set_list({investment1, investment2});
    std::vector<Investment> given_result = database.get_list();
    std::vector<Investment> expected_result = {investment1, investment2};
    REQUIRE(given_result == expected_result);
}

TEST_CASE("Getting number of investments in database.")
{
    Investment investment1(35.45, 23, 2, false, 4);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 45);
    Investment investment4(123.23, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE(database.get_number_of_investments() == 4);
}

TEST_CASE("Clearing list.")
{
    Investment investment1(35.45, 23, 2, false, 4);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 45);
    Investment investment4(123.23, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    database.clear_list();
    REQUIRE(database.get_list().empty() == true);
}

TEST_CASE("Adding investment.")
{
    Investment investment1(35.45, 23, 2, false, 4);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 45);
    Database database({investment1, investment2, investment3});
    Investment investment4(123.23, 34, 3, false, 0, 234, "GBP");
    database.add_investment(investment4);
    REQUIRE(database.get_list().size() == 4);
}

TEST_CASE("Removing investment.")
{
    Investment investment1(35.45, 23, 2, false, 4);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 45);
    Investment investment4(123.23, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    database.remove_investment(investment4);
    REQUIRE(database.get_list().size() == 3); 
}

TEST_CASE("Removing investment that is not in database.")
{
    Investment investment1(35.45, 23, 2, false, 4);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 45);
    Investment investment4(123.23, 34, 3, false, 0, 234, "GBP");
    Investment investment5(123.23, 34, 3, false, 0, 234, "EUR");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE_THROWS_WITH(database.remove_investment(investment5), "There is no such investment here!"); 
}

TEST_CASE("Searching investment.")
{
    Investment investment1(35.45, 23, 2, false, 4);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 45);
    Investment investment4(123.23, 34, 3, false, 0, 234, "GBP");
    Investment investment5(3.50);
    Database database({investment4, investment1, investment2, investment3});
    int given_position_number = database.search_investment(investment2);
    int expected_position_number = 3;
    REQUIRE(given_position_number == expected_position_number); 
}

TEST_CASE("Searching investment that is not in the database.")
{
    Investment investment1(35.45, 23, 2, false, 4);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 45);
    Investment investment4(123.23, 34, 3, false, 0, 234, "GBP");
    Investment investment5(3.50);
    Database database({investment4, investment1, investment2, investment3});
    REQUIRE_THROWS_WITH(database.search_investment(investment5), "There is no such investment in the database!"); 
}

TEST_CASE("Sorting by attribute: funds - increasing.")
{
    Investment investment1(35.45, 23, 2, false, 4);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 45);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    Database sorted_database({investment1, investment4, investment3, investment2});
    database.sort_list_by_number_attribute("funds");
    std::vector<Investment> before_sorting = database.get_list();
    std::vector<Investment> after_sorting = sorted_database.get_list();
    REQUIRE(before_sorting == after_sorting);
}

TEST_CASE("Sorting by attribute: funds - decreasing.")
{
    Investment investment1(35.45, 23, 2, false, 4);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 45);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    Database sorted_database({investment2, investment3, investment4, investment1});
    database.sort_list_by_number_attribute("funds", "-");
    std::vector<Investment> before_sorting = database.get_list();
    std::vector<Investment> after_sorting = sorted_database.get_list();
    REQUIRE(before_sorting == after_sorting);
}

TEST_CASE("Sorting by attribute: interest rate - increasing.")
{
    Investment investment1(35.45, 23, 2, false, 4);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 45);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    Database sorted_database({investment1, investment2, investment4, investment3});
    database.sort_list_by_number_attribute("interest_rate");
    std::vector<Investment> before_sorting = database.get_list();
    std::vector<Investment> after_sorting = sorted_database.get_list();
    REQUIRE(before_sorting == after_sorting);
}

TEST_CASE("Sorting by attribute: interest rate - decreasing.")
{
    Investment investment1(35.45, 23, 2, false, 4);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 45);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    Database sorted_database({investment3, investment4, investment2, investment1});
    database.sort_list_by_number_attribute("interest_rate", "-");
    std::vector<Investment> before_sorting = database.get_list();
    std::vector<Investment> after_sorting = sorted_database.get_list();
    REQUIRE(before_sorting == after_sorting);
}

TEST_CASE("Sorting by attribute: years - increasing.")
{
    Investment investment1(35.45, 23, 2, false, 4);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 45);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    Database sorted_database({investment1, investment3, investment4, investment2});
    database.sort_list_by_number_attribute("years");
    std::vector<Investment> before_sorting = database.get_list();
    std::vector<Investment> after_sorting = sorted_database.get_list();
    REQUIRE(before_sorting == after_sorting);
}

TEST_CASE("Sorting by attribute: years - decreasing.")
{
    Investment investment1(35.45, 23, 2, false, 4);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 45);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    Database sorted_database({investment2, investment4, investment3, investment1});
    database.sort_list_by_number_attribute("years", "-");
    std::vector<Investment> before_sorting = database.get_list();
    std::vector<Investment> after_sorting = sorted_database.get_list();
    REQUIRE(before_sorting == after_sorting);
}

TEST_CASE("Sorting by attribute: tax rate - increasing.")
{
    Investment investment1(35.45, 23, 2, false, 4);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 45);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    Database sorted_database({investment4, investment1, investment3, investment2});
    database.sort_list_by_number_attribute("tax_rate");
    std::vector<Investment> before_sorting = database.get_list();
    std::vector<Investment> after_sorting = sorted_database.get_list();
    REQUIRE(before_sorting == after_sorting);
}

TEST_CASE("Sorting by attribute: tax rate - decreasing.")
{
    Investment investment1(35.45, 23, 2, false, 4);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 45);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    Database sorted_database({investment2, investment3, investment1, investment4});
    database.sort_list_by_number_attribute("tax_rate", "-");
    std::vector<Investment> before_sorting = database.get_list();
    std::vector<Investment> after_sorting = sorted_database.get_list();
    REQUIRE(before_sorting == after_sorting);
}

TEST_CASE("Sorting by attribute: capitalization number per year - increasing.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    Database sorted_database({investment2, investment4, investment1, investment3});
    database.sort_list_by_number_attribute("capitalization_number_per_year", "+");
    std::vector<Investment> before_sorting = database.get_list();
    std::vector<Investment> after_sorting = sorted_database.get_list();
    REQUIRE(before_sorting == after_sorting);
}

TEST_CASE("Sorting by attribute: capitalization number per year - decreasing.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    Database sorted_database({investment3, investment1, investment4, investment2});
    database.sort_list_by_number_attribute("capitalization_number_per_year", "-");
    std::vector<Investment> before_sorting = database.get_list();
    std::vector<Investment> after_sorting = sorted_database.get_list();
    REQUIRE(before_sorting == after_sorting);
}

TEST_CASE("Sorting by attribute that does not exist.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE_THROWS_WITH(database.sort_list_by_number_attribute("owner", "+"), "Investment does not have that property!");
}

TEST_CASE("Sorting in direction that does not exist.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE_THROWS_WITH(database.sort_list_by_number_attribute("funds", "___"), "Wrong direction!");
}

TEST_CASE("Sorting by wrong direction and wrong attribute.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE_THROWS_WITH(database.sort_list_by_number_attribute("owner", "---"), "Investment does not have that property!");
}

TEST_CASE("Get number of investments above certain funds value.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE(database.number_of_investment_by_funds(230.56, ">") == 2);
}

TEST_CASE("Get number of investments below certain funds value.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE(database.number_of_investment_by_funds(400, "<") == 3);
}

TEST_CASE("Get number of investments equal certain funds value.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE(database.number_of_investment_by_funds(36.76, "=") == 0);
}

TEST_CASE("Get number of investments by funds - wrong relationship!")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE_THROWS_WITH(database.number_of_investment_by_funds(45.46, "====="), "Wrong relationship!");
}

TEST_CASE("Get number of investments above certain interest rate value.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE(database.number_of_investment_by_interest_rate(26.5, ">") == 3);
}

TEST_CASE("Get number of investments below certain interest rate value.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE(database.number_of_investment_by_interest_rate(50.57, "<") == 4);
}

TEST_CASE("Get number of investments equal certain interest rate value.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE(database.number_of_investment_by_interest_rate(34, "=") == 2);
}

TEST_CASE("Get number of investments by interest rate - wrong relationship!")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE_THROWS_WITH(database.number_of_investment_by_interest_rate(56.34, "ddd"), "Wrong relationship!");
}

TEST_CASE("Get number of investments above certain years value.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE(database.number_of_investment_by_years(4, ">") == 1);
}

TEST_CASE("Get number of investments below certain years value.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE(database.number_of_investment_by_years(4, "<") == 3);
}

TEST_CASE("Get number of investments equal certain years value.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE(database.number_of_investment_by_years(3, "=") == 2);
}

TEST_CASE("Get number of investments by years - wrong relationship!")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE_THROWS_WITH(database.number_of_investment_by_years(5, ","), "Wrong relationship!");
}

TEST_CASE("Get number of investments by tax state equals true.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE(database.number_of_investment_by_tax_state(true) == 1);
}

TEST_CASE("Get number of investments by tax state equals false.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE(database.number_of_investment_by_tax_state(false) == 3);
}

TEST_CASE("Get number of investments above certain tax rate.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE(database.number_of_investment_by_tax_rate(2, ">") == 3);
}

TEST_CASE("Get number of investments below certain tax rate.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE(database.number_of_investment_by_tax_rate(5, "<") == 3);
}

TEST_CASE("Get number of investments equal certain tax rate.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE(database.number_of_investment_by_tax_rate(4, "=") == 2);
}

TEST_CASE("Get number of investments by tax rate - wrong relationship!")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE_THROWS_WITH(database.number_of_investment_by_tax_rate(4, ""), "Wrong relationship!");
}

TEST_CASE("Get number of investments above certain capitalization per year value.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE(database.number_of_investment_by_capitalization(100, ">") == 3);
}

TEST_CASE("Get number of investments below certain capitalization per year value.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE(database.number_of_investment_by_capitalization(250, "<") == 2);
}

TEST_CASE("Get number of investments equal certain paitalization per year value.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE(database.number_of_investment_by_capitalization(546, "=") == 2);
}

TEST_CASE("Get number of investments by capitalization per year - wrong relationship!")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE_THROWS_WITH(database.number_of_investment_by_capitalization(45, "qwerty"), "Wrong relationship!");
}

TEST_CASE("Get number of investments by existing current.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546, "GBP");
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546, "EUR");
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE(database.number_of_investment_by_certain_current("GBP") == 2);
}

TEST_CASE("Get number of investments by non-existing current.")
{
    Investment investment1(35.45, 23, 2, false, 4, 546);
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 546);
    Investment investment4(35.45, 34, 3, false, 0, 234, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE(database.number_of_investment_by_certain_current("RUB") == 0);
}

TEST_CASE("Write databse to file.")
{
    Investment investment1(35.45, 23, 2, false, 4, 46, "EUR");
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 46, "CHF");
    Investment investment4(35.45, 34, 3, false, 2, 34, "GBP");
    Database database({investment1, investment2, investment3, investment4});
    REQUIRE(database.save_database("database.csv") == 7);
}

TEST_CASE("Load database from file.")
{
    Investment investment1(35.45, 23, 2, false, 4, 46, "EUR");
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 46, "CHF");
    Investment investment4(35.45, 34, 3, false, 2, 34, "GBP");
    Database expected_database({investment1, investment2, investment3, investment4});
    std::vector<Investment> empty_vector = {};
    Database database(empty_vector);
    database.load_database("database.csv");
    REQUIRE(database.get_list() == expected_database.get_list());
}

TEST_CASE("Test operator == - result true.")
{
    Investment investment1(35.45, 23, 2, false, 4, 46, "EUR");
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 46, "CHF");
    Investment investment4(35.45, 34, 3, false, 2, 34, "GBP");
    Database database1({investment1, investment2});
    Database database2({investment1, investment2});
    REQUIRE((database1 == database2) == true); 
}

TEST_CASE("Test operator == - result false.")
{
    Investment investment1(35.45, 23, 2, false, 4, 46, "EUR");
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 46, "CHF");
    Investment investment4(35.45, 34, 3, false, 2, 34, "GBP");
    Database database1({investment1, investment2});
    Database database2({investment1, investment3});
    REQUIRE((database1 == database2) == false); 
}

TEST_CASE("Test operator != - result true.")
{
    Investment investment1(35.45, 23, 2, false, 4, 46, "EUR");
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 46, "CHF");
    Investment investment4(35.45, 34, 3, false, 2, 34, "GBP");
    Database database1({investment1, investment2});
    Database database2({investment1, investment3});
    REQUIRE((database1 != database2) == true); 
}

TEST_CASE("Test operator != - result false.")
{
    Investment investment1(35.45, 23, 2, false, 4, 46, "EUR");
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 46, "CHF");
    Investment investment4(35.45, 34, 3, false, 2, 34, "GBP");
    Database database1({investment1, investment2});
    Database database2({investment1, investment2});
    REQUIRE((database1 != database2) == false); 
}

TEST_CASE("Test operator +=")
{
    Investment investment1(35.45, 23, 2, false, 4, 46, "EUR");
    Investment investment2(464.23, 34, 5, true, 23, 2, "PLN");
    Investment investment3(234.43, 45, 3, false, 4, 46, "CHF");
    Investment investment4(35.45, 34, 3, false, 2, 34, "GBP");
    Database database1({investment1, investment2});
    Database database2({investment3, investment4});
    Database expected_database({investment1, investment2, investment3, investment4});
    REQUIRE((database1 += database2) == expected_database); 
}