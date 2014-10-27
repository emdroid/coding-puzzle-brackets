/**
    @file

    The multi threaded string processor (interface).

    @author Emil Maskovsky
*/


#ifndef BRACKETS_PUZZLE_MULTITHREAD_PROCESSOR_HPP_2001410271034
#define BRACKETS_PUZZLE_MULTITHREAD_PROCESSOR_HPP_2001410271034

// BracketPuzzle
#include "BracketPuzzle/IProcessor.hpp"


namespace BracketPuzzle
{


/**
    The multi threaded string processor.
*/
class MultithreadProcessor
    : public IProcessor
{

public:

    /* The IProcessor interface */

    bool execute(
        const IValidator & validator,
        const IInputReader & reader,
        IResultWriter & writer) const;

}; // class MultithreadProcessor


} // namespace BracketPuzzle


#endif // BRACKETS_PUZZLE_MULTITHREAD_PROCESSOR_HPP_2001410271034

/* EOF */
