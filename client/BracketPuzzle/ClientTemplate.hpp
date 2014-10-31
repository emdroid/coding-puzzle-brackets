/**
    @file

    The brackets client template.

    @author Emil Maskovsky
*/


#ifndef BRACKETS_PUZZLE_CLIENT_TEMPLATE_HPP_2001410311407
#define BRACKETS_PUZZLE_CLIENT_TEMPLATE_HPP_2001410311407

// standard library
#include <cstdlib>
#include <iostream>

// Boost
#include <boost/exception/diagnostic_information.hpp>

// BracketPuzzle
#include "BracketPuzzle/StandardValidator.hpp"
#include "BracketPuzzle/StreamInputReader.hpp"
#include "BracketPuzzle/StreamResultWriter.hpp"


namespace BracketPuzzle
{


/**
    The brackets client template.

    @tparam PROCESSOR The brackets processor type.
*/
template< class PROCESSOR >
int clientRun()
{
    int result = EXIT_SUCCESS;

    try
    {
        StandardValidator validator;
        StreamInputReader reader(std::cin);
        StreamResultWriter writer(std::cout);

        PROCESSOR processor;
        if (!processor.execute(validator, reader, writer))
        {
            result = EXIT_FAILURE;
        }
    }
    catch (const boost::exception & e)
    {
        std::cerr << boost::diagnostic_information(e) << std::endl;
        result = EXIT_FAILURE;
    }
    catch (const std::exception & e)
    {
        std::cerr << std::endl
                  << "FAILURE: Exception caught!" << std::endl
                  << "Message: " << e.what() << std::endl;
        result = EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << std::endl
                  << "FAILURE: Unknown exception caught!" << std::endl;
        result = EXIT_FAILURE;
    }

    return result;
}


} // namespace BracketPuzzle


#endif // BRACKETS_PUZZLE_CLIENT_TEMPLATE_HPP_2001410311407

/* EOF */
