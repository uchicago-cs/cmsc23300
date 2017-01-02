===========
Style Guide
===========

    This document is based on the `CMSC 12100 Style Guide <https://www.classes.cs.uchicago.edu/archive/2015/fall/12100-1/style-guide/index.html>`_


Introduction
------------

This style guide is intended to provide some basic coding 
conventions for the CMSC 23300 projects. These conventions
are intended to improve the readability of your code. From
your perspective as a student, the readability of your code
is important for two big reasons:

#. If you have a problem with your code, or have trouble
   debugging a particular issue, it will be easier for us
   to provide assistance (and to provide it quickly) if your 
   code is easy to read. 
#. Writing readable code makes the lives of our graders easier.
   Remember: a happy grader is a generous grader. Additionally,
   graders *will* take points off for code that is hard to read
   (which includes, but is not limited to, code that doesn't
   follow the conventions in this style guide)

This document is not intended to be a comprehensive C style guide.
When you need guidance on a style issue not specified here,
we recommend using the `Linux Kernel Style Guide <https://www.kernel.org/doc/Documentation/CodingStyle>`_
(however, when that guide contradicts our guide, our guide will
be considered the normative document).

Code layout
------------

Indentation                                                              
^^^^^^^^^^^
        
You must follow one of the following two indent styles:

* `K&R style <https://en.wikipedia.org/wiki/Indent_style#K.26R_style>`_ (you can use any of the variants listed on that page, except BSD KNF), or
* `Allman style <https://en.wikipedia.org/wiki/Indent_style#Allman_style>`_

Make sure you choose one indent style and use it **consistently**. Please note that you can use `astyle <http://astyle.sourceforge.net/>`_ to take existing code and
convert it to one of the above indent styles::

    astyle --style=kr -r "*.c"
    astyle --style=allman -r "*.c"
                                                                  
Regardless of the descriptions of K&R and Allman you may find online, *you must use 4 spaces per indentation level*. This is the
indentation level used by default by astyle.
                                                                          
**Never use "tab characters".**

Note that you can configure most text editors to insert 4 spaces whenever you press the 
`tab key <https://en.wikipedia.org/wiki/Tab_key>`_. To check whether your editor is properly 
configured, try the following: press the tab key, and then press the left arrow key. If the
cursor jumps to the beginning of the line, your editor inserted a single "tab character". 
If the cursor only goes back one space (and you have to press the left arrow key three more 
times to get to the start of the line), then the editor is correctly inserting four spaces.

Whether to use `tabs or spaces <http://programmers.stackexchange.com/questions/57/tabs-versus-spaces-what-is-the-proper-indentation-character-for-everything-in-e>`_
is one of the many "religious wars" within the programming community.
So, you may run into people (even people here on campus) who will feel very strongly about
how tabs are better than spaces, and they may even present to you a number of cogent arguments
in favor of using tabs.

Do not listen to these people. They are wrong and cannot be trusted.

                                                                          
Maximum Line Length                                                      
^^^^^^^^^^^^^^^^^^^
                                                                          
Limit all lines to a maximum of 80 characters. This is not a hard limit,
and breaking it occasionally is fine, as long as you don't do it repeateadly
and always by a small number of additional characters. Also, remember that
most syntactical elements in C are delimited by whitespace, and that
newlines are considered whitespace. So, the following is correct C::

    if (VERY_VERY_VERY_VERY_VERY_VERY_VERY_VERY_VERY_VERY_LONG_CONDITION ||
        ANOTHER_VERY_VERY_VERY_VERY_VERY_VERY_VERY_VERY_VERY_VERY_LONG_CONDITION ||
        strlen(s) < 100)
    {
        /* ... */
    }
                                                                          
Blank Lines                                                              
^^^^^^^^^^^
                                                                          
Separate function definitions with two blank lines.
                                                                          
Extra blank lines may be used (sparingly) to separate groups of
related functions.
                                                                          
Use blank lines in functions, sparingly, to indicate logical sections.   

                                                                    
Whitespace in Expressions and Statements
----------------------------------------

Avoid extraneous whitespace in the following situations:                 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                                                                          
- Immediately inside parentheses:            

  ::

    Yes: chilog(INFO, "User %s has connected", user);
    No:  chilog( INFO, "User %s has connected", user );
                                                                          
- Immediately before a comma or a semicolon:               

  ::
                                                                          
    Yes: for (int i = 0; i < N; i++)
    No:  for (int i = 0 ; i < N ; i++)

  ::
                                                                          
    Yes: chilog(INFO, "User %s has connected", user);
    No:  chilog(INFO , "User %s has connected" , user);
                                                                          
- Immediately before the open parenthesis that starts the argument list of a function call:
                                                                          
  ::

    Yes: chilog(INFO, "User %s has connected", user);
    No:  chilog (INFO, "User %s has connected", user);
                                                                          
- Immediately before brackets indicating an array index:

  ::                                                                          

    Yes: a[N] = b[i]                                 
    No:  a [N] = b [i]
                                                                          
- More than one space around an assignment (or other) operator to align it with another.                                         
                                                                          
  Yes:

  ::

       x = 1;
       y = 2;
       long_variable = 3;
                                                                          
  No:

  ::

       x             = 1                                          
       y             = 2                                          
       long_variable = 3                                          
                                                                          

Places to use spaces                                                    
^^^^^^^^^^^^^^^^^^^^
                                                                          
- Always surround these binary operators with a single space on either side: assignment (=), augmented assignment (+=, -=, etc.), comparisons (==, <, >, !=, <>, <=, >=), Booleans (&&, ||). 

- Use a space after these keywords::

	if, switch, case, for, do, while
                                 
  Yes:

  ::

       if (x == 5)

  No:

  ::

       if(x == 5)                          
                                         
- Use spaces around arithmetic operators:                        

  Yes:                                                           

  ::

        i = i + 1                                                  
        submitted += 1                                             
        x = x * 2 - 1                                              
        hypot2 = x * x + y * y                                     
        c = (a + b) * (a - b)                                      
                                                                              
  No:                                                           

  ::

        i=i+1                                                      
        submitted +=1                                              
        x = x*2 - 1                                                
        hypot2 = x*x + y*y                                         
        c = (a+b) * (a-b)                                          
                                                                          
- Compound statements (multiple statements on the same line) are generally discouraged.                                         
                                                                          

  Yes:                                                           

  ::

        if (x == 0)
            do_blah_thing();
        do_one();
        do_two();                                                  
        do_three();
                                                                              
  Rather not:                                                    

  ::

        if (x == 0) do_blah_thing();
        do_one(); do_two(); do_three();
                                                                          

Comments
--------

Comments that contradict the code are worse than no comments. Always
make a priority of keeping the comments up-to-date when the code
changes!  Comments should consist of either a single short phrase or
one or more complete sentences. The first word of a comment should be
capitalized, unless it is an identifier that begins with a lower case
letter (never alter the case of identifiers!).
                                                                          
If a comment is short, the period at the end can be omitted. Block
comments generally consist of one or more paragraphs built out of
complete sentences, and each sentence should end in a period.
                                                                          
                                                                          
Header Comments                                                          
^^^^^^^^^^^^^^^
                                                                          
Header comments appear at the top of a file. These lines typically
include the filename, author, date, version number, and a description
of what the file is for and what it contains.
                                                                          
::                                                                       
                                                                          
    /*
     *  log.c: Logging functions
     *
     *  Use these functions to print log messages. Each message has an
     *  associated log level:
     *
     *  CRITICAL: A critical unrecoverable error
     *  ERROR: A recoverable error
     *  WARNING: A warning
     *  INFO: High-level information about the progress of the application
     *  DEBUG: Lower-level information
     *  TRACE: Very low-level information.
     *
     */
                                                                          

Function Comments                                                        
^^^^^^^^^^^^^^^^^
                                                                          
Function comments should be done in the form of a multiline comment
above the function header.

This comment must contain information specific to what a function does. 
It should also include a description of the purpose and expected
input arguments, the expected output values, and how error conditions
are handled.
                                                                         
Example:

::

    /*
     * chilog - Print a log message
     *
     * level: Logging level of the message
     *
     * fmt: printf-style formatting string
     *
     * ...: Extra parameters if needed by fmt
     *
     * Returns: nothing.
     */
    void chilog(loglevel_t level, char *fmt, ...);
                                                                          
                                                                          
Block Comments                                                           
^^^^^^^^^^^^^^
                                                                          
Block comments (``/* ... */``) generally apply to some (or all) code that follows
them, and are indented to the same level as that code. 
                                                                          
Inline Comments                                                          
^^^^^^^^^^^^^^^
                                                                          
Use inline comments sparingly.  An inline comment is a comment on the
same line as a statement. Inline comments should be separated by at
least two spaces from the statement.  They should start with a ``//`` and a
single space.
                                                                          
Inline comments are unnecessary and in fact distracting if they state
the obvious. Don't do this:
                                                                          
::                                                                       

   x = x + 1                 // Increment x                      
                                                                          
But sometimes, this style of comment is useful:                                           

