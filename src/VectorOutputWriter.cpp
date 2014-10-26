/**
    @file

    The vector output writer (implementation).

    @author Emil Maskovsky
*/

// BracketPuzzle
#include "BracketPuzzle/VectorOutputWriter.hpp"


namespace BracketPuzzle
{


const std::vector< std::string > & VectorOutputWriter::getData() const
{
    return m_data;
}


/* The IOutputWriter interface */

bool VectorOutputWriter::writeLine(
    const std::string & str)
{
    m_data.push_back(str);
    return true;
}


} // namespace BracketPuzzle


/* EOF */
