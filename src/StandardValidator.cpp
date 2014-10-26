/**
    @file

    The standard string validator (implementation).

    @author Emil Maskovsky
*/

// standard library
#include <stack>
#include <memory>

// BracketPuzzle
#include "BracketPuzzle/StandardValidator.hpp"


namespace
{


class IState;

/** Pointer to state. */
typedef std::unique_ptr< IState > StatePtr;


/**
    Single state of the stack.

    This is used to implement the validator logic.
*/
class IState
{

public:

    /**
        Get next open state according to the character @p c.

        @param [in] c The next character.

        @return StatePtr
            The next open state according to the character @p c, if the
            character determines an open state and the transition is
            allowed, otherwise an empty (NULL) pointer.
    */
    virtual StatePtr next(char c) const = 0;

    /**
        Get next open state according to the character @p c.

        @param [in] c The next character.

        @return bool
            Returns @c true if the character @p c closes the current
            state, otherwise @c false.
    */
    virtual bool closing(char c) const = 0;

}; // class IState


/**
    The initial state of the stack.
*/
class InitialState
    : public IState
{

public:

    virtual StatePtr next(char c) const;
    virtual bool closing(char c) const;

}; // class InitialState


/**
    The open parenthesis state.
*/
class StateParen
    : public IState
{

public:

    /** The opening character. */
    static const char OPEN = '(';
    /** The closing character. */
    static const char CLOSE = ')';

    virtual StatePtr next(char c) const;
    virtual bool closing(char c) const;

}; // class StateParen


/**
    The open bracket state.
*/
class StateBracket
    : public IState
{

public:

    /** The opening character. */
    static const char OPEN = '[';
    /** The closing character. */
    static const char CLOSE = ']';

    virtual StatePtr next(char c) const;
    virtual bool closing(char c) const;

}; // class StateBracket


/**
    The open brace state.
*/
class StateBrace
    : public IState
{

public:

    /** The opening character. */
    static const char OPEN = '{';
    /** The closing character. */
    static const char CLOSE = '}';

    virtual StatePtr next(char c) const;
    virtual bool closing(char c) const;

}; // class StateBrace


#define STATE_RETURN_CASE(state) \
case state::OPEN:                \
    return StatePtr(new state)


StatePtr InitialState::next(char c) const
{
    switch (c)
    {
        STATE_RETURN_CASE(StateParen);
        STATE_RETURN_CASE(StateBracket);
        STATE_RETURN_CASE(StateBrace);
    }
    return StatePtr();
}


bool InitialState::closing(char) const
{
    // no closing brace in initial state
    return false;
}


StatePtr StateParen::next(char c) const
{
    switch (c)
    {
        STATE_RETURN_CASE(StateBrace);
    }
    return StatePtr();
}


bool StateParen::closing(char c) const
{
    return CLOSE == c;
}


StatePtr StateBracket::next(char c) const
{
    switch (c)
    {
        STATE_RETURN_CASE(StateParen);
        STATE_RETURN_CASE(StateBracket);
        STATE_RETURN_CASE(StateBrace);
    }
    return StatePtr();
}


bool StateBracket::closing(char c) const
{
    return CLOSE == c;
}


StatePtr StateBrace::next(char c) const
{
    switch (c)
    {
        STATE_RETURN_CASE(StateBracket);
    }
    return StatePtr();
}


bool StateBrace::closing(char c) const
{
    return CLOSE == c;
}


#undef STATE_RETURN_CASE


} // anonymous namespace


namespace BracketPuzzle
{


/* The IValidator interface */

bool StandardValidator::validate(
    const std::string & str) const
{
    if (str.empty())
    {
        return false;
    }
    if (str.size() % 2)
    {
        return false;
    }

    // start the stack with initial state
    std::stack< StatePtr > state;
    state.push(std::move(StatePtr(new InitialState)));

    for (std::string::const_iterator it = str.begin();
         it != str.end();
         ++it)
    {
        StatePtr next = state.top()->next(*it);
        if (next)
        {
            state.push(std::move(next));
        }
        else if (state.top()->closing(*it))
        {
            state.pop();
        }
        else
        {
            // invalid character
            return false;
        }
    }

    // the entire string is valid
    return true;
}


} // namespace BracketPuzzle


/* EOF */
