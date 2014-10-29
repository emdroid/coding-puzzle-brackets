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
    // clone the result (the original one might be destroyed after
    // returning from this method)
    ResultPtr duplicate = result.clone();
    // need to guard by lock for thread-safe writes
    std::lock_guard< std::mutex > guard(m_lock);
    m_data.push_back(duplicate);
    return true;
}


} // namespace BracketPuzzle


/* EOF */
