/**
    @file

    The vector input reader (interface).

    @author Emil Maskovsky
*/

#ifndef BRACKETS_PUZZLE_VECTOR_INPUT_READER_HPP_2001410261845
#define BRACKETS_PUZZLE_VECTOR_INPUT_READER_HPP_2001410261845

// standard library
#include <vector>

// BracketPuzzle
#include "BracketPuzzle/IInputReader.hpp"


namespace BracketPuzzle
{


class VectorInputReader
    : public IInputReader
{

public:

    VectorInputReader();

    /**
        Append input line to the input reader.

        @param [in] str The input line.
    */
    void insert(
        const std::string & str);

    /* The IInputReader interface */

    bool readLine(
        std::string & str) const;

private:

    /** The input data. */
    std::vector< std::string > m_data;

    /** The actual input reader position. */
    mutable std::vector< std::string >::size_type m_position;

}; // class VectorInputReader


} // namespace BracketPuzzle


#endif // BRACKETS_PUZZLE_VECTOR_INPUT_READER_HPP_2001410261845

/* EOF */
