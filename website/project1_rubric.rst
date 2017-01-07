Project 1 Rubric
----------------

This project is worth 20% of your final grade, and is divided into three parts:

* Project 1a (Assignment 1 in chirc). Worth 20% of the Project 1 grade.
* Project 1b (Assignment 2 in chirc). Worth 40% of the Project 1 grade.
* Project 1c (Assignment 3 in chirc). Worth 40% of the Project 1 grade.

The grade for each project is divided into the following components:

- Completeness (50 points)
- Design (30 points) 
- Style (20 points)

Completeness
~~~~~~~~~~~~

The Completeness component of the grade will be determined by the result of running
the tests and, more specifically, on the number of points obtained when
running ``make grade`` (see `Using the automated tests <http://chi.cs.uchicago.edu/chirc/testing.html#using-the-automated-tests>`_
in the chirc documentation and, specifically, the "Producing a grade report" section).

Design
~~~~~~

The Design component of the grade will be determined by "qualities, many of which are intangible, 
that don’t have to do with (and exist to some extent independently of) the correct operation of your code."
(thanks to Adam Shaw for this concise phrasing). Across all three
parts of the project, we will be looking at least at the following
(the exact points for each of the parts of the project is specified
later):

* **Module/function decomposition**: We will look at whether you divided your
  implementation into modules and functions that make sense. This includes avoiding
  repeated/redundant code, ensuring that each function performs a well-defined
  task, and putting related functions in the same module (i.e., the same C file).
* **Data structure design**: We will look at whether you have designed (and/or used)
  the right data structures to store your server's state.
* **Efficiency**: We will look at whether your code is minimally efficient.
  In other words, we are not looking for sublimely efficient code but, rather,
  for the lack of grossly inefficient code. For example, we don't care whether
  you store your list of channels in a linked list (:math:`O(n)` lookup times) or a
  hash table (:math:`O(1)` lookup times), but we do care whether you iterate over a list
  in :math:`O(n^2)` time when the same task can reasonably be accomplished in
  :math:`O(n)` time (i.e., when the :math:`O(n)` is not particularly clever or relies
  on some obscure algorithm).
  
In Project 1a, the the 30 points of the Design portion will be divided as follows:

* **Module/function decomposition** (15 points). Please note that, in this part of
  the project, it is acceptable to have all your code in a single C file (so you
  are not required to divide your implementation into multiple modules, but are
  welcome to do so). You will get at most 5 points here if your entire implementation
  is inside the main() function, without using any additional functions.
* **Data structure design** (10 points). We will specifically be looking at how you
  handle the reassembly of partitioned messages (and the data structures to support
  this).
* **Efficiency** (5 points)

In Projects 1b and 1c, the 30 points of the Design portion will be divided as follows:

* **Module/function decomposition** (9 points). Please note that, in this part of
  the project, you *must* divide your server into multiple modules.
* **Locking** (9 points): Your code must adequately protect any data that can
  be accessed concurrently by more than one thread. Using a Big Fat Lock (i.e.,
  using a single lock for your entire server) is an automatic zero here.
* **Data structure design** (9 points). We will specifically look at how you store
  information about the server state, including the list of users (and their state)
  and the list of channels (and their state).
* **Efficiency** (3 points)

Please note that we will discuss the module/function decomposition and 
the data structure design of Project 1b in the Week 2 discussion session,
and for Project 1c in Week 3.


Style
~~~~~

The Style component of the grade will be determined by your adherence to
our `Style Guide <style_guide.html>`_. While you should strive to follow this guide as
closely as possible, there *are* certain aspects we will be paying more
attention to. In all three parts of the project, the 20 points of the Style 
portion are divided as follows:

- **Documenting functions** (8 points): Every function written by you must have
  a `function comment <style_guide.html#function-comments>`_ with a brief description 
  of what the function does, and a description of the parameters and the 
  return value.
- **Consistent indentation** (2 points): Your code must follow one of the
  `allowed indentation styles <style_guide.html#function-comments>`_ consistently.
  The presence of even a single tab character in your code will result in 0 points
  here.
- **Clarity** (6 points): Your code must be easy to read and understand. This
  is a fairly subjective aspect, but common deductions for lack of clarity
  include using variables without descriptive names, writing convoluted code
  that would be easier to understand with more code comments, using magic
  numbers, etc.
- **General adherence to the style guide** (4 points): The graders will not be
  checking that you follow every minute aspect of our style guide, and occasional
  infractions are ok (and won't necessarily be penalized). What we're more
  concerned with is that your code, overall, has a *consistent* style that
  asymptotically approaches the one specified in our style guide.

Additionally, the graders will apply the following penalties:

- Using `global variables <style_guide.html#global-variables>`_: 10 point penalty
- Using `goto statements <style_guide.html#goto-statements>`_: 5 point penalty
- Using `printf instead of chilog <style_guide.html#printing-logging-debug-messages>`_: 5 point penalty

Please note that the style guide does specify a few exceptions when using
some of the above is acceptable. You will not be penalized in those cases.


Additional Penalties
~~~~~~~~~~~~~~~~~~~~

We will also apply the following penalties:

* **Submitting code that doesn't build**: If the graders are able to build your
  code with a few minor fixes (missing semicolons, parenthesis, etc.), 
  we will apply a 15 point penalty. If your code
  requires substantial work to get it to build, you will receive a zero on
  the assignment.

  **So, make sure you verify that the version of the code you submitted builds correctly on a CS machine**

* **Grossly incorrect memory management**: Up to 5 point penalty. You should make sure
  to free any memory you malloc, but we will usually not take points off unless you've
  been grossly negligent in your malloc'ing/freeing. You should also make sure to
  not "save" pointers to stack-allocated memory that is going to be deallocated.
  This can happen if you store a pointer to a functions' local variable in a struct
  that is heap-allocated.




