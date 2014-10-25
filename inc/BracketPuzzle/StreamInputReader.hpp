/**
    @file

    The stream input reader (interface).

    @author Emil Maskovsky
*/


#ifndef BRACKETS_PUZZLE_STREAM_INPUT_READER_HPP_2001410251857
#define BRACKETS_PUZZLE_STREAM_INPUT_READER_HPP_2001410251857

// standard library
#include <istream>

// BracketPuzzle
#include "BracketPuzzle/IInputReader.hpp"
#include "BracketPuzzle/NonAssignable.hpp"


namespace BracketPuzzle
{


/**
    The stream input reader.
*/
class StreamInputReader
    : public IInputReader
    , private NonAssignable
{

public:

    explicit StreamInputReader(std::istream & in);

    /* The IInputReader interface */

    bool readLine(
        std::string & str) const;

private:

    /** The associated input stream. */
    std::istream & m_in;

}; // class StreamInputReader


} // namespace BracketPuzzle


#endif // BRACKETS_PUZZLE_STREAM_INPUT_READER_HPP_2001410251857

/* EOF */
