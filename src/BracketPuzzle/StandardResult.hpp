/**
    @file

    The standard result (interface).

    @author Emil Maskovsky
*/


#ifndef BRACKETS_PUZZLE_STANDARD_RESULT_HPP_2001410271452
#define BRACKETS_PUZZLE_STANDARD_RESULT_HPP_2001410271452

// BracketPuzzle
#include "BracketPuzzle/IResult.hpp"


namespace BracketPuzzle
{


/**
    The standard result.
*/
class StandardResult
    : public IResult
{

public:

    /**
        Constructor.

        @param [in] value The value of the result.
    */
    explicit StandardResult(bool value);

    /* The IResult interface */

    virtual ResultPtr clone() const;

    virtual bool isEqual(const IResult & other) const;

    virtual bool isLesserThan(const IResult & other) const;

    virtual std::ostream & write(
        std::ostream & out) const;

protected:

    bool checkEqual(const StandardResult & other) const;

    bool checkLesserThan(const StandardResult & other) const;

private:

    bool m_value;

}; // class StandardResult


} // namespace BracketPuzzle


#endif // BRACKETS_PUZZLE_STANDARD_RESULT_HPP_2001410271452

/* EOF */
