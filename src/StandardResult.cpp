/**
    @file

    The standard result (implementation).

    @author Emil Maskovsky
*/

// BracketPuzzle
#include "BracketPuzzle/StandardResult.hpp"


namespace BracketPuzzle
{


StandardResult::StandardResult(bool value)
    : m_value(value)
{
}


/* The IResult interface */

ResultPtr StandardResult::clone() const
{
    return std::make_shared< StandardResult >(*this);
}


bool StandardResult::isEqual(const IResult & other) const
{
    const StandardResult * const other_derived
        = dynamic_cast< const StandardResult * >(&other);
    return (other_derived != NULL) && checkEqual(*other_derived);
}


bool StandardResult::isLesserThan(const IResult & other) const
{
    const StandardResult * const other_derived
        = dynamic_cast< const StandardResult * >(&other);
    return (other_derived != NULL) && checkLesserThan(*other_derived);
}


std::ostream & StandardResult::write(
    std::ostream & out) const
{
    return out << (m_value ? "True" : "False");
}


bool StandardResult::checkEqual(const StandardResult & other) const
{
    return m_value == other.m_value;
}


bool StandardResult::checkLesserThan(const StandardResult & other) const
{
    return m_value < other.m_value;
}


} // namespace BracketPuzzle


/* EOF */
