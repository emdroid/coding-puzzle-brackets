/**
    @file

    The abstract result writer interface.

    @author Emil Maskovsky
*/


#ifndef BRACKETS_PUZZLE_I_RESULT_WRITER_HPP_2001410251817
#define BRACKETS_PUZZLE_I_RESULT_WRITER_HPP_2001410251817


namespace BracketPuzzle
{

// forward declarations
class IResult;


/**
    The abstract input reader interface.
*/
class IResultWriter
{

public:

    /**
        The destructor.
    */
    virtual ~IResultWriter()
    {
    }

    /**
        Write a result to the output.

        @param [in] result The result to be written.

        @return bool
            Returns @c true on success, @c false on failure.
    */
    virtual bool writeResult(
        const IResult & result) = 0;

}; // class IResultWriter


} // namespace BracketPuzzle


#endif // BRACKETS_PUZZLE_I_RESULT_WRITER_HPP_2001410251817

/* EOF */
