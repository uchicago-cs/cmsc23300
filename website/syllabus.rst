Syllabus
--------

Course description
~~~~~~~~~~~~~~~~~~

.. include:: description.txt

Course organization
~~~~~~~~~~~~~~~~~~~

The development of three programming projects accounts for the majority
of the grade in this course. To successfully complete these projects,
students must master fundamental concepts and skills in networking. The
class meets two times a week for lectures that provide a conceptual
scaffolding for the projects, but will also cover material that is not
directly applied in the projects. There is also an optional weekly
discussion session primarily intended for in-depth discussion of the
projects. Besides the projects, students will also be evaluated with a
midterm and a final exam. The course calendar, including the contents of
each lecture and project deadlines, is shown in the `Course Calendar <calendar.html>`_ page.

Projects
~~~~~~~~

Throughout the quarter, students will develop three projects:

#. **chirc**: Implementing an Internet Relay Protocol (IRC)
   server (partially compliant with RFC 2810, 2811, 2812, and 2813)
   using POSIX sockets and pthreads.

#. **chiTCP**: Implementing the Transmission Control Protocol.

#. **chirouter**: Implementing an Internet router using the `Mininet network emulator <https://github.com/mininet/mininet>`_

Each project is independent from the others. Students registered under the
undergraduate code (CMSC 23300) will develop these projects in pairs. Project 
groups must be formed by Friday of the first week of the quarter.
Groups can be changed from one project to another. If your partner drops out of
the course or you feel he/she is not contributing to the group’s effort,
you should make the instructor aware of this.

Students registered for the graduate code (CMSC 33300) will develop these projects individually.

Discussion Session
~~~~~~~~~~~~~~~~~~

The course includes an optional discussion session which will focus
primarily on the projects. During these discussion sessions, we will (1)
provide suggestions on how to approach the projects, (2) provide general
feedback on submitted projects, and (3) provide a general forum to
answer questions about the projects. For avoidance of doubt, the
discussion sessions are not intended to provide individual feedback or
help on the projects; please use Piazza and office hours for that
purpose.

Even though these discussion sessions are optional and have no direct
impact on your grade, we encourage you to attend them, as they will
provide you with very valuable pointers on how to do the projects. At
the very least, one of the two members in each group should plan to
attend the discussion session each week.

Please note that the first two discussion sessions will be used to
provide a refresher on socket programming and concurrent programming,
respectively. Students who did not take CMSC 15400 in the previous
school year, or who are not comfortable working with sockets or threads
in C, are *strongly* encouraged to attend these first two discussion
sessions.

Exams
-----

There will be an in-class midterm half-way through the quarter,
and a final exam will take place during Finals Week. An early final 
exam will be scheduled during 10th week for graduating students. Please
see the `Course Calendar <calendar.html>`_ page for the exact dates.

Questions and exercises related to the projects will make up a
substantial part of both exams. Students who have worked on the projects
(which requires understanding the material presented in class) should be
able to answer these questions with relative ease. However, the exams
will also include questions that are not related to the projects, but
will be in line with the learning goals outlined at the beginning of
this syllabus.

Books
~~~~~

This course has two *suggested* texts:

-  *Computer Networks: A Systems Approach*, 5th edition, Larry L.
   Peterson and Bruce S. Davie, Morgan Kaufmann 2012.

-  *TCP/IP Illustrated, Volume 1: The Protocols*, 2nd Edition, Kevin
   Fall and W. Richard Stevens, Addison-Wesley 2011.

Both are available for purchase from the Seminary Co-op Bookstore. These
texts are *not* required, and most students are able to complete the
class successfully without them. However, they can be a good complement
to the lectures and projects.

Grading
~~~~~~~

For undergraduates, the final grade will be based on the following:

- Project 1: 20%
- Project 2: 25%
- Project 3: 15%
- Midterm: 15%
- Final: 25%

Grades are not curved in this class or, at least, not in the traditional
sense. We use a standard set of grade boundaries:

-  95-100: A
-  90-95: A-
-  85-90: B+
-  80-85: B
-  75-80: B-
-  70-75: C+
-  < 70: Dealt on a case-by-case basis

We curve only to the extent that we may (and often do) *lower* the
boundaries for one or more letter grades, depending on the distribution
of the raw scores. We will never raise the boundaries in response to the
distribution.

Before the end of the quarter, we will provide students with an
estimated grade based on all the work they have done up to that point,
including a preliminary and non-binding list of grade boundaries.

Types of grades
~~~~~~~~~~~~~~~

Students may take this course for a quality grade (a "letter" grade) or
a pass/fail grade. By default, we assume students are taking the class
for a quality grade. We will honor all requests to withdraw or take the
class pass/fail *before* the final exam.

