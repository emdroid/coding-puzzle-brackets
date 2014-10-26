/**
    @file

    The stream input reader (implementation).

    @author Emil Maskovsky
*/

// BracketPuzzle
#include "BracketPuzzle/StreamInputReader.hpp"


namespace BracketPuzzle
{


StreamInputReader::StreamInputReader(std::istream & in)
    : m_in(in)
{
}


/* The IInputReader interface */

bool StreamInputReader::readLine(
    std::string & str) const
{
    std::getline(m_in, str);
    return m_in.good();
}


} // namespace BracketPuzzle


/* EOF */
