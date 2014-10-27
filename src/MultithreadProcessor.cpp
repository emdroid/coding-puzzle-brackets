/**
    @file

    The multi threaded string processor (implementation).

    @author Emil Maskovsky
*/

// standard library
#include <vector>
#include <sstream>

// BracketPuzzle
#include "BracketPuzzle/MultithreadProcessor.hpp"
#include "BracketPuzzle/IValidator.hpp"
#include "BracketPuzzle/IInputReader.hpp"
#include "BracketPuzzle/IResultWriter.hpp"
#include "BracketPuzzle/MultithreadResult.hpp"


namespace BracketPuzzle
{


bool MultithreadProcessor::execute(
    const IValidator & validator,
    const IInputReader & reader,
    IResultWriter & writer) const
{
    bool ok = true;
    std::string line;
    std::vector< std::string > lines;
    while (reader.readLine(line))
    {
        lines.push_back(line);
    }
    std::vector< std::string >::size_type iLine = 0;
    for (std::vector< std::string >::const_iterator it = lines.begin();
         it != lines.end() && ok;
         ++it, ++iLine)
    {
        ok = writer.writeResult(
            MultithreadResult(iLine, validator.validate(*it)));
    }
    return ok;
}


} // namespace BracketPuzzle


/* EOF */
