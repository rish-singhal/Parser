#pragma once

#include "../src/solver.h"

void test
        (
                std::string const& inputExpression,
                double const& expectedOutput,
                bool const& expectedError
        )
{
    const auto &[isError, value] = solve(inputExpression);
    assert(isError == expectedError);
    if (!isError)
        assert(value == expectedOutput);
}

void test_all()
{
    test("1 + 1", 2, false);
    test("1 + (2 * 5)", 11, false);
    test("1 * 2 + 5", 7, false);
    test("(1 + 1) * (2 +  5)", 14, false);
    test("1 / (1 + 2) + 3", (double) 3 + (1.0/3), false);
    test("5 - 5 -5", -5, false);
    test("(1) + (2)", 3, false);

    test("(1 + 1", 0, true);
    test("-1", 0, true);
    test("1 + ) * 2", 0, true);
    test("22 + 5x", 0, true);
    test("33", 0, true);
}
