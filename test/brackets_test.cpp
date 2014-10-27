/**
    @file

    Brackets processor unit test test.

    @author Emil Maskovsky
*/

// standard library
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <sstream>

// BracketPuzzle
#include "BracketPuzzle/StandardProcessor.hpp"
#include "BracketPuzzle/MultithreadProcessor.hpp"
#include "BracketPuzzle/StandardValidator.hpp"
#include "BracketPuzzle/VectorInputReader.hpp"
#include "BracketPuzzle/VectorOutputWriter.hpp"
using namespace BracketPuzzle;


namespace
{


typedef std::pair< std::string, bool > TaskSetup;

class IResultValidator
{

public:

    virtual ~IResultValidator()
    {
    }

    virtual bool check(
        const std::vector< TaskSetup > & tasks,
        const std::vector< std::string > & results) const = 0;

};


class StandardResultValidator
    : public IResultValidator
{

public:

    /* The IResultValidator interface */

    bool check(
        const std::vector< TaskSetup > & tasks,
        const std::vector< std::string > & results) const
    {
        bool ok = true;
        for (size_t i = 0; i < tasks.size() && i < results.size(); ++i)
        {
            const std::string & expected
                = getResultString(tasks[i].second);
            if (expected != results[i])
            {
                std::cerr << "Test failure: Input: \""
                          << tasks[i].first
                          << "\", expected: \"" << expected
                          << "\", received: \"" << results[i] << "\""
                          << std::endl;
                ok = false;
            }
        }
        if (tasks.size() < results.size())
        {
            std::cerr << "Test failure: Extra data in the output" << std::endl;
            ok = false;
        }
        else if (tasks.size() > results.size())
        {
            std::cerr << "Test failure: Missing data in the output"
                      << std::endl;
            ok = false;
        }
        return ok;
    }

private:

    static std::string getResultString(const bool value)
    {
        return value ? "True" : "False";
    }

};


class MultithreadResultValidator
    : public IResultValidator
{

public:

    /* The IResultValidator interface */

    bool check(
        const std::vector< TaskSetup > & tasks,
        const std::vector< std::string > & results) const
    {
        bool ok = true;
        // need to sort the results first - can come out of order
        // from different threads
        std::vector< std::string > sortedResults = results;
        std::sort(sortedResults.begin(), sortedResults.end());
        for (size_t i = 0;
             i < tasks.size() && i < sortedResults.size();
             ++i)
        {
            const std::string & expected
                = getResultString(i, tasks[i].second);
            if (expected != sortedResults[i])
            {
                std::cerr << "Test failure: Input: \""
                          << tasks[i].first
                          << "\", expected: \"" << expected
                          << "\", received: \"" << sortedResults[i] << "\""
                          << std::endl;
                ok = false;
            }
        }
        if (tasks.size() < results.size())
        {
            std::cerr << "Test failure: Extra data in the output" << std::endl;
            ok = false;
        }
        else if (tasks.size() > results.size())
        {
            std::cerr << "Test failure: Missing data in the output"
                      << std::endl;
            ok = false;
        }
        return ok;
    }

private:

    static std::string getResultString(const size_t idx, const bool value)
    {
        std::ostringstream result;
        result << idx << ':' << (value ? "True" : "False");
        return result.str();
    }

};


class ProcessingTestSetup
{

public:

    void insert(const TaskSetup & task)
    {
        m_tasks.push_back(task);
    }

    void configure(VectorInputReader & reader)
    {
        for (std::vector< TaskSetup >::const_iterator
             it = m_tasks.begin();
             it != m_tasks.end();
             ++it)
        {
            reader.insert(it->first);
        }
    }

    bool check(
        const VectorOutputWriter & writer,
        const IResultValidator & resultValidator)
    {
        return resultValidator.check(m_tasks, writer.getData());
    }

private:

    std::vector< TaskSetup > m_tasks;

}; // class ProcessingTestSetup


bool testProcessing(
    const IProcessor & processor,
    const IResultValidator & resultValidator)
{
    ProcessingTestSetup setup;
    setup.insert(TaskSetup("", false));
    setup.insert(TaskSetup("a", false));
    setup.insert(TaskSetup(" ", false));
    setup.insert(TaskSetup("(", false));
    setup.insert(TaskSetup(")", false));
    setup.insert(TaskSetup("()", true));
    setup.insert(TaskSetup("(()", false));
    setup.insert(TaskSetup("()(", false));
    setup.insert(TaskSetup("())", false));
    setup.insert(TaskSetup("( )", false));
    setup.insert(TaskSetup("()_", false));
    setup.insert(TaskSetup("[]", true));
    setup.insert(TaskSetup("{}", true));
    setup.insert(TaskSetup("({)}", false));
    setup.insert(TaskSetup("({})", true));
    setup.insert(TaskSetup("([])", false));
    setup.insert(TaskSetup("(())", false));
    setup.insert(TaskSetup("{[]}", true));
    setup.insert(TaskSetup("{()}", false));
    setup.insert(TaskSetup("{{}}", false));
    setup.insert(TaskSetup("[()]", true));
    setup.insert(TaskSetup("[{}]", true));
    setup.insert(TaskSetup("[[]]", true));
    setup.insert(TaskSetup("[[[]]]", true));
    setup.insert(TaskSetup("[([])]", false));
    setup.insert(TaskSetup("[()()]", true));
    setup.insert(TaskSetup("{[][()()]}", true));
    setup.insert(TaskSetup("()()", true));

    StandardValidator validator;
    VectorInputReader reader;
    VectorOutputWriter writer;

    setup.configure(reader);
    processor.execute(validator, reader, writer);
    return setup.check(writer, resultValidator);
}


}


int main()
{
    int result = EXIT_SUCCESS;

    try
    {
        std::cout << "Running the [Bracket processor] unit test" << std::endl
                  << "=========================================" << std::endl;

        if (!testProcessing(
                StandardProcessor(),
                StandardResultValidator()))
        {
            result = EXIT_FAILURE;
        }

        if (!testProcessing(
                MultithreadProcessor(),
                MultithreadResultValidator()))
        {
            result = EXIT_FAILURE;
        }
    }
    catch (const std::exception & e)
    {
        std::cerr << std::endl
                  << "FAILURE: Exception caught!" << std::endl
                  << "Message: " << e.what() << std::endl;

        result = EXIT_FAILURE;
    }

    return result;
}


/* EOF */
