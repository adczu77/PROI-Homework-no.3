// Autor: Adam Czubak
// Testy jednostkowe metod i operatorów zawartych w klasie.

#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include "investment.h"

TEST_CASE("Checking funds.")
{
    Investment investment(3000, 5, 2, false, 5, 2, "GBP");
    REQUIRE(investment.check_funds() == 3000);
}

TEST_CASE("Changing capital state.")
{
    Investment investment(94, 1, 9, true, 5, 2, "USD");
    investment.change_account_state(867.32);
    REQUIRE(investment.check_funds() == 867.32);
}

TEST_CASE("Adding funds to capital.")
{
    Investment investment(5000, 1, 2, false, 5, 2, "PLN");
    investment.add_funds(67.93);
    REQUIRE(investment.check_funds() == 5067.93);
}

TEST_CASE("Subtracting funds from capital.")
{
    Investment investment(450, 7.5, 3, false, 0, 2, "EUR");
    investment.add_funds(-55.57);
    REQUIRE(investment.check_funds() == 394.43);
}

TEST_CASE("Getting interest rate.")
{
    Investment investment(450, 7.54, 3, false, 0, 2, "EUR");
    REQUIRE(investment.get_interest_rate() == 7.54);
}

TEST_CASE("Setting interest rate.")
{
    Investment investment(230, 4.3, 5, true, 60, 3, "CHF");
    investment.change_interest_rate(6.73);
    REQUIRE(investment.get_interest_rate() == 6.73);
}

TEST_CASE("Getting years number.")
{
    Investment investment(234, 23, 4, false, 0, 4, "PLN");
    REQUIRE(investment.get_years() == 4);
}

TEST_CASE("Setting years number.")
{
    Investment investment(346, 5.76, 9, true, 23, 23, "GBP");
    investment.set_years(8);
    REQUIRE(investment.get_years() == 8);
}

TEST_CASE("Getting tax state.")
{
    Investment investment(94, 1, 9, true, 5, 2, "USD");
    REQUIRE(investment.get_tax_state() == true);
}

TEST_CASE("Setting tax state.")
{
    Investment investment(94, 1, 9, true, 5, 2, "USD");
    investment.set_tax_state(false);
    REQUIRE(investment.get_tax_state() == false);
}

TEST_CASE("Getting tax rate.")
{
    Investment investment(94, 1, 9, true, 5, 2, "USD");
    REQUIRE(investment.get_tax_rate() == 5);
}

TEST_CASE("Setting tax rate.")
{
    Investment investment(2234, 23, 3, true, 5, 3, "PLN");
    investment.set_tax_rate(19);
    REQUIRE(investment.get_tax_rate() == 19);
}

TEST_CASE("Getting capitalization number per year.")
{
    Investment investment(2234, 23, 3, true, 5, 3, "PLN");
    REQUIRE(investment.get_capitalization_number_per_year() == 3);
}

TEST_CASE("Setting capitalization number per year.")
{
    Investment investment(2234, 23, 3, true, 5, 3, "PLN");
    investment.set_capitalization_number_per_year(8);
    REQUIRE(investment.get_capitalization_number_per_year() == 8);
}

TEST_CASE("Checking if capitalization number per year gets default value.")
{
    Investment investment(2234, 23, 3, true, 5);
    REQUIRE(investment.get_capitalization_number_per_year() == 1);
}

TEST_CASE("Getting investment current.")
{
    Investment investment(2234, 23, 3, true, 5, 3, "PLN");
    REQUIRE(investment.get_investment_current() == "PLN");
}

TEST_CASE("Setting investment current.")
{
    Investment investment(2234, 23, 3, true, 5, 3, "PLN");
    investment.set_investment_current("GBP");
    REQUIRE(investment.get_investment_current() == "GBP");
}

TEST_CASE("Checking if investment current gets default value.")
{
    Investment investment(2234, 23, 3, true, 5, 3);
    REQUIRE(investment.get_investment_current() == "PLN");
}

TEST_CASE("Setting investment current but small letters are inputed.")
{
    Investment investment(2234, 23, 3, true, 5, 3, "PLN");
    investment.set_investment_current("gbp");
    REQUIRE(investment.get_investment_current() == "GBP");
}

TEST_CASE("Estimating profits without taxes. Data obtained from constructor.")
{
    Investment investment(2500, 5, 6, false, 5, 2, "PLN");
    REQUIRE(investment.estimate_profits(investment.get_interest_rate(),
            investment.get_years(),
            investment.get_tax_state(),
            investment.get_tax_rate(),
            investment.get_capitalization_number_per_year()) == 862.22);
}

TEST_CASE("Estimating profits with taxes. Data obtained from constructor.")
{
    Investment investment(2500, 5, 6, true, 48, 2, "PLN");
    REQUIRE(investment.estimate_profits(investment.get_interest_rate(),
            investment.get_years(),
            investment.get_tax_state(),
            investment.get_tax_rate(),
            investment.get_capitalization_number_per_year()) == 448.35);
}

