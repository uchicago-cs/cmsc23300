Using Git
---------

    This page is based on a lab written by `Gustav Larsson <http://people.cs.uchicago.edu/~larsson/>`_ for CMSC 12300

In many of your previous CS courses, you became familiar with using Subversion (SVN) to handle *revision control* (or *version control*) of your projects and assignments. In this class, we will be using Git instead, which has become the most popular revision control system in the open-source community in recent years. This page provides an overview of Git, and should be enough to get started, specially if you are already familiar with SVN. For a deeper dive into Git, we recommend consulting the `Pro Git <http://git-scm.com/book>`_ book (available for free online).

This page will also guide you through creating a GitHub account, which will allow you to experiment with uploading (or "pushing") your Git repository to a remote repository (and, also, because having a GitHub account is a generally useful thing to do). However, please note that, in this class, we will be using a `GitLab <https://about.gitlab.com/`>_ server run by the CS department. Working with GitLab is fairly similar to working with GitHub, but it is very important that you do not upload any of your code from the projects to your GitHub account!

Git
~~~

In the olden days (~10 years ago), most open-source projects used primarily CVS or SVN, the latter being a newer replacement of the former. These systems follow a client-server model, where you commit and check out the source code to and from a single server. In our case, that server was PhoenixForge, hosted by the university.

In the last 5-10 years, there has been a move to using distributed revision control systems, where there is no technical distinction between client and server. In this paradigm, each computer has its own self-contained copy of the version history, and updates can be shared between any two computers. This offers a lot more flexibility, that you may or may not experience during this course. I say that, since it can still be used in a client-server manner, which is mainly how we will use it. Luckily, these newer systems also offer many other improvements over their predecessors. Three of the most popular such systems today emerged in 2005 and are called Git, Mercurial and Bazaar. We will be using Git.

Git basics
~~~~~~~~~~

Let us look at some of the basics of Git. Since Git is decentralized, we do not need a server to get started. To create a new repository, simply do::

    $ mkdir new-project 
    $ cd new-project
    $ git init

That's it, we now have an empty local repository. Try::

    $ git status

It will say *nothing to commit*, so let us add a file. Create a text file, add some random text and save it as ``file1.txt``. If you run ``git status`` again, you will see that it lists ``file1.txt`` under *Untracked files*. Just like in SVN, run::

    $ git add file1.txt

If you run ``git status`` yet again, you will see that the file is now listed under *Changes to be committed*. Before we commit it, Git needs to know your name and e-mail, which will help identify you in the version history. It is important in this step to specify **the same e-mail as when signing up to GitHub** later in this document. To set this up, please run the following::

    $ git config user.name "Your Name Here"
    $ git config user.email "your_email@example.com"

Now, go ahead and commit::

    $ git commit -m "Added file1.txt"

As with SVN, if you omit ``-m``, it will open up a text editor, which allows you to write longer multi-line commit messages. You can specify which editor you want to use by changing the environment variable ``GIT_EDITOR``.

Now, modify ``file1.txt`` and try running commit again. It will say *no changes added to commit*, even though we modified the file. This is because Git works a bit different from SVN and requires you to add all modified files for *staging*, meaning that they will be acknowledged by a commit. This can be done by running ``git add file1.txt`` again, but instead we shall use the shorthand ``-a``::

    $ git commit -a -m "Fixed typo in file1.txt"

This will automatically stage all tracked files before committing, giving a similar workflow as ``svn commit``, with one very important distinction: ``git commit`` only updates the *local* repository, whereby ``svn commit`` would automatically send the updates to the server. In this example, the local repository is all we have, so let us defer further discussion of this until later.

To remove a file::

    $ git rm file1.txt

If you have modified the file first without committing, Git will complain much like Subversion would. To circumvent this and remove the file anyway, add the flag ``-f`` as instructions will suggest.

Instead of having only a local repository, we will let GitHub host our projects and use it in a client-server manner.

GitHub
~~~~~~
`GitHub <https://github.com>`_ is a website that offers free hosting of Git repositories for any open-source project, with plenty of additional features that grease the wheels of collaborative work.

For instance, GitHub makes it easy to *fork* (clone) someone else's open-source project, which means you create your own copy of it, where you have free rein. In your cloned version, you can fix bugs, add features or simply experiment in any way that you want. Anyone can use your cloned version, but if you really think your changes would be useful to everyone, then you can open a *pull request*, to have those changes merged back into the main repository. GitHub makes it easy to manage your repositories, discuss changes, track bugs/issues, create wikis and visualize statistics for your project, and follow the progress of other developers and their projects.

