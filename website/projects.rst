Projects
--------

General
~~~~~~~

Make sure you read the following before working on any of the projects:

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

Make sure you read the `Project 1 tips <project1_tips.html>`_.


Project 2: chitcp
~~~~~~~~~~~~~~~~~

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


Project 3: chirouter
~~~~~~~~~~~~~~~~~~~~

Coming soon.

.. toctree::
   :maxdepth: 2
   :hidden:

   git.rst
   registering.rst
   initial_code.rst
   submit.rst
   project1_tips.rst