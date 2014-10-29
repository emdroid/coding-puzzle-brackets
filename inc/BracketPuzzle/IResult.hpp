/**
    @file

    The result interface.

    @author Emil Maskovsky
*/


#ifndef BRACKETS_PUZZLE_I_RESULT_HPP_2001410271432
#define BRACKETS_PUZZLE_I_RESULT_HPP_2001410271432

// standard library
#include <memory>
#include <ostream>


namespace BracketPuzzle
{


class IResult;

/**
    Shared pointer to IResult.
*/
typedef std::shared_ptr< IResult > ResultPtr;

/**
    Shared pointer to constant IResult.
*/
typedef std::shared_ptr< const IResult > ConstResultPtr;


/**
    The abstract result interface.
*/
class IResult
{

public:

    /**
        The destructor.
    */
    virtual ~IResult()
    {
    }

    /**
        Clone the result.

        Creates a (polymorphic) clone of the object.

        @return ResultPtr
            New instance of the result (polymorphically copied).
    */
    virtual ResultPtr clone() const = 0;

    /**
        Equality check with other IResult.

        @param [in] other The other IResult object.

        @warning
            The equality check is done polymorphically on the level of
            the actual type of the object. That means, if the other
            instance is a more derived type, it will still be considered
            equal as long as they are equal on the level of the current
            object.

        @return bool
            Returns @c true, if the objects are equal on current object
            level, @c false otherwise.
    */
    virtual bool isEqual(const IResult & other) const = 0;

    /**
        Less-than check with other IResult.

        @param [in] other The other IResult object.

        @warning
            The less-than check is done polymorphically on the level of
            the actual type of the object, similar to isEqual().

        @return bool
            Returns @c true, if the current objects is lesser-than the
            other object on the current object level, @c false
            otherwise.
    */
    virtual bool isLesserThan(const IResult & other) const = 0;

    /**
        Write the result to an output stream.

        @param [in] out The output stream.

        @return std::ostream &
            Returns reference of the output stream.
    */
    virtual std::ostream & write(
        std::ostream & out) const = 0;

}; // class IResult


/**
    IResult output streaming operator.

    @tparam OSTREAM_TYPE The output stream type.

    @param [out] out    The output stream.
    @param [in]  result The IResult reference.

    @return OSTREAM_TYPE &
        Returns reference of the output stream.
*/
template< class OSTREAM_TYPE >
OSTREAM_TYPE & operator <<(OSTREAM_TYPE & out, const IResult & result)
{
    result.write(out);
    return out;
}


/**
    IResult less-than comparison operator.

    @param [in] left
        The IResult object on the left side of the comparator.
    @param [in] right
        The IResult object on the right side of the comparator.

    @return bool
        Returns @c true when left < right, @c false otherwise.
*/
bool operator <(const IResult & left, const IResult & right);


} // namespace BracketPuzzle


#endif // BRACKETS_PUZZLE_I_RESULT_HPP_2001410271432

/* EOF */
