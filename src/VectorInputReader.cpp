/**
    @file

    The vector input reader (implementation).

    @author Emil Maskovsky
*/

// BracketPuzzle
#include "BracketPuzzle/VectorInputReader.hpp"


namespace BracketPuzzle
{


VectorInputReader::VectorInputReader()
    : m_data()
    , m_position(0)
{
}


/**
    Append input line to the input reader.

    @param [in] str The input line.
*/
void VectorInputReader::insert(
    const std::string & str)
{
    m_data.push_back(str);
}


/* The IInputReader interface */

bool VectorInputReader::readLine(
    std::string & str) const
{
    bool ok = m_position < m_data.size();
    if (ok)
    {
        str = m_data[m_position++];
    }
    return ok;
}


} // namespace BracketPuzzle


/* EOF */