Note: *Students taking this course to meet general education
requirements must take the course for a letter grade*.

Late submissions
~~~~~~~~~~~~~~~~

If you work on the projects with the same partner throughout the quarter,
then the late submission policy is simple: you have four 24-hour extensions 
to use at your discretion on any of the projects. Take into account that:

- Extensions are all-or-nothing: if you use an extension, you get an indivisible
  24-hour extension. You cannot use a portion of an extension 
  and have the rest “carry over” to another extension.
- More than one extension can be applied to a single submission. 
  e.g., a single 24-hour extension on four submissions, or a 96-hour 
  extension on a single submission.
- You do not need to ask permission to use an extension. Extensions are
  handled automatically by the project submission system we use.
- Extensions cannot be transferred, sold, or exchanged for points.

If extraordinary circumstances (illness, family emergency, etc.) prevent
a student from meeting a deadline, the student must inform the
instructor *before* the deadline. Requests for extraordinary extensions
after a project deadline will not be considered.

If you work with different partners throughout the quarter, the late submission
policy is slightly more complicated. Each individual student has four extensions,
and using an extension as a pair consumes one extension from each student (so,
if you have the same partner throughout the quarter then you have, as a pair, four extensions
as well). However, if you use one extension with one partner, and then form a different group
with someone who has used two extensions already, then you will only be able to
use two extensions as a pair.


Policy on academic honesty
~~~~~~~~~~~~~~~~~~~~~~~~~~

The University of Chicago has a `formal policy on academic honesty <http://college.uchicago.edu/advising/academic-integrity-student-conduct>`_
that you are expected to adhere to.

In brief, academic dishonesty (handing in someone else’s work as your
own, taking existing code and not citing its origin, etc.) will *not* be
tolerated in this course. Depending on the severity of the offense, you
risk getting a hefty point penalty or being dismissed altogether from
the course. All occurrences of academic dishonesty will furthermore be
referred to the Dean of Students office, which may impose further
penalties, including suspension and expulsion.

Even so, discussing the concepts necessary to complete the projects is
certainly allowed (and encouraged). Under *no circumstances* should you
show (or email) another student your code or post your solution to a
web-page or social media site. If you have discussed parts of an
assignment with someone else, then make sure to say so in your
submission (e.g., in a README file or as a comment at the top of your
source code file). If you consulted other sources, please make sure you
cite these sources.

Furthermore, the use of external libraries is generally allowed on all
the projects, as long as they don't provide networks-related functionality 
that you're expected to implement. In particular, the following libraries
have been used by students in the past and can be considered safe to incorporate
into your code:

- `simclist <http://mij.oltrelinux.com/devel/simclist/>`_: A C library for Lists
- `bstring <http://bstring.sourceforge.net/>`_: The Better String Library
- `uthash <https://troydhanson.github.io/uthash/>`_: A hash table for C structures

Finally, if you have any questions regarding what would or would not be
considered academic dishonesty in this course, please don’t hesitate to
ask the instructor.

Asking questions
~~~~~~~~~~~~~~~~

The preferred form of support for this course is through *Piazza*
(http://www.piazza.com/), an on-line discussion service which can be
used to ask questions and share useful information with your classmates.
Students will be enrolled in Piazza at the start of the quarter.

All questions regarding assignments or material covered in class must be
sent to Piazza, and not directly to the instructors or TAs, as this
allows your classmates to join in the discussion and benefit from the
replies to your question. If you send a message directly to the
instructor or the TAs, you will get a gentle reminder that your question
should be asked on Piazza.

Piazza has a mechanism that allows you to ask a private question, which
will be seen only by the instructors and teaching assistants. This
mechanism should be used *only* for questions that require revealing
part of your solution to a project.

Piazza also allows students to post anonymously. *Anonymous posts will
be ignored* (you will also get a gentle reminder asking you to not post
anonymously). This is a majors-level course: you are expected to feel
comfortable sharing your questions and thoughts with your classmates
without hiding behind a veil of anonymity.

Additionally, all course announcements will be made through Piazza. It
is your responsibility to check Piazza often to see if there are any
announcements. Please note that you can configure your Piazza account to
send you e-mail notifications every time there is a new post on Piazza.
Just go to your Account Settings, then to Class Settings, click on "Edit
Notifications" under CMSC 23300. We encourage you to select either the
"Real Time" option (get a notification as soon as there are new posts)
or the "Smart Digest" option (get a summary of all the posts sent over
the last 1-6 hours – you can select the frequency).

Acknowledgements
~~~~~~~~~~~~~~~~

This syllabus is based on previous CMSC 23300/33300 syllabi developed by
Prof. Anne Rogers and Prof. Ian Foster from the University of Chicago.
