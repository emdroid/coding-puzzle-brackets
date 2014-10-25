/**
    @file

    The abstract string processor interface.

    @author Emil Maskovsky
*/


#ifndef BRACKETS_PUZZLE_I_PROCESSOR_HPP_2001410251750
#define BRACKETS_PUZZLE_I_PROCESSOR_HPP_2001410251750


namespace BracketPuzzle
{

// forward declarations
class IInputReader;
class IOutputWriter;
class IValidator;


/**
    The abstract string processor interface.
*/
class IProcessor
{

public:

    /**
        The destructor.
    */
    virtual ~IProcessor()
    {
    }

    /**
        Execute the string processing.

        Reads all the strings using the input reader, validates them by
        the validator and writes out the results using the output
        writer.

        @param [in]  validator The string validator.
        @param [in]  reader    The input reader.
        @param [out] writer    The output writer.

        @return bool
            Returns @c true on success, @c false on failure.
    */
    virtual bool execute(
        const IValidator & validator,
        const IInputReader & reader,
        IOutputWriter & writer) const = 0;

}; // class IProcessor


} // namespace BracketPuzzle


#endif // BRACKETS_PUZZLE_I_PROCESSOR_HPP_2001410251750

/* EOF */
