/**
    @file

    The multi threaded result (interface).

    @author Emil Maskovsky
*/


#ifndef BRACKETS_PUZZLE_MULTITHREAD_RESULT_HPP_2001410271452
#define BRACKETS_PUZZLE_MULTITHREAD_RESULT_HPP_2001410271452

// BracketPuzzle
#include "BracketPuzzle/StandardResult.hpp"


namespace BracketPuzzle
{


/**
    The multi threaded result.
*/
class MultithreadResult
    : public StandardResult
{

public:

    /**
        Constructor.

        @param [in] order The ordinal number of the result.
        @param [in] value The value of the result.
    */
    MultithreadResult(size_t order, bool value);

    /* The IResult interface */

    virtual ResultPtr clone() const;

    virtual bool isEqual(const IResult & other) const;

    virtual bool isLesserThan(const IResult & other) const;

    virtual std::ostream & write(
        std::ostream & out) const;

protected:

    bool checkEqual(const MultithreadResult & other) const;

    bool checkLesserThan(const MultithreadResult & other) const;

private:

    size_t m_order;

}; // class MultithreadResult


} // namespace BracketPuzzle


#endif // BRACKETS_PUZZLE_MULTITHREAD_RESULT_HPP_2001410271452

/* EOF */
