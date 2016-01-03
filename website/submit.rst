Submitting a project
--------------------

Preliminaries
~~~~~~~~~~~~~

* Submissions are made using the ``chisubmit`` tool. Make sure you run these commands from your chisubmit directory
  (the one you initialized with ``chisubmit init`` as described in `Registering for the projects <registering.html>`_).
* Before making a submission, make sure you have pushed your code to the GitLab server. If your code hasn't been pushed to GitLab, then ``chisubmit`` will not see it.

Selecting the commit you want to submit
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To submit a project for grading, you first need to select the specific commit you want us to grade. Commits in git are identified by a SHA-1 hash, and look something like this::

    4eac77c9f11dfb101dbbbe3e9f2df07c40f9b2f5

You can see the list of commits in your repository by running the following::

    git log

Or, if you simply want to get the SHA-1 hash of the latest commit in your `master` branch, you can just run this::

    git rev-parse master

Making the submission
~~~~~~~~~~~~~~~~~~~~~

Once you've identified the commit you want to submit, you need to run the following **BEFORE THE DEADLINE**::

    chisubmit student assignment submit <team-id> <assignment-id> <commit-sha>

Where:

* ``<team-id>`` is your team identifier, which is also your repository name (typically your CNetIDs separated by hyphens).
* ``<assignment-id>`` is the project identifier. Your instructor will tell you what identifier to use, but you can also see the list of possible assignment ids by running `chisubmit student assignment list`.
* ``<commit-sha>`` is the SHA-1 hash of the commit you want to submit.

For example, the command could look something like this::

    chisubmit student assignment submit amr-borja p1a 4eac77c9f11dfb101dbbbe3e9f2df07c40f9b2f5

You will be given an opportunity to verify the details of the submission before you actually submit your code. For example, the above command would print something like this::

    You are going to make a submission for p1a (chirc: Part 1).
    The commit you are submitting is the following:
    
          Commit: 4eac77c9f11dfb101dbbbe3e9f2df07c40f9b2f5
            Date: 2015-01-07 08:55:31
         Message: Ready for submission
          Author: Borja Sotomayor <borja@cs.uchicago.edu>
    
    PLEASE VERIFY THIS IS THE EXACT COMMIT YOU WANT TO SUBMIT
    
    Your team currently has 4 extensions
    
    You are going to use 0 extensions on this submission.
    
    You will have 4 extensions left after this submission.

    Are you sure you want to continue? (y/n):

Before you type "y", **take a moment to ensure that this commit is the one you actually want to submit**. If the commit message and date shown by chisubmit don't look right, then you should double-check whether you were able to successfully commit and push your code.

Finally, remember that the above has to be run *before the deadline*. If you fail to do so, it doesn't matter if your code was pushed to the GitLab server before the deadline. For your code to be accepted for grading, you must also run the `chisubmit` submission command before the deadline. The `chisubmit` system will mercilessly stop accepting submissions once the deadline has passed.


Verifying that your submission went through
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following command will show you the projects you are registered for, and whether you have made a submission for them::
 
   chisubmit student team show TEAM_ID
   
If you have not submitted a project, you will see something like this::
 
    ASSIGNMENTS
    -----------
    ID: pa1
    Name: Programming Assignment 1
    Deadline: 2015-10-07 01:07:15+00:00
    NOT SUBMITTED
     
If you have submitted the project correctly, you will see something like this::
 
    ASSIGNMENTS
    -----------
    ID: pa1
    Name: Programming Assignment 1
    Deadline: 2015-10-07 01:07:15+00:00
    Last submitted at: 2015-10-07 00:07:20.017641+00:00
    Commit SHA: 2e5969ce281b88bcb3743dc81539623124e63f41
    Extensions used: 0

If you want to be extra sure, you can log into the `GitLab server <https://mit.cs.uchicago.edu>`_, then click on your repository  on the right side of the page, then click on "Commits" on the right side of the page. You will see the list of commits that are on the server (this is what the graders will see). On the right side of the page, you will see the first eight characters of each commit's SHA; find the one that was shown by ``chisubmit student team show command``, and verify that it is, indeed the version of the code that you want the graders to grade.

Amending a submission
~~~~~~~~~~~~~~~~~~~~~

If you make a submission, and realize you want to change something in your submission, all you have to do is make the changes, commit them, and run ``chisubmit student assignment submit`` with the new commit and with the ``--force`` option. For example::

    chisubmit student assignment submit amr-borja p1a 3bc2ab13a504393e12c48a3b8a56510a901329fd --force

