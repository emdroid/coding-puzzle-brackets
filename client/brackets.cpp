/**
    @file

    Brackets coding puzzle - Part 1 (single threaded processing).

    @author Emil Maskovsky
*/

// BracketPuzzle
#include "BracketPuzzle/ClientTemplate.hpp"
#include "BracketPuzzle/StandardProcessor.hpp"


int main()
{
    return BracketPuzzle::clientRun< BracketPuzzle::StandardProcessor >();
}


/* EOF */
