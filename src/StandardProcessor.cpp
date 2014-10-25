/**
    @file

    The standard string processor (implementation).

    @author Emil Maskovsky
*/

// BracketPuzzle
#include "BracketPuzzle/StandardProcessor.hpp"
#include "BracketPuzzle/IValidator.hpp"
#include "BracketPuzzle/IInputReader.hpp"
#include "BracketPuzzle/IOutputWriter.hpp"


namespace BracketPuzzle
{


bool StandardProcessor::execute(
    const IValidator & validator,
    const IInputReader & reader,
    IOutputWriter & writer) const
{
    bool ok = true;
    std::string line;
    while (ok && reader.readLine(line))
    {
        ok = writer.writeLine(
            validator.validate(line)
            ? "True"
            : "False");
    }
    return ok;
}


} // namespace BracketPuzzle


/* EOF */
