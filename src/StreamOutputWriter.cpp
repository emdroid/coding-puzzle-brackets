/**
    @file

    The stream output writer (implementation).

    @author Emil Maskovsky
*/

// BracketPuzzle
#include "BracketPuzzle/StreamOutputWriter.hpp"


namespace BracketPuzzle
{


StreamOutputWriter::StreamOutputWriter(std::ostream & out)
    : m_out(out)
{
}


/* The IOutputWriter interface */

bool StreamOutputWriter::writeLine(
    const std::string & str)
{
    m_out << str << std::endl;
    return true;
}


} // namespace BracketPuzzle


/* EOF */
