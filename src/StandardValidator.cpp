/**
    @file

    The standard string validator (implementation).

    @author Emil Maskovsky
*/

// BracketPuzzle
#include "BracketPuzzle/StandardValidator.hpp"


namespace BracketPuzzle
{


/* The IValidator interface */

bool StandardValidator::validate(
    const std::string & str) const
{
    bool valid = !str.empty();

    // TODO Implement here.

    return valid;
}


} // namespace BracketPuzzle


/* EOF */
