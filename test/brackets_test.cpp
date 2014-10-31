/**
    @file

    Brackets coding puzzle unit tests.

    @author Emil Maskovsky
*/

// standard library
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <memory>

// Boost
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE  Master
#include <boost/test/unit_test.hpp>

// BracketPuzzle
#include "BracketPuzzle/StandardProcessor.hpp"
#include "BracketPuzzle/MultithreadProcessor.hpp"
#include "BracketPuzzle/StandardValidator.hpp"
#include "BracketPuzzle/StreamInputReader.hpp"
#include "BracketPuzzle/StreamResultWriter.hpp"
#include "BracketPuzzle/VectorInputReader.hpp"
#include "BracketPuzzle/VectorResultWriter.hpp"
#include "BracketPuzzle/StandardResult.hpp"
#include "BracketPuzzle/MultithreadResult.hpp"
using namespace BracketPuzzle;


BOOST_AUTO_TEST_SUITE(InputReader)


BOOST_AUTO_TEST_CASE(StreamInputReaderTest)
{
    std::istringstream input("Line1\nLine2\n");
    StreamInputReader reader(input);

    std::string line;

    // the first line
    BOOST_CHECK(reader.readLine(line));
    BOOST_CHECK_EQUAL(line, "Line1");
    // the second line
    BOOST_CHECK(reader.readLine(line));
    BOOST_CHECK_EQUAL(line, "Line2");
}


BOOST_AUTO_TEST_CASE(VectorInputReaderTest)
{
    VectorInputReader reader;
    reader.insert("Line1");
    reader.insert("Line2");

    std::string line;

    // the first line
    BOOST_CHECK(reader.readLine(line));
    BOOST_CHECK_EQUAL(line, "Line1");
    // the second line
    BOOST_CHECK(reader.readLine(line));
    BOOST_CHECK_EQUAL(line, "Line2");
}


BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(Result)


BOOST_AUTO_TEST_CASE(StandardResultTest)
{
    StandardResult result1(true);
    StandardResult result2(true);
    StandardResult result3(false);

    BOOST_CHECK(result1.isEqual(result2));
    BOOST_CHECK(result2.isEqual(result1));
    BOOST_CHECK(!result1.isEqual(result3));
    BOOST_CHECK(!result3.isEqual(result2));
    BOOST_CHECK(!result1.isLesserThan(result2));
    BOOST_CHECK(!result2.isLesserThan(result1));
    BOOST_CHECK(!result1.isLesserThan(result3));
    BOOST_CHECK(result3.isLesserThan(result1));
}


BOOST_AUTO_TEST_CASE(MultithreadResultTest)
{
    MultithreadResult result1(0, true);
    MultithreadResult result2(0, true);
    MultithreadResult result3(1, false);

    BOOST_CHECK(result1.isEqual(result2));
    BOOST_CHECK(result2.isEqual(result1));
    BOOST_CHECK(!result1.isEqual(result3));
    BOOST_CHECK(!result3.isEqual(result2));
    BOOST_CHECK(!result1.isLesserThan(result2));
    BOOST_CHECK(!result2.isLesserThan(result1));
    BOOST_CHECK(result1.isLesserThan(result3));
    BOOST_CHECK(!result3.isLesserThan(result1));
}


BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(ResultWriter)


BOOST_AUTO_TEST_CASE(StreamResultWriterTest)
{
    std::ostringstream out;
    StreamResultWriter writer(out);

    BOOST_CHECK(writer.writeResult(StandardResult(false)));
    BOOST_CHECK_EQUAL(out.str(), "False\n");
    BOOST_CHECK(writer.writeResult(StandardResult(true)));
    BOOST_CHECK_EQUAL(out.str(), "False\nTrue\n");
    BOOST_CHECK(writer.writeResult(MultithreadResult(5, true)));
    BOOST_CHECK_EQUAL(out.str(), "False\nTrue\n5:True\n");
}


BOOST_AUTO_TEST_CASE(VectorResultWriterTest)
{
    VectorResultWriter writer;

    BOOST_CHECK(writer.writeResult(StandardResult(true)));
    BOOST_CHECK_EQUAL(writer.getData().size(), 1u);
    BOOST_CHECK(writer.getData()[0]->isEqual(StandardResult(true)));

    BOOST_CHECK(writer.writeResult(StandardResult(false)));
    BOOST_CHECK_EQUAL(writer.getData().size(), 2u);
    BOOST_CHECK(writer.getData()[0]->isEqual(StandardResult(true)));
    BOOST_CHECK(writer.getData()[1]->isEqual(StandardResult(false)));

    BOOST_CHECK(writer.writeResult(MultithreadResult(8, false)));
    BOOST_CHECK_EQUAL(writer.getData().size(), 3u);
    BOOST_CHECK(writer.getData()[0]->isEqual(StandardResult(true)));
    BOOST_CHECK(writer.getData()[1]->isEqual(StandardResult(false)));
    BOOST_CHECK(writer.getData()[2]->isEqual(MultithreadResult(8, false)));
}


BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(Validator)


BOOST_AUTO_TEST_CASE(StandardValidatorTest)
{
    StandardValidator validator;

    BOOST_CHECK(!validator.validate(""));
    BOOST_CHECK(!validator.validate("a"));
    BOOST_CHECK(!validator.validate(""));
    BOOST_CHECK(!validator.validate("a"));
    BOOST_CHECK(!validator.validate(" "));
    BOOST_CHECK(!validator.validate("("));
    BOOST_CHECK(!validator.validate(")"));
    BOOST_CHECK(validator.validate("()"));
    BOOST_CHECK(!validator.validate("(()"));
    BOOST_CHECK(!validator.validate("()("));
    BOOST_CHECK(!validator.validate("())"));
    BOOST_CHECK(!validator.validate("( )"));
    BOOST_CHECK(!validator.validate("()_"));
    BOOST_CHECK(validator.validate("[]"));
    BOOST_CHECK(validator.validate("{}"));
    BOOST_CHECK(!validator.validate("({)}"));
    BOOST_CHECK(validator.validate("({})"));
    BOOST_CHECK(!validator.validate("([])"));
    BOOST_CHECK(!validator.validate("(())"));
    BOOST_CHECK(validator.validate("{[]}"));
    BOOST_CHECK(!validator.validate("{()}"));
    BOOST_CHECK(!validator.validate("{{}}"));
    BOOST_CHECK(validator.validate("[()]"));
    BOOST_CHECK(validator.validate("[{}]"));
    BOOST_CHECK(validator.validate("[[]]"));
    BOOST_CHECK(validator.validate("[[[]]]"));
    BOOST_CHECK(!validator.validate("[([])]"));
    BOOST_CHECK(validator.validate("[()()]"));
    BOOST_CHECK(validator.validate("{[][()()]}"));
    BOOST_CHECK(validator.validate("()()"));
}


BOOST_AUTO_TEST_SUITE_END()


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


BOOST_AUTO_TEST_CASE(StandardProcessorTest)
{
    testProcessing(
        StandardProcessor(),
        StandardResultValidator());
}


BOOST_AUTO_TEST_CASE(MultithreadProcessorTest)
{
    testProcessing(
        MultithreadProcessor(),
        MultithreadResultValidator());
}


BOOST_AUTO_TEST_SUITE_END()


/* EOF */
