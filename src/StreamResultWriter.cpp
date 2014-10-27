/**
    @file

    The stream result writer (implementation).

    @author Emil Maskovsky
*/

// standard library
#include <sstream>

// BracketPuzzle
#include "BracketPuzzle/StreamResultWriter.hpp"
#include "BracketPuzzle/IResult.hpp"


namespace BracketPuzzle
{


StreamResultWriter::StreamResultWriter(std::ostream & out)
    : m_out(out)
{
}


/* The IResultWriter interface */

bool StreamResultWriter::writeResult(
    const IResult & result)
{
    // write the entire line to a temporary string stream
    // this is to ensure, that the lines will not interleave
    // under multithreaded access
    std::ostringstream line;
    line << result << std::endl;
    m_out << line.str();
    return true;
}


} // namespace BracketPuzzle


/* EOF */
