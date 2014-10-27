/**
    @file

    Brackets coding puzzle - Part 1 (single threaded processing).

    @author Emil Maskovsky
*/

// standard library
#include <cstdlib>
#include <iostream>

// BracketPuzzle
#include "BracketPuzzle/StandardProcessor.hpp"
#include "BracketPuzzle/StandardValidator.hpp"
#include "BracketPuzzle/StreamInputReader.hpp"
#include "BracketPuzzle/StreamResultWriter.hpp"


int main()
{
    using namespace BracketPuzzle;

    int result = EXIT_SUCCESS;

    try
    {
        StandardValidator validator;
        StreamInputReader reader(std::cin);
        StreamResultWriter writer(std::cout);

        StandardProcessor processor;
        if (!processor.execute(validator, reader, writer))
        {
            result = EXIT_FAILURE;
        }
    }
    catch (const std::exception & e)
    {
        std::cerr << std::endl
                  << "FAILURE: Exception caught!" << std::endl
                  << "Message: " << e.what() << std::endl;

        result = EXIT_FAILURE;
    }

    return result;
}


/* EOF */
