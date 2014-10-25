/**
    @file

    The abstract string validator interface.

    @author Emil Maskovsky
*/


#ifndef BRACKETS_PUZZLE_I_VALIDATOR_HPP_2001410251817
#define BRACKETS_PUZZLE_I_VALIDATOR_HPP_2001410251817

// standard library
#include <string>


namespace BracketPuzzle
{


/**
    The abstract string validator interface.
*/
class IValidator
{

public:

    /**
        The destructor.
    */
    virtual ~IValidator()
    {
    }

    /**
        Validate the input string.

        @param [in] str The input string.

        @return bool
            Returns @c true if the string is well formed (validated),
            @c false otherwise.
    */
    virtual bool validate(
        const std::string & str) const = 0;

}; // class IValidator


} // namespace BracketPuzzle


#endif // BRACKETS_PUZZLE_I_VALIDATOR_HPP_2001410251817

/* EOF */
