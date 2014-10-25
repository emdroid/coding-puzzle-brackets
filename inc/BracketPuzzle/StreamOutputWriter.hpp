/**
    @file

    The stream output writer (interface).

    @author Emil Maskovsky
*/


#ifndef BRACKETS_PUZZLE_STREAM_OUTPUT_WRITER_HPP_2001410251858
#define BRACKETS_PUZZLE_STREAM_OUTPUT_WRITER_HPP_2001410251858

// standard library
#include <ostream>

// BracketPuzzle
#include "BracketPuzzle/IOutputWriter.hpp"
#include "BracketPuzzle/NonAssignable.hpp"


namespace BracketPuzzle
{


/**
    The stream input reader.
*/
class StreamOutputWriter
    : public IOutputWriter
    , private NonAssignable
{

public:

    explicit StreamOutputWriter(std::ostream & out);

    /* The IOutputWriter interface */

    bool writeLine(
        const std::string & str);

private:

    /** The associated output stream. */
    std::ostream & m_out;

}; // class IOutputWriter


} // namespace BracketPuzzle


#endif // BRACKETS_PUZZLE_STREAM_OUTPUT_WRITER_HPP_2001410251858

/* EOF */
