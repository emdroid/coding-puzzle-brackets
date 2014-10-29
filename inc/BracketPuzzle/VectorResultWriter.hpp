/**
    @file

    The vector result writer (interface).

    @author Emil Maskovsky
*/

#ifndef BRACKETS_PUZZLE_VECTOR_RESULT_WRITER_HPP_2001410261847
#define BRACKETS_PUZZLE_VECTOR_RESULT_WRITER_HPP_2001410261847

// standard library
#include <vector>
#include <mutex>

// BracketPuzzle
#include "BracketPuzzle/IResultWriter.hpp"
#include "BracketPuzzle/IResult.hpp"


namespace BracketPuzzle
{


class VectorResultWriter
    : public IResultWriter
{

public:

    typedef std::vector< ConstResultPtr > ValuesType;

    const ValuesType & getData() const;

    /* The IResultWriter interface */

    bool writeResult(
        const IResult & result);

private:

    /** The output data. */
    ValuesType m_data;

    /** Mutex lock of the data. */
    std::mutex m_lock;

}; // class VectorResultWriter


} // namespace BracketPuzzle


#endif // BRACKETS_PUZZLE_VECTOR_RESULT_WRITER_HPP_2001410261847

/* EOF */
