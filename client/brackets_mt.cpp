/**
    @file

    Brackets coding puzzle - Part 2 (multi threaded processing).

    @author Emil Maskovsky
*/

// standard library
#include <cstdlib>
#include <iostream>

// BracketPuzzle
#include "BracketPuzzle/MultithreadProcessor.hpp"
#include "BracketPuzzle/StandardValidator.hpp"
#include "BracketPuzzle/StreamInputReader.hpp"
#include "BracketPuzzle/StreamOutputWriter.hpp"


int main()
{
    using namespace BracketPuzzle;

    int result = EXIT_SUCCESS;

    try
    {
        StandardValidator validator;
        StreamInputReader reader(std::cin);
        StreamOutputWriter writer(std::cout);

        MultithreadProcessor processor;
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
