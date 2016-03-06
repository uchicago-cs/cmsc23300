Project 3 Virtual Machine
=========================

The mininet network simulator in Project 3 must be run with root privileges
on a Linux machine. If you do not have access to such a machine, we recommend
using a virtual machine to run mininet. Take into account that this doesn't
mean you have to do all your development work inside the virtual machine; you
will be able to continue to use your usual development environment (your laptop,
a CSIL machine, etc.), and will simply instruct chirouter to connect to the instance
of mininet running on the virtual machine (instead of running mininet directly
on your machine).

Although mininet provides some ready-to-use VMs, we will be using the VM image
from CMSC 12100. This is an Ubuntu image that closely mirrors the standard CS
Linux environment, and which our Techstaff is deeply familiar with if we
run into any issues. Furthemore, this VM image can be run with VirtualBox,
an open source virtualization software package.

You can download the VM here:

    `http://mirror.cs.uchicago.edu/techstaff/cs121-aut-15-final.ova <http://mirror.cs.uchicago.edu/techstaff/cs121-aut-15-final.ova>`_ [3.3 GB]

To get the VM running on Windows or OS X, just follow the instructions provided 
`on the CS 121 website <https://www.classes.cs.uchicago.edu/archive/2015/fall/12100-1/install-guide/index-download.html>`_, with the following exceptions:

* You can download the latest version of VirtualBox (you don't need to use the 5.0.4
  version specified in those instructions)
* If installing on OS X, you can skip steps 8 and 9, and all the steps after (and including) step 16.
* If installing on Windows, you can skip steps 7 and 8, and all the steps after (and including) step 14.

Make sure you start the VM on an Internet-connected machine. Once you do so, log into
the VM (username: ``student``, password: ``uccs``), open a terminal and run the following
commands::

    sudo apt-get update
    sudo apt-get install traceroute
    
    git clone https://github.com/uchicago-cs/chirouter.git
    git clone https://github.com/mininet/mininet.git
    
    cd mininet/
    git checkout -b 2.2.1 2.2.1
    util/install.sh -nfv
    
Take into account that this final command will take a while to run.

At this point, your VM will be set up to run mininet and POX. You can
use the VM in one of two ways:

* Developing your code directly on the VM
* Developing your code elsewhere, and using the VM only to run mininet.

Please follow the instructions below for the appropriate case:

Using the VM as your development environment
--------------------------------------------

If you do this, you do not need to configure your VM further, and you
will be able to run the mininet and POX commands as described in the
chirouter documentation.

However, you will need to clone your repository inside the VM, which
will require generating and upload SSH keys as described in
`Uploading the initial code to your repository <http://uchicago-cs.github.io/cmsc23300/initial_code.html>`_

Nonetheless, you may want to run the following to disable Ubuntu's Network
Manager, as it can sometimes interfere with the virtual networking
devices created by mininet::

    sudo stop network-manager
    sudo ifconfig eth0 up
    sudo dhclient eth0

Note: You will have to re-run these commands if you reboot the VM.


Using the VM only to run mininet
--------------------------------

In this case, you will run POX and mininet inside the VM. Note that
you can do so using the chirouter repository you cloned earlier,
following the instructions in the chirouter specification.
*You do not neet to clone your team's repository*. Instead,
your team repository will be in the host machine (i.e., the machine
that is running the VM). You will build and run chirouter on the
host machine, and then instruct chirouter to connect to POX/mininet
on the VM.

However, while VirtualBox will, by default, allow your VM to access the
Internet using the host machine's network, it won't allow
the VM and the host machine to communicate directly, so we
need to change your VM's network configuration to use "Host Only" mode.

To do this, you must first create a Host-only Network. On VirtualBox,
go to File -> Preferences -> Network -> Host-only Networks, and then
click on the plus icon.

Next, before starting your VM, click on Settings -> Network, and
select "Host-only Adapter" under "Attached to". Note that you can
also do this while the VM is running by clicking on the network icon
on the bottom-left corner of the VM window (the network icon is the one
with two computers).

Then, from a terminal in the VM, run the following::

    sudo stop network-manager
    sudo ifconfig eth0 up
    sudo dhclient eth0

This will stop Ubuntu's Network Manager, which can interfere with
the virtual network devices created by mininet. Note: You will have 
to re-run these commands if you reboot the VM.

Next, you need to find out what IP address has been assigned to your
machine. Run this from inside the VM::
    
    ifconfig eth0

The address will likely be an address like 192.168.56.101. You should
verify that you can ping this IP address from the host machine.

Now, when you run chirouter, you must include an ``-s`` option to
specify that you're connecting to POX/mininet on a different machine.
For example::

    ./chirouter -s 192.168.56.101 -p 9999 -r topologies/basic/rtable9999 -vv
    
Note: setting the VM to Host-only Networking will prevent the VM from accessing
the Internet. If you later on realize you need to access the Internet from the VM,
just go back to the Network settings and switch the "Attached to" option to "NAT".




