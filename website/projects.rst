Projects
--------

General
~~~~~~~

Make sure you read the following before working on any of the projects:

* **Supported software environments**: We can only provide support for work performed
  on a CS Linux machine or using a `CS Virtual Machine <https://howto.cs.uchicago.edu/vm:index>`_
  (version 201718.3 or higher). If you use any other software environment, it is your
  responsibility to test your work on a supported environment before submitting your code.

  Note: The CS Virtual Machine is **required** to complete Project 3 (this project uses
  a network simulator that requires root access on a Linux machine, and the easiest way to
  provide this to you is through a virtual machine). Even if you don't plan on using the virtual
  machine for Projects 1 and 2, you may want to ensure (well ahead of Project 3) that
  you are able to install and use the virtual machine.
* `Using Git <git.html>`_: If you are unfamiliar with Git, read this first.
* `Registering for the projects <registering.html>`_: Before you start working on
  each project, there are some steps you need to take to register for each project.
* `Uploading the initial code to your repository <initial_code.html>`_: We provide starter
  code for all the projects. To upload this code to your repository, make sure to follow 
  the instructions described in this page.
* `Submitting a project <submit.html>`_: This page explains how to submit your projects,
  including how to use your extensions.
* `Style Guide <style_guide.html>`_: Conventions for writing C code in this class.




Project 1: chirc
~~~~~~~~~~~~~~~~

In this project, you will implement a simple Internet Relay Chat (IRC)
server called chirc. This project has three goals:

#. To provide a refresher of socket and concurrent programming covered
   in CMSC 15400.

#. To implement a system that is (partially) compliant with an
   established network protocol specification.

#. To allow you to become comfortable with high-level networking
   concepts before we move on to the lower-level concepts in this
   course.

The project specification is available `here <http://chi.cs.uchicago.edu/chirc/>`_.

Make sure you read the `Project 1 rubric <project1_rubric.html>`_ and the `Project 1 tips <project1_tips.html>`_.

Project 2: chitcp
~~~~~~~~~~~~~~~~~

.. admonition:: WARNING: Project 2 has not yet been updated for Winter 2018!

   You can find here the links to the project specification, and other resources,
   exactly as they were assigned in 2017. You may find them useful to get a sense
   of what the project will involve, but **DO NOT** work on this project until
   we tell you to do so, as the project specification may change.

In this project you will be implementing the Transmission Control Protocol, as
specified in `[RFC793] <http://tools.ietf.org/html/rfc793>`__. However, instead
of implementing it inside the operating system itself, you will be implementing
it inside a system called chiTCP. This system allows you to write socket-based
applications that rely on your TCP implementation instead of the one included
in your operating system. To do this, chiTCP provides an alternate socket
library, chisocket, that provides the same functions as the standard socket
library (``connect``, ``send``, ``recv``, etc.). Although the chisocket
functions have the same expected behaviour as the standard socket functions,
they do not implement the entire functionality provided by standard sockets
(e.g., non-blocking sockets are not supported).

The project specification is available `here <http://chi.cs.uchicago.edu/chitcp/>`_.

Make sure you read the `Project 2 rubric <project2_rubric.html>`_ and the `Project 2 tips <project2_tips.html>`_.


Project 3: chirouter
~~~~~~~~~~~~~~~~~~~~

.. admonition:: WARNING: Project 3 has not yet been updated for Winter 2018!

   You can find here the links to the project specification, and other resources,
   exactly as they were assigned in 2017. You may find them useful to get a sense
   of what the project will involve, but **DO NOT** work on this project until
   we tell you to do so, as the project specification may change.

   Also, **DO NOT** install last year's virtual machine, as it will undergo
   major updates for this year. We cannot provide any support on this project
   if you install an outdated VM.

In this project you will be implementing a simple IP router capable of routing IPv4 datagrams between multiple networks. This router will have a static routing table, so you will not have to deal with implementing a routing protocol like RIP or OSPF; instead, the project will focus on the routing of IP datagrams. While, at a high level, this just involves receiving IP datagrams and figuring out what interface they should be sent on, this requires building additional functionality before you can actually start routing IP datagrams.

The project specification is available `here <http://chi.cs.uchicago.edu/chirouter/>`_.

Make sure you read the `Project 3 rubric <project3_rubric.html>`_ and the `Project 3 tips <project3_tips.html>`_.

Take into account that this project requires using a network simulator that
needs to be run with root privileges on a Linux machine. If you do not have
access to such a machine, you can use a virtual machine to run the network
simulator. If you need to use a virtual machine, please read our 
`VM instructions <project3_vm.html>`_.


.. toctree::
   :maxdepth: 2
   :hidden:

   git.rst
   registering.rst
   initial_code.rst
   submit.rst
   project1_tips.rst
