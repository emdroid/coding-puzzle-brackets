/**
    @file

    The abstract input reader interface.

    @author Emil Maskovsky
*/


#ifndef BRACKETS_PUZZLE_I_INPUT_READER_HPP_2001410251817
#define BRACKETS_PUZZLE_I_INPUT_READER_HPP_2001410251817

// standard library
#include <string>


namespace BracketPuzzle
{


/**
    The abstract input reader interface.
*/
class IInputReader
{

public:

    /**
        The destructor.
    */
    virtual ~IInputReader()
    {
    }

    /**
        Read a single input line into the string.

        @param [out] str The output string.

        @return bool
            Returns @c true if there was another string available,
            @c false otherwise.
    */
    virtual bool readLine(
        std::string & str) const = 0;

}; // class IInputReader


} // namespace BracketPuzzle


#endif // BRACKETS_PUZZLE_I_INPUT_READER_HPP_2001410251817

/* EOF */
