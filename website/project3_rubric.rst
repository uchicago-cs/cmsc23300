Project 3 Rubric
----------------

This project is worth 15% of your final grade. The grade for the project is 
divided into the following components:

- Completeness/Correctness (60 points)
- Design (20 points) 
- Style (20 points)

Completeness/Correctness
~~~~~~~~~~~~~~~~~~~~~~~~

This project does not have automated tests, but the graders will be running through the
commands described in the `Testing your Implementation <http://chi.cs.uchicago.edu/chirouter/testing.html>`_
page in the chirouter documentation. They will be looking specifically at the following:

* ARP - 20 points

  * Responding to ARP requests - 2 points
  * Sending ARP requests - 3 points
  * Processing ARP replies - 5 points
  * Managing Pending ARP Requests - 10 points

* ICMP - 15 points

  * Responding to Echo Requests - 5 points
  * Host Unreachable - 2 points
  * Time Exceeded - 5 points
  * Port Unreachable - 3 points

* IP Forwarding - 15 points

  * Basic Forwarding - 5 points
  * Sending withheld frames - 5 points
  * Host Unreachable - 5 points

* Multiple routers - 10 points

  * Two Router topology: 7.5 points
  * Three Router topology: 2.5 points
 
While the graders will be basing their score largely on whether your implementation
produces the expected results when running the commands listed on the chirouter
documentation, points may also be deducted for issues with your code that, while
not explicitly captured by the commands, could lead to *incorrect* behaviour in your router.


Design
~~~~~~

The Design component of the grade will be determined by "qualities, many of which are intangible, 
that don’t have to do with (and exist to some extent independently of) the correct operation of your code."
(thanks to Adam Shaw for this concise phrasing). We will specifically be looking at the following:

* **Function decomposition** (15 points): We will look at whether you divided your
  implementation into functions that make sense. This includes avoiding
  repeated/redundant code, ensuring that each function performs a well-defined
  task, and putting related functions in the same module (i.e., the same C file).
* **Efficiency** (5 points): We will look at whether your code is minimally efficient.
  In other words, we are not looking for sublimely efficient code but, rather,
  for the lack of grossly inefficient code. In this project, you should not need
  to add any additional data structures (lists, hash tables, etc.) to the existing code,
  but we will care about how you use the provided data structures. For example, if
  you iterate over a list in :math:`O(n^2)` time when the same task can reasonably be accomplished in
  :math:`O(n)` time (i.e., when the :math:`O(n)` is not particularly clever or relies
  on some obscure algorithm), we may deduct points for this.


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

.. include:: additional_penalties.txt




