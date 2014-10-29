/**
    @file

    The multi threaded string processor (implementation).

    @author Emil Maskovsky
*/

// standard library
#include <vector>
#include <sstream>

// Boost
#include <boost/thread.hpp>
#include <boost/asio.hpp>

// BracketPuzzle
#include "BracketPuzzle/MultithreadProcessor.hpp"
#include "BracketPuzzle/IValidator.hpp"
#include "BracketPuzzle/IInputReader.hpp"
#include "BracketPuzzle/IResultWriter.hpp"
#include "BracketPuzzle/MultithreadTask.hpp"
#include "BracketPuzzle/MultithreadResult.hpp"


namespace BracketPuzzle
{


bool MultithreadProcessor::execute(
    const IValidator & validator,
    const IInputReader & reader,
    IResultWriter & writer) const
{
    bool ok = true;

    // read all the input lines
    std::string line;
    std::vector< std::string > lines;
    while (reader.readLine(line))
    {
        lines.push_back(line);
    }

    // thread pool
    boost::asio::io_service io_service;
    boost::thread_group threads;
    typedef std::unique_ptr< boost::asio::io_service::work > WorkerPtr;
    WorkerPtr worker
        = WorkerPtr(new boost::asio::io_service::work(io_service));

    // spawn the worker threads
    unsigned int countCores = boost::thread::hardware_concurrency();
    if (countCores == 0)
    {
        countCores = 1;
    }
    for (unsigned int i = 0; i < countCores; ++i)
    {
        threads.create_thread(boost::bind(&boost::asio::io_service::run,
                &io_service));
    }

    // post the tasks to the io_service
    std::vector< std::string >::size_type order = 0;
    for (std::vector< std::string >::const_iterator it = lines.begin();
         it != lines.end();
         ++it, ++order)
    {
        io_service.dispatch(std::move(
                // ok will be set to false if any task fails
                MultithreadTask(order, *it, validator, writer, ok)));
    }

    // wait for all the workers to terminate
    worker.reset();
    threads.join_all();
    io_service.stop();

    return ok;
}


} // namespace BracketPuzzle


/* EOF */
