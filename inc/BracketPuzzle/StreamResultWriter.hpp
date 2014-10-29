/**
    @file

    The stream result writer (interface).

    @author Emil Maskovsky
*/


#ifndef BRACKETS_PUZZLE_STREAM_RESULT_WRITER_HPP_2001410251858
#define BRACKETS_PUZZLE_STREAM_RESULT_WRITER_HPP_2001410251858

// standard library
#include <ostream>

// BracketPuzzle
#include "BracketPuzzle/IResultWriter.hpp"
#include "BracketPuzzle/NonAssignable.hpp"


namespace BracketPuzzle
{


/**
    The stream result writer.

    Writes the result to stream.
*/
class StreamResultWriter
    : public IResultWriter
    , private NonAssignable
{

public:

    explicit StreamResultWriter(std::ostream & out);

    /* The IResultWriter interface */

    bool writeResult(
        const IResult & result);

private:

    /** The associated output stream. */
    std::ostream & m_out;

}; // class StreamResultWriter


} // namespace BracketPuzzle


#endif // BRACKETS_PUZZLE_STREAM_RESULT_WRITER_HPP_2001410251858

/* EOF */
