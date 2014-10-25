/**
    @file

    The abstract output writer interface.

    @author Emil Maskovsky
*/


#ifndef BRACKETS_PUZZLE_I_OUTPUT_WRITER_HPP_2001410251817
#define BRACKETS_PUZZLE_I_OUTPUT_WRITER_HPP_2001410251817

// standard library
#include <string>


namespace BracketPuzzle
{


/**
    The abstract input reader interface.
*/
class IOutputWriter
{

public:

    /**
        The destructor.
    */
    virtual ~IOutputWriter()
    {
    }

    /**
        Write a single line to the output.

        @param [in] str The output line.

        @return bool
            Returns @c true on success, @c false on failure.
    */
    virtual bool writeLine(
        const std::string & str) = 0;

}; // class IOutputWriter


} // namespace BracketPuzzle


#endif // BRACKETS_PUZZLE_I_OUTPUT_WRITER_HPP_2001410251817

/* EOF */
