Registering for the projects
----------------------------

Registering for the first time
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

We use a command-line tool called ``chisubmit`` to manage teams and their repositories in this course. Before you can start working on the projects, you will need to register your team with `chisubmit` (this will result in a Git repository being created for your team in our GitLab server). First, choose an empty directory in your CS home directory on which to do your CMSC 23300 work on. Inside that directory, run the following command on a CS Linux machine (or by SSH'ing into linux.cs.uchicago.edu):: 

    chisubmit init

When prompted for your "chisubmit username" and "chisubmit password", just use your CNetID and password. Once you have entered your username and password, you will be shown a list of courses you belong to in ``chisubmit``. If CMSC 23300 does not appear in them, you registration information may not have been added to ``chisubmit`` (if you registered for the class recently, please try again in 24 hours; if not, please contact your instructor).

After ``chisubmit init`` runs successfully, you will be able to run ``chisubmit`` commands from inside that directory.

The first thing you should do is register for the first project (``p1a``) as a team. You (``studentA``) must run this command::

    chisubmit student assignment register p1a --partner studentB

And your partner (``studentB``) must run this command::

    chisubmit student assignment register p1a --partner studentA

You will be assigned a team name which will be composed of your CNetIDs (e.g., in this case, the team name would be ``studentA-studentB``. You can see the list of teams you are in with this command::

    chisubmit student team list

And you can use this command to check the status of your team (and, in particular, whether your partner has completed their part of the registration)::

    chisubmit student team show TEAMNAME

(where ``TEAMNAME`` should be replaced by your team name)

Once you have both registered for the first project (``p1a``), a GitLab repository will be created for you. Please note that there is usually a lag of 30-60 minutes between completing your registration and having your repository created. 

Once your repository has been created, *do not initialize or upload anything to your repository*. You should follow the instructions described in `Uploading the initial code to your repository <initial_code.html>`_. 


Registering for subsequent projects
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Once you have registered for the first project, and your team repository has been created, you will need to register for the other projects too (otherwise, you will not be able to submit them). However, you do not need to repeat all the steps described above. If you are working with the same partner, all you (``studentA``) has to do is run the following command from your chisubmit directory (the one you initialized with `chisubmit init`)::

    chisubmit student assignment register PROJECT_ID --partner studentB
    
Where ``PROJECT_ID`` should be replaced with the project you are registering for (``p1b``, ``p1c``, ``p2a``, ``p2b``, or ``p3``). Your partner, ``studentB``, does not need to run the equivalent command (since you are both already confirmed to be working together). 

We suggest you register for an assignment as soon as you know you will be working on it (i.e., do not wait until right before the deadline). This way, the instructor will know what teams are working on what projects.

Finally, please make sure your project partner wants to continue working with you before registering your team again. If you want to cancel your registration for a given assignment, just run the following::

    chisubmit student assignment cancel-registration PROJECT_ID

If you decide to switch to a different team for one of the projects, then both you and your new partner will have to run the ``chisubmit student assignment register`` command, and you must wait for a shared repository to be created for your team.

