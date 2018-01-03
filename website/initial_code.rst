Uploading the initial code to your repository
---------------------------------------------

For each project, we provide some initial code that you must upload to your repository. We need you to upload this code in a very specific way, to make sure that our grading scripts can find your code, build it, and run tests on it.

In this page we provide the exact commands you need to run to set up your repository. Some of them will look like dark magic but, at this point, you do not need to understand them.

Preliminaries
~~~~~~~~~~~~~

* If you are new to Git, make sure you've read the `Using Git <git.html>`_ page.
* Make sure you have added your SSH public key to your GitLab account (otherwise, you will only have read-only access to the GitLab server). You can do this in this page: https://mit.cs.uchicago.edu/profile/keys. If you do not know what an SSH key is, or do not know how to generate one, read https://help.github.com/articles/generating-ssh-keys.
* Only one of the team members needs to initialize the repository. In other words, do *not* follow these instructions more than once. Once one of you has initialized the repository, the other team member will be able to simply create a local copy of the (initialized) Git repository that you are both sharing.
* The first thing you need to do is create an empty local repository. In an empty directory, run the following::

        git init

  For the procedure described in this page to work, you also need to make sure that there is at least one commit in your repository. You can simply add a README file with the names of the students in your group, and commit it like so::

        git add README
        git commit -m "Added README"

* The procedure described in this page relies on the ``git subtree`` subcommand. This command was added in Git 1.7.11, so you must use at least that version of Git. Please note that ``git subtree`` *is* available on the CS machines.

Project 1
~~~~~~~~~

To initialize your repository for project 1, run the following commands from inside your local repository (i.e., the directory where you ran ``git init``). Make sure you substitute ``studentA-studentB`` with your repository name.

::

    REPO_NAME=studentA-studentB
    git remote add -f origin git@mit.cs.uchicago.edu:cmsc23300-win-18/$REPO_NAME.git
    git remote add -f chirc-upstream https://github.com/uchicago-cs/chirc.git
    git subtree add --prefix chirc chirc-upstream master --squash

At this point, you have only added the code to your local repository. To push it to your GitHub repository, run the following::

    git push -u origin master

If you want to create other copies of the repository (e.g., if you are the team member who did *not* run the above commands) just run the following *after* the repository has been initialized::

    git clone git@mit.cs.uchicago.edu:cmsc23300-win-18/$REPO_NAME.git

If we make any changes to the upstream repository, and you want to merge them into your repository, you need to run the following command::

    git subtree pull --prefix chirc chirc-upstream master --squash

Project 2
~~~~~~~~~

The process is the same as the one described for Project 1, except with the following commands to add the initial code::

    git remote add -f chitcp-upstream https://github.com/uchicago-cs/chitcp.git
    git subtree add --prefix chitcp chitcp-upstream master --squash

And the following command to pull any updates from upstream::

    git subtree pull --prefix chitcp chitcp-upstream master --squash

Project 3
~~~~~~~~~

The process is the same as the one described for Project 1, except with the following commands to add the initial code::

    git remote add -f chirouter-upstream https://github.com/uchicago-cs/chirouter.git
    git subtree add --prefix chirouter chirouter-upstream master --squash

And the following command to pull any updates from upstream::

    git subtree pull --prefix chirouter chirouter-upstream master --squash