``chisubmit`` will warn you that there is an existing submission, and will ask you to confirm that you want to make a new one::

    WARNING: You have already submitted assignment p1a and you
    are about to overwrite the previous submission of the following commit:
    
          Commit: 4eac77c9f11dfb101dbbbe3e9f2df07c40f9b2f5
            Date: 2015-01-07 08:55:31
         Message: Ready for submission
          Author: Borja Sotomayor <borja@cs.uchicago.edu>
    
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    THE ABOVE SUBMISSION FOR p1a (chirc: Part 1) WILL BE CANCELLED.
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    
    If you continue, your submission for p1a (chirc: Part 1)
    will now point to the following commit:
    
          Commit: 3bc2ab13a504393e12c48a3b8a56510a901329fd
            Date: 2015-01-07 08:59:31
         Message: Ok, really ready for submission now
          Author: Borja Sotomayor <borja@cs.uchicago.edu>
    
    PLEASE VERIFY THIS IS THE EXACT COMMIT YOU WANT TO SUBMIT
    
    Your team currently has 4 extensions

    You used 0 extensions in your previous submission of this assignment.
    and you are going to use 0 additional extensions now.
    
    You will have 4 extensions left after this submission.
    
    Are you sure you want to continue? (y/n):  y

Like your first submission, you can only re-submit *before the deadline*. Once the deadline passes, you cannot modify your submission, not even if you use extensions.

If you make a submission and, before the deadline, you realize you want to use an extension (and re-submit after the deadline with an extension), then you need to make sure you **cancel** your submission before the deadline. For example::

    chisubmit student assignment cancel-submit amr-borja p1a

You will see something like this::

    This is your existing submission for assignment pa1:
    
          Commit: 3bc2ab13a504393e12c48a3b8a56510a901329fd
            Date: 2015-01-07 08:59:31
         Message: Ok, really ready for submission now
          Author: Borja Sotomayor <borja@cs.uchicago.edu>
    
    Are you sure you want to cancel this submission? (y/n):  y
    
    Your submission has been cancelled.

Using extensions
~~~~~~~~~~~~~~~~

First of all, please note that you do not need to ask the instructors for permission to use an extension. Please do not e-mail us to ask for permission to use an extension, or even to inform us that you intend to use one. All of this is handled automatically by the chisubmit system. To use an extension, you need to use the ``--extensions`` option when submitting your assignment. For example::

    chisubmit student assignment submit <team-id> <project-id> <commit-sha> --extensions <num-extensions>

If you are using an extension, you do not need to run this command before the original deadline. Instead, you should allow the original deadline to pass, and then make sure that you make your submission (with the extension) before the extended deadline. So, if the deadline is January 12 at 8pm, and you plan to use two extensions, then the extended deadline is January 14 at 8pm.
 
chisubmit will validate that the number of extensions you’re requesting is acceptable based on the submission time, the deadline, and the number of extensions you have left. chisubmit will not allow you to submit your code if you try to request too many or not enough extensions (or if you do not have sufficient extensions to make the submission).

For example, you could run the command like this::

    chisubmit student assignment submit amr-borja p1a 4eac77c9f11dfb101dbbbe3e9f2df07c40f9b2f5 --extensions 1

Please note that if you amend a submission (using the ``--force`` parameter) for which you have used extensions, you need
to specify the number of extensions again. This does not mean that you are consuming additional extensions to amend the
submission; you are simply reasserting how many extensions you are using.

Checking your remaining number of extensions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
To see how many late chips you have left, run this::
 
    chisubmit student course show-extensions

Making a safety submission
~~~~~~~~~~~~~~~~~~~~~~~~~~

Take into account that chisubmit allows you to make multiple submissions before the deadline. A good strategy is to always make a "safety submission" well ahead of the deadline. For example, if a project has five tasks, and you have completed four of those tasks but expect to be working on the fifth one right up until the deadline, you should make a submission before you start working on the fifth task. That way, if you end up missing the deadline, there is already a submission in the system with most of your work on it (which may not be as good as a submission with partial or complete work for that fifth task, but still better than not submitting anything at all).

**Safety submissions are specially important if you have used all your extensions**. If the deadline passes and you have not made any submissions, and you are out of late chips, that means an automatic zero on that assignment.


