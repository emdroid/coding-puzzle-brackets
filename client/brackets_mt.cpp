/**
    @file

    Brackets coding puzzle - Part 2 (multi threaded processing).

    @author Emil Maskovsky
*/

// BracketPuzzle
#include "BracketPuzzle/ClientTemplate.hpp"
#include "BracketPuzzle/MultithreadProcessor.hpp"


int main()
{
    return BracketPuzzle::clientRun< BracketPuzzle::MultithreadProcessor >();
}


/* EOF */
