/**
    @file

    The standard string validator (interface).

    @author Emil Maskovsky
*/


#ifndef BRACKETS_PUZZLE_STANDARD_VALIDATOR_HPP_2001410251856
#define BRACKETS_PUZZLE_STANDARD_VALIDATOR_HPP_2001410251856

// BracketPuzzle
#include "BracketPuzzle/IValidator.hpp"


namespace BracketPuzzle
{


/**
    The standard string validator.
*/
class StandardValidator
    : public IValidator
{

public:

    /* The IValidator interface */

    bool validate(
        const std::string & str) const;

}; // class StandardValidator


} // namespace BracketPuzzle


#endif // BRACKETS_PUZZLE_STANDARD_VALIDATOR_HPP_2001410251856

/* EOF */
