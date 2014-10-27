/**
    @file

    The vector result writer (implementation).

    @author Emil Maskovsky
*/

// BracketPuzzle
#include "BracketPuzzle/VectorResultWriter.hpp"


namespace BracketPuzzle
{


const VectorResultWriter::ValuesType & VectorResultWriter::getData() const
{
    return m_data;
}


/* The IResultWriter interface */

bool VectorResultWriter::writeResult(
    const IResult & result)
{
    m_data.push_back(result.clone());
    return true;
}


} // namespace BracketPuzzle


/* EOF */
