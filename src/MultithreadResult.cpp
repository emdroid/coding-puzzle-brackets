/**
    @file

    The multi threaded result (implementation).

    @author Emil Maskovsky
*/

// BracketPuzzle
#include "BracketPuzzle/MultithreadResult.hpp"


namespace BracketPuzzle
{


MultithreadResult::MultithreadResult(size_t order, bool value)
    : StandardResult(value)
    , m_order(order)
{
}


/* The IResult interface */

ResultPtr MultithreadResult::clone() const
{
    return std::make_shared< MultithreadResult >(*this);
}


bool MultithreadResult::isEqual(const IResult & other) const
{
    const MultithreadResult * const other_derived
        = dynamic_cast< const MultithreadResult * >(&other);
    return (other_derived != NULL) && checkEqual(*other_derived);
}


bool MultithreadResult::isLesserThan(const IResult & other) const
{
    const MultithreadResult * const other_derived
        = dynamic_cast< const MultithreadResult * >(&other);
    return (other_derived != NULL) && checkLesserThan(*other_derived);
}


std::ostream & MultithreadResult::write(
    std::ostream & out) const
{
    out << m_order << ':';
    return StandardResult::write(out);
}


bool MultithreadResult::checkEqual(
    const MultithreadResult & other) const
{
    return (StandardResult::checkEqual(other))
           && (m_order == other.m_order);
}


bool MultithreadResult::checkLesserThan(
    const MultithreadResult & other) const
{
    return (m_order < other.m_order)
           || (m_order == other.m_order
               && StandardResult::checkLesserThan(other));
}


} // namespace BracketPuzzle


/* EOF */