::                                                                       
                                                                          
   x = x + 1                 // Compensate for border            
                                                                          


Naming Conventions
------------------

Variable and function names should use the `snake_case <https://en.wikipedia.org/wiki/Snake_case>`_
naming convention (i.e., ``lowercase_with_underscore``). For example:
                                                                          
::                                                                       
                                                                          
          sum_of_squares                                                    
          print_happy_birthday                                              
          total_apples                                                     
                                                                          
                                                                          
Constants names should use snake_case with all caps:

::

    PI
    MAX_CLIENTS
    MAX_IRC_MSG_LEN


Use descriptive names for parameter names, variables, and function
names.  Use short names for local
variables.  In general, the further away a variable will be used, the more
descriptive the name needs to be.

Printing logging / debug messages
---------------------------------

All the projects in this class use a simple logging library called ``chilog`` that is documented in each of the project specifications. You must use the ``chilog`` functions *exclusively* for printing logging or debug messages. **Do not use printf() directly in your code**. Please note that the ``chilog`` functions provide essentially the same functionality as ``printf``, so there is no situation where ``printf`` would be necessary instead of ``chilog`` (using ``chilog`` consistently also means you will not have to scrub ``printf``'s from your code before submitting it).

Furthermore, all the messages at the ``INFO``, ``WARNING``, ``ERROR``, and ``CRITICAL`` levels must be used only for their intended purposes (e.g., only use ``ERROR`` to print out actual errors in the execution of your program). You must use the ``DEBUG`` level only to print informative debug messages that would be understood by any developer trying to debug your code. You may use the ``TRACE`` level to print *any* debug message (including those that would only be understood by you). However, if your code is riddled with ``TRACE`` logging statements (including commented out ones) to the point where it is hard to read the code itself, we may take points off for this. So, once a ``TRACE`` logging statement has served its purpose, we suggest you remove it (not just comment it out).

You should assume that graders will run your code with logging at the ``INFO`` level, and will only use the ``DEBUG`` level if they need to debug an issue with your code. We will never run your code with logging at the ``TRACE`` level.

Please note that, in assignments where you are responsible for writing the ``main`` function, you may use ``fprintf`` to print to *standard error* if there is an error that prevents the program from starting (e.g., if a command-line parameter has not been provided, etc.)

Global variables
----------------

The use of global variables is forbidden in this class, except for defining compile-time *constants*. **There are no other exceptions**.

A compile-time constant is a global variable with a value that is known and set at compile-time and *never* changed during the runtime of the program (if the variable can be used to access other values, e.g., because it is a pointer, a ``struct``, etc., all the values reachable from the variable must also be known and set at compile-time). Such variables must have ``ALL_CAPS`` names, be declared as ``const`` and, if they are only going to be used in a single module, they must also be declared as ``static``. Please note that our definition excludes variables that are initialized when the program starts running, *even if the value of that variable won't change once it has been initialized*. If the value of the variable is not known before the program is running, it cannot be a global variable.

To be fair, there are a few, very limited cases where using a (non-constant) global variable is truly justified. However, *none of those cases apply to the code you must write in this class*. Please do not try to convince us to the contrary: we are steadfast in our opposition to using global variables in this class. 

When writing a function, you must make sure that all the data the function is going to operate on is passed to the function via its parameters, and that all data the functions produces is returned via its return value (or through an input/output parameter). If, instead, you write a function that uses a global variable to convey information to/from the function (except when using a compile-time constant), you can expect some pretty hefty point deductions.
  
For more details, see the Wikipedia entry on `Global Variables <https://en.wikipedia.org/wiki/Global_variable>`_, which also notes "They are usually considered bad practice".


``goto`` statements
-------------------

``goto`` statements can *only* be used to perform error handling. See this blog post for more details on how to do error handling with ``goto``'s in C: `Using goto for error handling in C <http://eli.thegreenplace.net/2009/04/27/using-goto-for-error-handling-in-c>`_. That post describes an additional acceptable use case for ``goto``'s (breaking out of deeply-nested loops) and, while we will technically accept that use of ``goto``'s as well, none of your code should require such a level of loop nesting (or, rather, if you find yourself needing to use a ``goto`` in this way, you should reconsider whether you need to re-design your code or break it up into more functions to avoid so many nested loops in the same function).


Avoid Magic Numbers
-------------------

Avoid sprinkling numbers that will have very little meaning to your
reader throughout your code. For example:

Yes:

::

    if (strlen(msg) > MAX_IRC_MSG_LEN)

No:

::

    if (strlen(msg) > 510)





