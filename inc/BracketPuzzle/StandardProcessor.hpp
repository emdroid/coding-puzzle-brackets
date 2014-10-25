/**
    @file

    The standard string processor (interface).

    @author Emil Maskovsky
*/


#ifndef BRACKETS_PUZZLE_STANDARD_PROCESSOR_HPP_2001410251753
#define BRACKETS_PUZZLE_STANDARD_PROCESSOR_HPP_2001410251753

// BracketPuzzle
#include "BracketPuzzle/IProcessor.hpp"


namespace BracketPuzzle
{


/**
    The standard string processor.
*/
class StandardProcessor
    : public IProcessor
{

public:

    /* The IProcessor interface */

    bool execute(
        const IValidator & validator,
        const IInputReader & reader,
        IOutputWriter & writer) const;

}; // class StandardProcessor


} // namespace BracketPuzzle


#endif // BRACKETS_PUZZLE_STANDARD_PROCESSOR_HPP_2001410251753

/* EOF */