GitHub account
~~~~~~~~~~~~~~
To work through the rest of the instructions in this page, you will need a GitHub account. If you already have one, you can skip this step and simply use your existing account. 

Go to https://github.com/ and follow the instructions on how to create an account. This is straightforward. Remember to use the same e-mail as you specified earlier.

Once you have created an account, make sure you add your SSH public key to your account (otherwise, you will only have read-only access to GitHub). You can do this in this page: https://github.com/settings/ssh. If you do not know what an SSH key is, or do not know how to generate one, read https://help.github.com/articles/generating-ssh-keys.

Create a repository
~~~~~~~~~~~~~~~~~~~
In this course, we will create a repository for you on the department's GitLab server. However, if you're new to Git, you should try creating a repository under your GitHub account so you can experiment and tinker around without fear of messing up your CMSC 23300 repository.

We will create our Git repository through GitHub's web interface. Once logged in, you should see several icons in the top right corner, next to your username. Click on the left-most icon, which should say "Create new..". If you click on it, you will have the option to select "New repository". Pick a name for your repository and write a short description. 

GitHub only offers free hosting for *Public* (open-source) projects, and if you select *Private* you will see that payment options appear. Select *Public* and also tick the box *Initialize this repository with a README*.

Finally, GitHub can add an appropriate ``.gitignore`` for your project if you know what programming language you will be using. The ``.gitignore`` file will tell Git to hide certain files from ``git status`` that should not be commited, such as ``.o`` files in C or log files.

Once the project is created, you need to create a local clone on your computer.

Cloning from GitHub
~~~~~~~~~~~~~~~~~~~
On your repo's front page, you will see a text field on the right column called "SSH clone URL". Select this URL and copy it to your clipboard. Now, go to an appropriate folder in your home directory where you want to put your local copy. Take into account that when we clone (check out) a repository, Git will create a folder with the repo's name for us, so there is no need to do that separately. Now, enter ``git clone`` followed by pasting from your clipboard, e.g.::

    $ git clone git@github.com:<username>/<reponame>.git

Now, you are all set up to interact with the repository as previously described. Please add a file similar to ``file1.txt``. This can be a temporary file, in which case you should remove it later.

When the file has been added and committed, it will not automatically appear on GitHub, as it would on PhoenixForge for SVN. Since Git is distributed, committing only means accepting the changes to the local repository. The next step is to push these changes to GitHub. This is done by::

    $ git push origin master

The parameter ``origin`` tells us to push the change to the place from where we cloned it, and ``master`` refers to the branch. 

.. note:: 

    By default, a repo has a single *branch* and it is called ``master``. Branches are used to keep several parallel versions of your source code. You can for instance use a branch for each new feature, and then merge them into ``master`` once they are done. A more elaborate example of using branches can be seen in the blog post `A successful Git branching model <http://nvie.com/posts/a-successful-git-branching-model/>`_. Using branches in this way requires a lot more Git fluency, so you will probably just stick with one ``master`` branch at first.

The fact that we can work on our project and commit several times without the need to be connected to our SVN server is one of the benefits of distributed revision control. 

Finally, to pull changes from GitHub, essentially performing the equivalent of ``svn up``::

    $ git pull origin master

If the remote repository (on GitHub) has changed since you last pulled from it, you will need to run ``git pull`` before you can run ``git push``. At this point, there might be a conflict between your changes and someone else's that Git can't merge automatically. In this case, it will include both versions in the file, looking something like::

    This is a text file.
    <<<<<<< HEAD:file1.txt
    This is version 1. 
    =======
    This is version 2.
    >>>>>>>
    Here is some more text.

To resolve this conflict, all you have to do is edit the file in any way that you want as long as you remove the lines with ``<<<<<<<``, ``=======`` and ``>>>>>>>``. When you are done, call ``git commit -a`` as usual. If you run into problems, please post a question on Piazza.

Committing etiquette
~~~~~~~~~~~~~~~~~~~~
Remember to commit **often** with **descriptive commit messages**. Try to avoid committing code that doesn't run into the ``master`` branch. If it will take a while for your project to be running at all, you should relax this suggestion and still commit often. Please avoid committing files that does not belong in the repository (binaries, logs, etc.), and remove them if you accidentally add them at some point. 


GitHub vs GitLab
~~~~~~~~~~~~~~~~

Remember: this page presents GitHub as an easy way for you to get acquainted with how to use a remote Git server. However, 
in this class, we will use the CS department's GitLab server. **Never upload any of your CMSC 23300 code to GitHub**