TEST_CASE("Estimating profits without taxes. Data obtained from function arguments.")
{
    Investment investment(2500, 5, 6, true, 48, 2, "PLN");
    REQUIRE(investment.estimate_profits(5, 5, false, 99, 2) == 700.21);
}

TEST_CASE("Estimating profits with taxes. Data obtained from function arguments.")
{
    Investment investment(2500, 5, 6, true, 48, 2, "PLN");
    REQUIRE(investment.estimate_profits(5, 5, true, 17, 2) == 581.17);
}

TEST_CASE("Changing current.")
{
    Investment investment(2242, 5, 6, false, 5, 2, "PLN");
    REQUIRE(investment.convert_current("GBP", 0.17) == 381.14);
    CHECK(investment.check_funds() == 381.14);
    CHECK(investment.get_investment_current() == "GBP");
}

TEST_CASE("Setting interest rate below available range.")
{
    Investment investment(94, 1, 9, true, 5, 2, "USD");
    REQUIRE_THROWS_WITH(investment.change_interest_rate(-9.234), "Interest rate must be between 1 and 100!");
}

TEST_CASE("Setting interest rate above available range.")
{
    Investment investment(94, 1, 9, true, 5, 2, "USD");
    REQUIRE_THROWS_WITH(investment.change_interest_rate(125), "Interest rate must be between 1 and 100!");
}

TEST_CASE("Setting interest rate at zero.")
{
    Investment investment(94, 1, 9, true, 5, 2, "USD");
    REQUIRE_THROWS_WITH(investment.change_interest_rate(0), "Interest rate must be between 1 and 100!");
}

TEST_CASE("Setting year at zero.")
{
    Investment investment(450, 7.5, 4, false, 0, 2, "EUR");
    REQUIRE_THROWS_WITH(investment.set_years(0), "Years cannot be zero!");
}

TEST_CASE("Setting non-available current!")
{
    Investment investment(2234, 23, 3, true, 5, 3, "PLN");
    REQUIRE_THROWS_WITH(investment.set_investment_current("RUB"), "This current is not available!");
}

TEST_CASE("Converting current to not available one!")
{
    Investment investment(2234, 23, 3, true, 5, 3, "PLN");
    REQUIRE_THROWS_WITH(investment.convert_current("RUB", 23.94), "This current is not available!");
}

TEST_CASE("Converting current to the same one!")
{
    Investment investment(2234, 23, 3, true, 5, 3, "PLN");
    REQUIRE_THROWS_WITH(investment.convert_current("PLN", 2.01), "Resulting current cannot be the same as the present one!");
}

TEST_CASE("Getting default parameters of constructor.")
{
    Investment investment;
    CHECK(investment.check_funds() == 0);
    CHECK(investment.get_interest_rate() == 0);
    CHECK(investment.get_tax_rate() == 0);
    CHECK(investment.get_years() == 0);
    CHECK(investment.get_tax_state() == false);
    CHECK(investment.get_tax_rate() == 0);
}

TEST_CASE("Checking operator ++")
{
    Investment investment(2234, 23, 3, true, 5, 3, "PLN");
    investment++;
    REQUIRE(investment.check_funds() == 2334);
}

TEST_CASE("Checking operator --")
{
    Investment investment(2234, 23, 3, true, 5, 3, "PLN");
    investment--;
    REQUIRE(investment.check_funds() == 2134);
}

TEST_CASE("Checking operator +=")
{
    Investment investment(2234, 23, 3, true, 5, 3, "PLN");
    Investment investment2(10, 3.5, 1, true, 2, 3);
    investment += investment2;
    REQUIRE(investment.check_funds() == 2244);
    REQUIRE(investment.get_interest_rate() == 26.5);
    REQUIRE(investment.get_years() == 4);
    REQUIRE(investment.get_tax_rate() == 7);
    REQUIRE(investment.get_capitalization_number_per_year() == 6);
}

TEST_CASE("Checking operator -=")
{
    Investment investment(2234, 23, 3, true, 5, 3, "PLN");
    Investment investment2(10, 3.5, 1, true, 2, 2);
    investment -= investment2;
    REQUIRE(investment.check_funds() == 2224);
    REQUIRE(investment.get_interest_rate() == 19.5);
    REQUIRE(investment.get_years() == 2);
    REQUIRE(investment.get_tax_rate() == 3);
    REQUIRE(investment.get_capitalization_number_per_year() == 1);
}

TEST_CASE("Checking operator *=")
{
    Investment investment(2234, 23, 3, true, 5, 3, "PLN");
    Investment investment2(10, 2, 2, true, 2, 3);
    investment *= investment2;
    REQUIRE(investment.check_funds() == 22340);
    REQUIRE(investment.get_interest_rate() == 46);
    REQUIRE(investment.get_years() == 6);
    REQUIRE(investment.get_tax_rate() == 10);
    REQUIRE(investment.get_capitalization_number_per_year() == 9);
}

