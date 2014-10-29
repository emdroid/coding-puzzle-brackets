/**
    @file

    The multi threaded task (implementation).

    @author Emil Maskovsky
*/

// BracketPuzzle
#include "BracketPuzzle/MultithreadTask.hpp"
#include "BracketPuzzle/MultithreadResult.hpp"


namespace BracketPuzzle
{


MultithreadTask::MultithreadTask(
    size_t order,
    const std::string & input,
    const IValidator & validator,
    IResultWriter & writer,
    bool & status)
    : m_order(order)
    , m_input(input)
    , m_validator(validator)
    , m_writer(writer)
    , m_status(status)
{
}


void MultithreadTask::operator ()()
{
    // calculate the result
    if (!m_writer.writeResult(
            MultithreadResult(m_order, m_validator.validate(m_input))))
    {
        // this should be thread-safe as long as the boolean is
        // initially set and we only unset (we should never set it
        // back to true)
        m_status = false;
    }
}


} // namespace BracketPuzzle


/* EOF */
