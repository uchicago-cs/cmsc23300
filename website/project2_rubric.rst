Project 2 Rubric
----------------

This project is worth 25% of your final grade, and is divided into three parts:

* Project 2a (Assignment 1 in chiTCP). Worth 60% of the Project 2 grade.
* Project 2b (Assignment 2 in chiTCP). Worth 40% of the Project 2 grade.

The grade for each project is divided into the following components:

- Completeness (50 points)
- Correctness (10 points)
- Design (20 points) 
- Style (20 points)

Completeness
~~~~~~~~~~~~

The Completeness component of the grade will be determined by the result of running
the tests and, more specifically, on the number of points obtained when
running ``make grade`` (see `Automated tests <http://chi.cs.uchicago.edu/chitcp/testing.html#automated-tests>`_
in the chiTCP documentation and, specifically, the "Producing a grade report" section).

Correctness
~~~~~~~~~~~

The Correctness component of the grade encompasses issues with your code that, while
not explicitly captured by the tests, could lead to *incorrect* behaviour in your server.
Unlike Project 1, there are many aspects of the implementation that are hard to
check via the automated tests, so a perfect score on the tests is no guarantee
that you'll also get a high score in this section.

Most penalties in this section are usually because something was implemented
by rote. For example, it is easy to pass the three-way handshake
by making TCP go into an ESTABLISHED state after receiving two packets (without checking
whether the first one is a SYN packet, and whether the second one contains a valid ACK).
In general, making assumptions about the packets you will receive, instead of performing
the checks that are clearly specified in RFC 793, will result in penalties.

The graders may also take points off for not implementing something that is clearly specified
in the project or in RFC 793, even if the tests don't test for it (e.g., not setting all the
values in the TCP header, even if they're not relevant for a specific test; a common
pitfall is to forget to set/update the window-related fields/variables). In Project 2b 
we will be paying special attention to your RTT estimation code, which is 
difficult to test automatically.

Finally, please note that this section of the rubric will not re-penalize you for a failure
that is already captured by the tests. So, if your code fails to implement something
we told you to implement, but that is already captured by the tests, we would not
re-penalize you here.

Design
~~~~~~

The Design component of the grade will be determined by "qualities, many of which are intangible, 
that don’t have to do with (and exist to some extent independently of) the correct operation of your code."
(thanks to Adam Shaw for this concise phrasing). Across both
parts of the project, we will be looking at the following
(the exact points for each of the parts of the project is specified
later):

* **Function decomposition** : We will look at whether you divided your
  implementation into functions that make sense. This includes avoiding
  repeated/redundant code, ensuring that each function performs a well-defined
  task, and putting related functions in the same module (i.e., the same C file).

  Please note that, unlike Project 1, all you work will be constrained to a
  single C file: ``tcp.c`` (and its header file ``tcp.h``). **Do not create 
  additional C files or header files, and do not modify any other files in the project**
* **Data structure design** (Project 2b only): We will look at whether you have designed 
  (and/or used) the right data structures to manage retransmissions and out-of-order delivery.
* **Efficiency**: We will look at whether your code is minimally efficient.
  In other words, we are not looking for sublimely efficient code but, rather,
  for the lack of grossly inefficient code. For example, we don't care whether
  you store your list of channels in a linked list (:math:`O(n)` lookup times) or a
  hash table (:math:`O(1)` lookup times), but we do care whether you iterate over a list
  in :math:`O(n^2)` time when the same task can reasonably be accomplished in
  :math:`O(n)` time (i.e., when the :math:`O(n)` is not particularly clever or relies
  on some obscure algorithm).
  
In Project 2a, we will be looking at the following:

* **Function decomposition** (15 points). We strongly encourage you to write a 
  `packet arrival handler <project2_tips.html#writing-the-packet-arrival-handler>`_.
  While it is not strictly required, it should make your life much easier. Please
  note that the packet arrival handler will probably be a very long function; we will
  not deduct points for this, as long as you clearly document how each part of the
  function corresponds to what is specified in pages 64-75 of RFC 793.

  However, we *will* deduct points if your packet arrival handler unnecessarily repeats
  code (e.g., the code to construct and send a packet).
* **Efficiency** (5 points)

In Project 2b, we will be looking at the following:

* **Function decomposition** (8 points). In particular, the code for handling timeouts,
  retransmissions, and out-of-order delivery should be written in their own functions.
  A good design would be one where your p2a code only requires adding a few calls to
  these new functions, instead of a complete overhaul of your code.
* **Data structure design** (8 points). We will specifically look at how you keep track
  of retranmissions and out-of-order packets.
* **Efficiency** (4 points)


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

Please note that, as mentioned in the Design section, we will *not* deduct points
if your packet arrival handler is a very long function (as long as you clearly 
document how each part of the function corresponds to what is specified in pages 
64-75 of RFC 793). We may still take points off if *other* functions you write are
too long and difficult to follow.

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

  **So, make sure you verify that the version of the code you submitted builds correctly on a supported
  software environment** (see the `Projects <projects.html>`_ page for more details on this)

* **Grossly incorrect memory management**: Up to 5 point penalty. You should make sure
  to free any memory you malloc, but we will usually not take points off unless you've
  been grossly negligent in your malloc'ing/freeing. You should also make sure to
  not "save" pointers to stack-allocated memory that is going to be deallocated.
  This can happen if you store a pointer to a functions' local variable in a struct
  that is heap-allocated.




