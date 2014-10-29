/**
    @file

    The result interface (implementation).

    @author Emil Maskovsky
*/

// BracketPuzzle
#include "BracketPuzzle/IResult.hpp"


namespace BracketPuzzle
{


bool operator ==(const IResult & left, const IResult & right)
{
    // the RTTI check, if the objects are of the same type
    if (typeid(left) != typeid(right))
    {
        return false;
    }
    return left.isEqual(right);
}


bool operator <(const IResult & left, const IResult & right)
{
    return left.isLesserThan(right);
}


} // namespace BracketPuzzle


/* EOF */
