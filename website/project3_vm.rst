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

Although mininet provides some ready-to-use VMs, we will be using our own
VM image. This is an Ubuntu image that closely mirrors the standard CS
Linux environment, and which our Techstaff is deeply familiar with if we
run into any issues. Furthemore, this VM image can be run with VirtualBox,
an open source virtualization software package. 

Please note that the VM **does not recognize CNetIDs, nor will it have access to your CS
home directory**. However, as we explain below, you will be able to develop
your code in your environment of choice, and then use the VM only when you
need to test your code (and you will not even have to copy your code into the VM;
your chirouter implementation can run on your own machine, and then communicate
with mininet and POX on the VM).

You can download the VM here:

    `http://mirror.cs.uchicago.edu/techstaff/cs233-win-17.ova <http://mirror.cs.uchicago.edu/techstaff/cs233-win-17.ova>`_ [3.3 GB]

    MD5: 75519a792d99b747789a8e036a344751

To get the VM running on Windows or OS X, just follow the instructions provided 
`on the CS 121 website <https://www.classes.cs.uchicago.edu/archive/2016/fall/12100-1/install-guide/index-download.html>`_ (that class
used a similar VM). However, please note the following exceptions:

* Instead of the ``cs121-aut-15-final.ova`` file referred to in that page, use the 
  OVA file you downloaded from the URL above.
* You can download the latest version of VirtualBox (you don't need to use the 5.0.4
  version specified in those instructions)
* If installing on OS X, you can skip steps 8 and 9, and all the steps after (and including) step 16.
* If installing on Windows, you can skip steps 7 and 8, and all the steps after (and including) step 14.

Make sure you start the VM on an Internet-connected machine. Once you do so, log into
the VM (username: ``student``, password: ``uchicago``). The software to run mininet
and POX is already installed on the VM, and you can
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

    sudo service network-manager stop

Note: You will have to re-run this command if you reboot the VM.


Using the VM only to run mininet
--------------------------------

In this case, you will run POX and mininet inside the VM, but you will
develop and run your chirouter code elsewhere (typically, on the machine
that is running the VM).

To run POX and mininet, the VM already includes a clone of the chirouter repository
in your home directory, and you should run POX and mininet
from the ``~/chirouter/`` directory. **You do not neet to clone your 
team's repository in the VM**. Instead,
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

    sudo service network-manager stop

This will stop Ubuntu's Network Manager, which can interfere with
the virtual network devices created by mininet. Note: You will have 
to re-run this commands if you reboot the VM.

Next, you need to find out what IP address has been assigned to your
machine. Run this from inside the VM::
    
    ifconfig

The network interface for your VM may not have the usual ``ethX`` name,
so you should look for an interface with a private IP address, typically
something like 192.168.56.101. You should
verify that you can ping this IP address from the host machine.

Now, when you run chirouter, you must include an ``-s`` option to
specify that you're connecting to POX/mininet on a different machine.
For example::

    ./chirouter -s 192.168.56.101 -p 9999 -r topologies/basic/rtable9999 -vv
    
Note: setting the VM to Host-only Networking will prevent the VM from accessing
the Internet. If you later on realize you need to access the Internet from the VM,
just go back to the Network settings and switch the "Attached to" option to "NAT".


Common issues when running the VM
---------------------------------

Enabling virtualization extensions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
If you try to run the VM and VirtualBox shows a message like this::

    Failed to open a session for the virtual machine CMSC23300.
     
    VT-x is disabled in the BIOS for all CPU modes (VERR_VMX_MSR_ALL_VMX_DISABLED).
    Result Code:	E_FAIL (0x80004005)
    Component:	ConsoleWrap
    Interface:	IConsole {872da645-4a9b-1727-bee2-5585105b9eed}

This means that your computer's "virtualization extensions" (which enables the CPU to efficiently run virtual machines) have not been activated. You can usually activate them by rebooting your computer and going into the BIOS menu (usually by pressing Esc or Shift at boot; if your computer is nice, it will probably tell you exactly what key to press to interrupt the computer's bootup and to go into the BIOS menu)

Once there, you'll have to look around for the option to turn on "VT-X" or "VMX" or some variation of the term "Virtualization Extensions". If you're unsure on how to do any of this, try Googling for your computer's brand/model along with "BIOS menu" or "virtualization". This will likely turn up the appropriate instructions for your machine.

Corrupted download
~~~~~~~~~~~~~~~~~~

If VirtualBox complains about trying to import or launch a corrupted VM, make sure the OVA file
you downloaded was correctly downloaded. You can check the integrity of the file by running
the following::

    md5sum cs233-win-17.ova

The resulting MD5 hash should match the one shown at the top of this page. If it doesn't,
try re-downloading the file. We recommend using ``wget`` or ``curl``, which will usually
deal better with resuming an interrupted download.


