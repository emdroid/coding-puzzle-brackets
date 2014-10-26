/**
    @file

    The vector output writer (interface).

    @author Emil Maskovsky
*/

#ifndef BRACKETS_PUZZLE_VECTOR_OUTPUT_WRITER_HPP_2001410261847
#define BRACKETS_PUZZLE_VECTOR_OUTPUT_WRITER_HPP_2001410261847

// standard library
#include <vector>

// BracketPuzzle
#include "BracketPuzzle/IOutputWriter.hpp"


namespace BracketPuzzle
{


class VectorOutputWriter
    : public IOutputWriter
{

public:

    const std::vector< std::string > & getData() const;

    /* The IOutputWriter interface */

    bool writeLine(
        const std::string & str);

private:

    /** The output data. */
    std::vector< std::string > m_data;

}; // class VectorOutputWriter


} // namespace BracketPuzzle


#endif // BRACKETS_PUZZLE_VECTOR_OUTPUT_WRITER_HPP_2001410261847

/* EOF */
