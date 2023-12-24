Debugging techniques in cpp,
Felix Okoronkwo 10/19/23

 Debugging Techniques
=========================================================================
1) commenting out code
2) validating code flow
- Note:
  - when printing information for debugging case use `std::cerr` instead of `std::cout`
    because its unbuffered and it makes it clear that that your printing is error based

3) Printing values
4) conditionalizing debugging code
```cpp
  #include <iostream>
  #define DEBUG_MODE                // comment this line macro out to turn of debug mode

  int getInput()
  {
  #ifndef DEBUG_MODE
  std::cerr << "getInput Function entered" < "\n";
  #endif
    std::cout << "input your number" << "\n";
    int input{};
    std::cin >> input;
    return input;
  }

  int main()
  {
  #ifndef DEBUG_MODE
  std::cerr << "main Function entered" < "\n";
  #endif
    int result { getInput() };
    std::cout << "this is your input squared " < result * result < '\n';
    return 0;
  }
```

5) use a logger `plog`, `std::clog`, `spdlog` (for larger projects):
```cpp
  #include <plog/Log.h>                                       // place headers
  #include <plog/Initializers/RollinFileInitializer.h>
  #include <iostream>

  int getUserInput()
  {
    PLOGD << "getUserInput() Called";                         // log

    std::cout << "Input your number: " << "\n";
    int input{};
    std::cin >> input;

    return input;
  }

  int main()
  {
    plog::init(plog::debug, "LogFile.txt");                   // initialize logger

    PLOGD << "main function called";                          // log

    int result { getUserInput() };
    std::cout << "You Inputed: " << result << '\n';

    return 0;
  }
```

 Using an Integerated Debugger: Stepping
=========================================================================
A debugger is a computer program that allows a programmer control how another computer program
executes and examine it while the program is in its running state.

The debuggger helps to precisely control program execution and it allows to examine and modify the
programs state while running.

Stepping is the name of a related set of tools a debugger posses to allows us execute (step into)
code in a program statement by statement.

Note:
- while debuggging since `std::cout` is buffered you can add the below snippet at the top of your main
  function for automatic flushing of the `std::cout` for immediat print and flush
```cpp
  #ifdef DEBUG
  std::cout << std::unitbuf;          // enable automatic flushing for std::cout
  #endif
```

 Steppings
=========================================================================
Step into
-----------------------------------------------
This allows us to execute and examine an exacutable statement by statement with pause with every
statment to examine the current execution. if a function is called the step into command steps into
the function pointing out the line (in an IDE), pauses and gives detail on the execution going on there.

Step over
-----------------------------------------------
This allows you to go through program statement by statement but when encounters a function it executes
the function as a whole ans steps over to the next statement in the `main()`, its serves as a convinient
way to skip functions when your sure they are'nt the issue.

Step Out
-----------------------------------------------
it executes all remaining code in the function currently being executed, and then returns control to
you when the function has returned.

A step too far
-----------------------------------------------
If you step past your intended destination, the usual thing to do is stop debugging and restart debugging
again, being a little more careful not to pass your target this time.

Step back
-----------------------------------------------
The Goal of step beck is to rewind the program to its last step, sort of returning the porgram to a prior
state (reverse debugging).


 Using an Integerated Debugger: Running and breakpoints
=========================================================================
Run to cursor
-----------------------------------------------
This allows execution of a program until the statement youve selected eith yupur cursor,
it then returns control of the program to you at that point, for debugging.

Continue
-----------------------------------------------
Continue allows forward program execution continuation while in the middle of debugging session.
it continues the program as per normal, until it terminates or untill something

Start
-----------------------------------------------
The continue command has a twin brother named start. The start command performs the same action as
continue, just starting from the beginning of the program. It can only be invoked when not already in
a debug session.

Breakpoint
-----------------------------------------------
A breakpoint is a special marker that tells the debugger to stop execution of the program at the
breakpoint when running in debug mode.

Set Next Statement
-----------------------------------------------
The set next statement command allows us to change the point of execution to some other statement
(sometimes informally called jumping).
This can be used to jump the point of execution forwards and skip some code that would otherwise execute,
or backwards and have something that already executed run again.

 Using an integrated debugger: Watching variables
=========================================================================
nothing worth noting.

 Using an integrated debugger: The call stack
=========================================================================
A call stack is a stack of functions that has been called to get to the current point of execution.
the call stack window shows the curent call stack which, what functiosn are running and what stack theyll return to after
running.

when a function is executed it is placed at the top of the stack and the function and upon completion the stack is
is popped of the stack returning to the caller stack (the stack in which the prior running function was called from)

 Defensive programming
=========================================================================
This is a practice in which the developer anticipates all possible cirumstances in which the software could be
misused either by the end-users, developers or the programmer him/herself and plan to circumvent them.


