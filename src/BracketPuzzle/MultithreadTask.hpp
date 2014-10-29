/**
    @file

    The multi threaded task (interface).

    @author Emil Maskovsky
*/


#ifndef BRACKETS_PUZZLE_MULTITHREAD_TASK_HPP_2001410291347
#define BRACKETS_PUZZLE_MULTITHREAD_TASK_HPP_2001410291347

// standard library
#include <string>

// BracketPuzzle
#include "BracketPuzzle/NonAssignable.hpp"
#include "BracketPuzzle/IValidator.hpp"
#include "BracketPuzzle/IResultWriter.hpp"


namespace BracketPuzzle
{


/**
    The multi threaded task.
*/
class MultithreadTask
    : private NonAssignable
{

public:

    /**
        Constructor.

        @param [in]  order     The task order.
        @param [in]  input     The task input string.
        @param [in]  validator The string validator.
        @param [out] writer    The result writer.
        @param [out] status    The error status.
    */
    MultithreadTask(
        size_t order,
        const std::string & input,
        const IValidator & validator,
        IResultWriter & writer,
        bool & status);

    /**
        The call operator.

        Provides the body of the task.
    */
    void operator ()();

private:

    /** The task order. */
    size_t m_order;

    /** The task input string. */
    std::string m_input;

    /** The string validator. */
    const IValidator & m_validator;

    /** The result writer. */
    IResultWriter & m_writer;

    /** The error status. */
    bool & m_status;

}; // class MultithreadTask


} // namespace BracketPuzzle


#endif // BRACKETS_PUZZLE_MULTITHREAD_TASK_HPP_2001410291347

/* EOF */
