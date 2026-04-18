// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdexcept>
#include <string>

// Custom exception to create, throw, and catch custom exception type.
class CustomApplicationException : public std::exception
{
private:
    std::string message;

public:
    explicit CustomApplicationException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

bool do_even_more_custom_application_logic()
{
    std::cout << "Running Even More Custom Application Logic." << std::endl;
    throw std::runtime_error("Standard exception from do_even_more_custom_application_logic().");
    return false;
}

void do_custom_application_logic()
{
    std::cout << "Running Custom Application Logic." << std::endl;

    // Wrap the call in a try/catch that handles std::exception, prints message, then continues
    try
    {
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Caught std::exception in do_custom_application_logic: "
            << e.what() << std::endl;
    }

    std::cout << "Leaving Custom Application Logic." << std::endl;
    // Throw a custom exception derived from std::exception
    throw CustomApplicationException("Custom application exception thrown from do_custom_application_logic().");

}

float divide(float num, float den)
{
    // Use standard exception for divide-by-zero.
    if (den == 0.0f)
    {
        throw std::runtime_error("Divide by zero error in divide().");
    }

    return (num / den);
}

void do_division() noexcept
{
    //Handler to catch standard exception thrown by divide(), then print the message, and continue
    try
    {
        float numerator = 10.0f;
        float denominator = 0.0f;

        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Caught divide exception in do_division: "
            << e.what() << std::endl;
    }
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    try
    {
        do_division();
        do_custom_application_logic();
    }
    catch (const CustomApplicationException& e)
    {
        std::cout << "Caught custom exception in main: "
            << e.what() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Caught std::exception in main: "
            << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Caught an unknown exception in main." << std::endl;
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu