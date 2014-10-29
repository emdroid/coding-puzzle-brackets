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
#include <memory>

// Boost
#include <boost/exception/diagnostic_information.hpp>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE  Master
#include <boost/test/unit_test.hpp>

// BracketPuzzle
#include "BracketPuzzle/StandardProcessor.hpp"
#include "BracketPuzzle/MultithreadProcessor.hpp"
#include "BracketPuzzle/StandardValidator.hpp"
#include "BracketPuzzle/VectorInputReader.hpp"
#include "BracketPuzzle/VectorResultWriter.hpp"
#include "BracketPuzzle/StandardResult.hpp"
#include "BracketPuzzle/MultithreadResult.hpp"
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

    virtual void check(
        const std::vector< TaskSetup > & tasks,
        const VectorResultWriter::ValuesType & results) const = 0;

};


class StandardResultValidator
    : public IResultValidator
{

public:

    /* The IResultValidator interface */

    void check(
        const std::vector< TaskSetup > & tasks,
        const VectorResultWriter::ValuesType & results) const
    {
        for (size_t i = 0; i < tasks.size() && i < results.size(); ++i)
        {
            const StandardResult expected(tasks[i].second);
            BOOST_CHECK_MESSAGE(expected.isEqual(*results[i]),
                "input: \"" << tasks[i].first
                            << "\", expected: \"" << expected
                            << "\", received: \"" << *results[i] << "\"");
        }
        BOOST_CHECK_EQUAL(tasks.size(), results.size());
    }

};


class MultithreadResultValidator
    : public IResultValidator
{

public:

    /* The IResultValidator interface */

    void check(
        const std::vector< TaskSetup > & tasks,
        const VectorResultWriter::ValuesType & results) const
    {
        // need to sort the results first - can come out of order
        // from different threads
        VectorResultWriter::ValuesType sortedResults = results;
        std::sort(
            sortedResults.begin(),
            sortedResults.end(),
            ConstResultPtrLesserThan);
        for (size_t i = 0;
             i < tasks.size() && i < sortedResults.size();
             ++i)
        {
            const MultithreadResult expected(i, tasks[i].second);
            BOOST_CHECK_MESSAGE(expected.isEqual(*sortedResults[i]),
                "input: \"" << tasks[i].first
                            << "\", expected: \"" << expected
                            << "\", received: \"" << *sortedResults[i] << "\"");
        }
        BOOST_CHECK_EQUAL(tasks.size(), results.size());
    }

private:

    static bool ConstResultPtrLesserThan(ConstResultPtr left,
        ConstResultPtr right)
    {
        return *left < *right;
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

    void check(
        const VectorResultWriter & writer,
        const IResultValidator & resultValidator)
    {
        resultValidator.check(m_tasks, writer.getData());
    }

private:

    std::vector< TaskSetup > m_tasks;

}; // class ProcessingTestSetup


void testProcessing(
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
    VectorResultWriter writer;

    setup.configure(reader);
    processor.execute(validator, reader, writer);
    setup.check(writer, resultValidator);
}


}


BOOST_AUTO_TEST_SUITE(Processing)

BOOST_AUTO_TEST_CASE(SingleThreadedProcessing)
{
    testProcessing(
        StandardProcessor(),
        StandardResultValidator());
}

BOOST_AUTO_TEST_CASE(MultiThreadedProcessing)
{
    testProcessing(
        MultithreadProcessor(),
        MultithreadResultValidator());
}

BOOST_AUTO_TEST_SUITE_END()


/* EOF */
