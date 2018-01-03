Submitting a project
--------------------

Preliminaries
~~~~~~~~~~~~~

* Submissions are made using the ``chisubmit`` tool. Make sure you run these commands from your chisubmit directory
  (the one you initialized with ``chisubmit init`` as described in `Registering for the projects <registering.html>`_).
* Before making a submission, make sure you have pushed your code to the GitLab server. If your code hasn't been pushed to GitLab, then ``chisubmit`` will not see it.


Making the submission
~~~~~~~~~~~~~~~~~~~~~

To submit a project, simply run the following **BEFORE THE DEADLINE**::

    chisubmit student assignment submit <assignment-id>

Where ``<assignment-id>`` is the project identifier. Your instructor will tell you what identifier to use, but you can also see the list of possible assignment ids by running ``chisubmit student assignment list``.

By default, chisubmit will create a submission using the latest commit in your repository. You should see something like this::

    SUBMISSION FOR ASSIGNMENT p1a (chirc: Part 1)
    ---------------------------------------------

    This is a TEAM submission for team amr-borja with the following students:
     - Anne Rogers
     - Borja Sotomayor

    The latest commit in your repository is the following:

          Commit: c53b947521b3d741ee8c5562e4552e3bc06ddc6e
            Date: 2017-01-09 18:05:04
         Message: p1a done!
          Author: Borja Sotomayor <borja@cs.uchicago.edu>

    PLEASE VERIFY THIS IS THE EXACT COMMIT YOU WANT TO SUBMIT

    Your team currently has 4 extensions

    You are going to use 0 extensions on this submission.

    You will have 4 extensions left after this submission.

    Are you sure you want to continue? (y/n):

.. warning::

   At this point, a lot of student just press "y" without reading the message printed by chisubmit. **It is your responsibility to ensure that the commit shown by chisubmit is the one you actually want to submit**. By pressing "y", you are agreeing to have your code graded at the specified commit. If you submit the wrong version of your code, we will not accept "I thought I was submitting a different version" as an excuse. Please note that we also provide below several ways to double/triple/quadruple check that your submission was made correctly.

   Please note that a common pitfall is to make all your final changes locally, but then forgetting to push to your repository (or encountering an issue when pushing, such as a merge conflict). chisubmit can only see commits that you have successfully pushed to the GitLab server so, if the commit message and date shown by chisubmit don't look right, then you should double-check whether you were able to successfully commit and push your code

After you type ``y``, you should see the following message::

    Your submission has been completed.

If you want to submit an earlier commit, use the ``--commit-sha`` option when running chisubmit::

    chisubmit student assignment submit p1a --commit-sha 2e5969ce281b88bcb3743dc81539623124e63f41


Verifying that your submission was made correctly
-------------------------------------------------

If you see ``Your submission has been completed``, that means you are all set. If you want to be extra sure, the following command will show you the assignments you are registered for, and their submission status::
 
    chisubmit student team show TEAMNAME

(where ``TEAMNAME`` should be replaced by your team name)

If you have not submitted an assignment, you will see something like this::
 
    ASSIGNMENTS
    -----------
    ID: p1a
    Name: chirc: Part 1
    Deadline: 2017-01-09 20:00:00-06:00
    NOT SUBMITTED
 
If you have submitted the assignment correctly, you will see something like this::
 
    ASSIGNMENTS
    -----------
    ID: p1a
    Name: chirc: Part 1
    Deadline: 2017-01-09 20:00:00-06:00
    Last submitted at: 2017-01-09 18:11:47-06:00
    Commit SHA: 2e5969ce281b88bcb3743dc81539623124e63f41
    Extensions used: 0

If you want to be super extra double sure, you can log into the GitLab server (`https://mit.cs.uchicago.edu <https://mit.cs.uchicago.edu>`_), then click on your repository on the right side of the page, then click on "Commits" on the left side of the page. You will see the list of commits that are on the server (this is what the graders will see). On the right side of the page, you will see the first eight characters of each commit's SHA; find the one that was shown by ``chisubmit student team show`` command, and verify that it is, indeed the version of the code that you want the graders to grade. To do this, simply click on "Browse files" to see the state of the repository at that commit

Please note that, if you click on the commit itself (either the title or the identifier), you will see the changes that were included just in that commit. *Don't be alarmed if you don't see all your files in your last commit!* A Git commit only stores the information of what changed in your repository since the previous commit; to see the complete state of your repository (up to and including a given commit), just click on "Browse files" for that commit in the list of commits. 

Re-submitting
-------------

Re-submitting is possible, but can sometimes be tricky because, in some cases, the graders may have already
started grading your previous submission! So, if you think you may want to resubmit an assignment,
you have to remember this important rule:

   **If the deadline for an assignment passes, and you have made a submission
   for that assignment before the deadline, the graders will be able to start grading it!**
   
What happens internally is that, once the deadline passes, chisubmit looks at all the submissions
that have been already made and flags them as "ready for grading". So, when a grader checks
whether there is any grading assigned to them, your submission will show up on their end.
   
Don't worry: if you have extensions to use, there are ways of ensuring that you can re-submit even 
after the deadline passes, but it requires being careful about what steps you take to do so.
If you find yourself in that situation, make sure you read the following sections *very carefully*.

For now, let's assume the simplest (and most common) scenario: resubmitting when you have
no intention of using any extensions. In this case, things become very simple:
you can resubmit as many times as you want *before the deadline*. Then, once the deadline
passes, your last submission before the deadline will be the one that the graders will see.

To re-submit before the deadline, just run the submission command like before::

    chisubmit student assignment submit p1a

chisubmit will know that you already made a submission, and will ask you to confirm that you want to create a new submission::

    SUBMISSION FOR ASSIGNMENT p1a (chirc: Part 1)
    ---------------------------------------------

    This is a TEAM submission for team amr-borja with the following students:
     - Anne Rogers
     - Borja Sotomayor

    You have already submitted assignment p1a

    You submitted the following commit on 2017-01-09 18:11:47-06:00:

          Commit: c53b947521b3d741ee8c5562e4552e3bc06ddc6e
            Date: 2017-01-09 18:05:04
         Message: p1a done!
          Author: Borja Sotomayor <borja@cs.uchicago.edu>

    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    IF YOU CONTINUE, THE ABOVE SUBMISSION FOR p1a (chirc: Part 1) WILL BE CANCELLED.
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    If you continue, your submission will instead point to the following commit:

          Commit: 5b485c80fad76d02df675044b6b4c6c0d32b4ae8
            Date: 2017-01-09 19:17:56
         Message: p1a done! For real! This time!
          Author: Borja Sotomayor <borja@cs.uchicago.edu>

    PLEASE VERIFY THIS IS THE EXACT COMMIT YOU WANT TO SUBMIT

    Your team currently has 4 extensions

    You used 0 extensions in your previous submission of this assignment.
    and you are going to use 0 additional extensions now.

    You will have 4 extensions left after this submission.

    Are you sure you want to continue? (y/n):  y

    Your submission has been completed.


The safety submission strategy
------------------------------

Since you can submit as many times as you want before the deadline, a good strategy is to always make a **safety submission** well ahead of the deadline. For example, if an assignment has five tasks, and you have completed four of those tasks but expect to be working on the fifth one right up until the deadline, you should make a submission before you start working on the fifth task. That way, if you end up missing the deadline, there is already a submission in the system with most of your work on it (which may not be as good as a submission with partial or complete work for that fifth task, but still better than not submitting anything at all).

*Safety submissions are specially important if you have exhausted your extensions. If the deadline passes and you have not made any submissions, and you are out of extensions, that means an automatic zero on that assignment.*

We also recommend that you plan to make your absolute final submission at least an hour before the deadline, in case there are any issues when you try to submit. If an issue does come up, and you post about it on Piazza with an hour to go, it is very likely that an instructor or a TA will be able to assist you before the deadline. If you wait until three minutes before the deadline to submit, and run into issues, that limits how much assistance we can provide.


Using extensions
----------------

Please make sure you have read and understood the `Late submissions <syllabus.html#late-submissions>`_ section of the syllabus!

If you want to use an extension, you do not need to ask an instructor for permission and you do not need to notify us of you intention to do so. When you submit, chisubmit will simply determine how many extensions you need to use. For example, if you submit less than 24 hours after the deadline (meaning you only need to use one extension), chisubmit will include something like this when you run the submission command::

    Your team currently has 4 extensions

    You are going to use 1 extensions on this submission.

    You will have 3 extensions left after this submission.

To check how many extensions you have left, just run the following::

    chisubmit student course show-extensions


The deadline grace period
~~~~~~~~~~~~~~~~~~~~~~~~~

In every assignment, there will be a *very short* grace period after the deadline where a submission will not consume an extension. The intent of this grace period is to give some breathing room to students who run into last-minute issues when trying to submit their code (e.g., issues with git). However, you should always aim to submit your code *before* the deadline, for the following reasons:

- The length of the grace period is not disclosed, and it will be progressively shorter with each programming assignment.
- chisubmit informs the instructors of which students have submitted during the grace period. If we see a team that submits during the grace period for multiple projects, we may begin applying point penalties to any future submissions you make during a grace period.

When you submit during the grace period, chisubmit will print the following before you confirm your submission::

    NOTE: You are submitting after the deadline, but the instructor has
    allowed some extra time after the deadline for students to submit
    without having to consume an extension.

And the following once you confirm your submission::

    Your submission has been completed.

    Your submission was made during the deadline's grace period. This means
    that, although your submission was technically made *after* the
    deadline, we are counting it as if it had been made before the deadline.

    In the future, you should not rely on the presence of this grace period!
    Your instructor may choose not to use one in future assignments, or may
    use a shorter grace period. Your instructor is also aware of which
    submissions are made during the grace period; if you repeatedly submit
    during the grace period, your instructor bring this to your attention.


Re-submitting with an extension
-------------------------------

As we said earlier, chisubmit flags your submission as being ready for grading once the
deadline passes, which means the graders might start looking at your submission right away. 
This is why re-submitting after the deadline is a bit trickier: the graders may have
already started grading your code.

If you made a submission before the deadline and realize (before the deadline) that you 
want to use an extension after all, then you need to cancel your submission. That way, 
chisubmit will not flag it as ready for grading when the deadline passes. Simply run this comm

    chisubmit student assignment cancel-submit p1a

You should see something like this::

    This is your existing submission for assignment p1a:

          Commit: 5b485c80fad76d02df675044b6b4c6c0d32b4ae8
            Date: 2017-01-09 19:17:56
         Message: p1a done! For real! This time!
          Author: Borja Sotomayor <borja@cs.uchicago.edu>

    Are you sure you want to cancel this submission? (y/n):  y

    Your submission has been cancelled.

Once you've done that, just re-submit *after* the deadline, and chisubmit will apply 
the necessary extensions.

The above command may even work *after* the deadline: if the graders haven't actually
started grading your code, chisubmit will still allow you to cancel your submission,
even if the deadline has passed. However, if you plan to resubmit after the deadline,
you should always aim to cancel your submission before the deadline. 

If you try to cancel it after the deadline, and the graders have started grading your code,
chisubmit will not allow you to cancel your submission. 
You will need to ask an instructor to cancel your submission manually,
which may involve having to tell the graders to discard any grading they have already 
done on your submission. This is very inconvenient to the graders, so please try to 
avoid getting into this situation.

