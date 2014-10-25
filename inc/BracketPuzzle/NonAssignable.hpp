/**
    @file

    The non assignable class.

    @author Emil Maskovsky
*/


#ifndef BRACKETS_PUZZLE_NON_ASSIGNABLE_HPP_2001410251932
#define BRACKETS_PUZZLE_NON_ASSIGNABLE_HPP_2001410251932

// standard library
#include <string>


namespace BracketPuzzle
{


/**
    The non assignable class.

    To disable assignment for a particular class, inherit from the
    NonAssignable by using private inheritance like this:
    @code
    class Example
        : public BaseClass
        ...
        , private NonAssignable
    {
        ...
    };
    @endcode

    The private inheritance is particularly important, because the
    NonAssignable class does not have a virtual destructor (to not pay
    for the virtual inheritance in non-virtual classes). The private
    inheritance should ensure that nobody will use this class to
    polymorfically access the derived class.
*/
class NonAssignable
{

    // declare the private assignment operator
    // (so that it cannot be used)
    NonAssignable & operator =(const NonAssignable &);

    // note that actual definition of the operator body is not necessary

}; // class NonAssignable


} // namespace BracketPuzzle


#endif // BRACKETS_PUZZLE_NON_ASSIGNABLE_HPP_2001410251932

/* EOF */