TEST_CASE("Checking operator /=")
{
    Investment investment(2234, 26, 3, true, 6, 3, "PLN");
    Investment investment2(10, 13, 1, true, 2, 3);
    investment /= investment2;
    REQUIRE(investment.check_funds() == 223.4);
    REQUIRE(investment.get_interest_rate() == 2);
    REQUIRE(investment.get_years() == 3);
    REQUIRE(investment.get_tax_rate() == 3);
    REQUIRE(investment.get_capitalization_number_per_year() == 1);
}

TEST_CASE("Checking operator +")
{
    Investment investment(2234, 23, 3, true, 5, 3, "PLN");
    Investment investment2(10, 3.5, 1, true, 2, 3);
    Investment result(2244, 26.5, 4, true, 7, 6);
    REQUIRE((investment+investment2) == result);
}

TEST_CASE("Checking operator -")
{
    Investment investment(2234, 23, 3, true, 5, 3, "PLN");
    Investment investment2(10, 3.5, 1, true, 2, 2);
    Investment result(2224, 19.5, 2, true, 3, 1);
    REQUIRE((investment-investment2) == result);
}

TEST_CASE("Checking operator *")
{
    Investment investment(2234, 23, 3, true, 5, 3, "PLN");
    Investment investment2(10, 2, 3, true, 4, 5);
    Investment result(22340, 46, 9, true, 20, 15);
    REQUIRE((investment*investment2) == result);
}

TEST_CASE("Checking operator /")
{
    Investment investment(2234, 26, 3, true, 10, 3, "PLN");
    Investment investment2(10, 4, 1, true, 2, 3);
    Investment result(223.4, 6.5, 3, true, 5, 1);
    REQUIRE((investment/investment2) == result);
}

TEST_CASE("Checking operator == - result true")
{
    Investment investment(2234, 26, 3, true, 10, 3, "PLN");
    Investment investment2(2234, 26, 3, true, 10, 3);
    REQUIRE((investment==investment2) == true);
}

TEST_CASE("Checking operator == - result false")
{
    Investment investment(2234, 26, 3, true, 10, 3, "PLN");
    Investment investment2(2234, 25, 3, true, 10, 3);
    REQUIRE((investment==investment2) == false);
}

TEST_CASE("Checking operator != - result true")
{
    Investment investment(2234, 26, 3, true, 10, 3, "PLN");
    Investment investment2(2234, 25, 3, true, 10, 3);
    REQUIRE((investment!=investment2) == true);
}

TEST_CASE("Checking operator != - result false")
{
    Investment investment(2234, 26, 3, true, 10, 3, "PLN");
    Investment investment2(2234, 26, 3, true, 10, 3);
    REQUIRE((investment!=investment2) == false);
}

TEST_CASE("Checking operator > - result true")
{
    Investment investment(2234, 26, 3, true, 10, 3, "PLN");
    Investment investment2(22, 2, 2, true, 1, 2);
    REQUIRE((investment>investment2) == true);
}

TEST_CASE("Checking operator > - result false")
{
    Investment investment(2234, 26, 3, true, 10, 3, "PLN");
    Investment investment2(22, 27, 2, true, 1, 2);
    REQUIRE((investment>investment2) == false);
}

TEST_CASE("Checking operator < - result true")
{
    Investment investment(2, 1, 1, true, 1, 1, "PLN");
    Investment investment2(22, 2, 2, true, 2, 2);
    REQUIRE((investment<investment2) == true);
}

TEST_CASE("Checking operator < - result false")
{
    Investment investment(2, 1, 1, true, 1, 1, "PLN");
    Investment investment2(22, 2, 1, true, 2, 2);
    REQUIRE((investment<investment2) == false);
}

TEST_CASE("Checking operator >= - result true")
{
    Investment investment(2234, 26, 4, true, 10, 3, "PLN");
    Investment investment2(2234, 2, 4, true, 10, 2);
    REQUIRE((investment>=investment2) == true);
}

TEST_CASE("Checking operator >= - result false")
{
    Investment investment(2234, 26, 3, true, 10, 3, "PLN");
    Investment investment2(2234, 27, 2, true, 1, 2);
    REQUIRE((investment>=investment2) == false);
}

TEST_CASE("Checking operator <= - result true")
{
    Investment investment(22, 1, 1, true, 1, 1, "PLN");
    Investment investment2(22, 2, 2, true, 2, 2);
    REQUIRE((investment<=investment2) == true);
}

TEST_CASE("Checking operator <= - result false")
{
    Investment investment(23, 1, 1, true, 1, 1, "PLN");
    Investment investment2(22, 2, 1, true, 2, 2);
    REQUIRE((investment<=investment2) == false);
}