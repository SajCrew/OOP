#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <stdexcept>
#include "../Calculator/Calculator.h"
#include "../Calculator/Validation.h"

TEST_CASE("Variable creation and operations") {
    Variable var("x");

    SECTION("New variable should be undefined") {
        REQUIRE_FALSE(var.IsDefined());
    }

    SECTION("Setting value makes variable defined") {
        var.SetValue(42.0);
        REQUIRE(var.GetValue() == Approx(42.0));
        REQUIRE(var.IsDefined());
    }
}

TEST_CASE("Function creation and operations") {
    Variable x("x");
    Variable y("y");
    x.SetValue(10.0);
    y.SetValue(5.0);

    SECTION("Simple function (copy)") {
        Function fn("fn1", &x);
        REQUIRE(fn.GetValue() == Approx(10.0));
    }

    SECTION("Binary operations") {
        Function add("add", &x, &y, '+');
        REQUIRE(add.GetValue() == Approx(15.0));

        Function sub("sub", &x, &y, '-');
        REQUIRE(sub.GetValue() == Approx(5.0));

        Function mul("mul", &x, &y, '*');
        REQUIRE(mul.GetValue() == Approx(50.0));

        Function div("div", &x, &y, '/');
        REQUIRE(div.GetValue() == Approx(2.0));
    }

    SECTION("Undefined operands") {
        Variable undef("undef");
        Function fn("fn2", &undef);
        REQUIRE_FALSE(fn.IsDefined());

        Function fn3("fn3", &x, &undef, '+');
        REQUIRE_FALSE(fn3.IsDefined());
    }

    SECTION("Division by zero") {
        y.SetValue(0.0);
        Function div("div", &x, &y, '/');
        REQUIRE_FALSE(div.IsDefined());
    }
}

TEST_CASE("Calculator operations") {
    Calculator calc;

    SECTION("Variable commands") {
        calc.ProcessCommand("var x");
        REQUIRE(calc.GetIdentifierPtr("x") != nullptr);
        REQUIRE(std::isnan(calc.GetIdentifierPtr("x")->GetValue()));

        calc.ProcessCommand("let x = 42.5");
        REQUIRE(calc.GetIdentifierPtr("x")->GetValue() == Approx(42.5));

        calc.ProcessCommand("let y = x");
        REQUIRE(calc.GetIdentifierPtr("y")->GetValue() == Approx(42.5));
    }

    SECTION("Function commands") {
        calc.ProcessCommand("var x");
        calc.ProcessCommand("var y");
        calc.ProcessCommand("let x = 10");
        calc.ProcessCommand("let y = 5");

        calc.ProcessCommand("fn sum = x + y");
        REQUIRE(calc.GetIdentifierPtr("sum")->GetValue() == Approx(15.0));

        calc.ProcessCommand("let x = 20");
        REQUIRE(calc.GetIdentifierPtr("sum")->GetValue() == Approx(25.0));
    }

    SECTION("unknown commands") {
        REQUIRE_THROWS_WITH(calc.ProcessCommand("unknown cmd"), "Unknown command");
    }
    
    SECTION("unknown variable") {
        REQUIRE_THROWS_WITH(calc.ProcessCommand("unknown cmd"), "Unknown command");
    }

    // тест на присваивание переменной несуществующей переменной
    SECTION("let x = non exists variable") {
        calc.ProcessCommand("var x");

        REQUIRE_THROWS_WITH(calc.ProcessCommand("let x = z"), "Name does not exist");
    }
    // тест на присваивание переменной nan переменной
    SECTION("let x = nan variable") {
        calc.ProcessCommand("var x");
        calc.ProcessCommand("let x = 1");
        calc.ProcessCommand("var y");
        calc.ProcessCommand("let x = y");
       REQUIRE(std::isnan(calc.GetIdentifierPtr("x")->GetValue()));
    }
    //тест на повторное обьявление переменной
    SECTION("double var x") {
        calc.ProcessCommand("var x");
        
        REQUIRE_THROWS_WITH(calc.ProcessCommand("var x"), "Name already exists");
    }

    //добавить c fn обьявление переменных
}