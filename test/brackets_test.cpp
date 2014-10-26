/**
    @file

    Brackets puzzle unit test suite.

    @author Emil Maskovsky
*/

// standard library
#include <cstdlib>
#include <iostream>

// BracketPuzzle
#include "BracketPuzzle/StandardProcessor.hpp"
#include "BracketPuzzle/StandardValidator.hpp"
#include "BracketPuzzle/VectorInputReader.hpp"
#include "BracketPuzzle/VectorOutputWriter.hpp"
using namespace BracketPuzzle;


namespace
{


typedef std::pair< std::string, std::string > TaskSetup;

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

    bool check(const VectorOutputWriter & writer)
    {
        bool ok = true;
        const std::vector< std::string > & data = writer.getData();
        for (size_t i = 0; i < m_tasks.size() && i < data.size(); ++i)
        {
            if (m_tasks[i].second != data[i])
            {
                std::cerr << "Test failure: Input: \""
                          << m_tasks[i].first
                          << "\", expected: \"" << m_tasks[i].second
                          << "\", received: \"" << data[i] << "\"" << std::endl;
                ok = false;
            }
        }
        if (m_tasks.size() < data.size())
        {
            std::cerr << "Test failure: Extra data in the output" << std::endl;
            ok = false;
        }
        else if (m_tasks.size() > data.size())
        {
            std::cerr << "Test failure: Missing data in the output"
                      << std::endl;
            ok = false;
        }
        return ok;
    }

private:

    std::vector< TaskSetup > m_tasks;

}; // class ProcessingTestSetup


bool testProcessing(const IProcessor & processor)
{
    ProcessingTestSetup setup;
    setup.insert(TaskSetup("", "False"));
    setup.insert(TaskSetup("a", "False"));
    setup.insert(TaskSetup(" ", "False"));
    setup.insert(TaskSetup("(", "False"));
    setup.insert(TaskSetup(")", "False"));
    setup.insert(TaskSetup("()", "True"));
    setup.insert(TaskSetup("(()", "False"));
    setup.insert(TaskSetup("()(", "False"));
    setup.insert(TaskSetup("())", "False"));
    setup.insert(TaskSetup("( )", "False"));
    setup.insert(TaskSetup("()_", "False"));
    setup.insert(TaskSetup("[]", "True"));
    setup.insert(TaskSetup("{}", "True"));
    setup.insert(TaskSetup("({)}", "False"));
    setup.insert(TaskSetup("({})", "True"));
    setup.insert(TaskSetup("([])", "False"));
    setup.insert(TaskSetup("(())", "False"));
    setup.insert(TaskSetup("{[]}", "True"));
    setup.insert(TaskSetup("{()}", "False"));
    setup.insert(TaskSetup("{{}}", "False"));
    setup.insert(TaskSetup("[()]", "True"));
    setup.insert(TaskSetup("[{}]", "True"));
    setup.insert(TaskSetup("[[]]", "True"));
    setup.insert(TaskSetup("[[[]]]", "True"));
    setup.insert(TaskSetup("[([])]", "False"));
    setup.insert(TaskSetup("[()()]", "True"));
    setup.insert(TaskSetup("{[][()()]}", "True"));
    setup.insert(TaskSetup("()()", "True"));

    StandardValidator validator;
    VectorInputReader reader;
    VectorOutputWriter writer;

    setup.configure(reader);
    processor.execute(validator, reader, writer);
    return setup.check(writer);
}


}


int main()
{
    int result = EXIT_SUCCESS;

    try
    {
        std::cout << "Running the [Bracket processor] unit test" << std::endl
                  << "=========================================" << std::endl;

        if (!testProcessing(StandardProcessor()))
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
