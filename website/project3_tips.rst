Project 3 Tips
==============

Before you get started
----------------------

- Make sure you've read all the pages listed under "General" in the main `Projects <projects.html>`_
  page.
- Double-check that your repository has a single ``chirouter`` directory in it, and that the chirouter 
  files are in that directory. If the chirouter files (``README.md``, ``src/``, ...) are in the top 
  level of your repository, they will not be graded. Make sure you follow the exact instructions 
  in `Uploading the initial code to your repository <initial_code.html>`_.

Using the CS Virtual Machine
----------------------------

The mininet network simulator in Project 3 must be run with root privileges
on a Linux machine. If you do not have access to such a machine, we recommend
using the `CS Virtual Machine <https://howto.cs.uchicago.edu/vm:index>`_ (version 201718.3 or higher)
to run mininet. 

Take into account that this doesn't mean you have to do all your development work inside the virtual machine; you
will be able to continue to use your usual development environment (your laptop,
a CSIL machine, etc.). You will simply need to follow the instructions on 
"Running chirouter and mininet on separate machines" in the chirouter documentation. Please note that,
when using the CS Virtual Machine, the ``HOST`` you must specify in the ``--chirouter`` parameter
to ``run-mininet`` is **10.0.2.2**. This is the IP that, from inside the VM, will allow you to connect
to the host that is running the VM.

Please note that, for this to work, the Network settings for your VM (in VirtualBox) must indicate that
"Adapter 1" is attached to **NAT**. This is the default value but, if you change this value, it will likely prevent chirouter and mininet
from being able to communicate.


Resetting Mininet
-----------------

If, at any point, Mininet starts behaving in an unexpected manner, specially if you see the following error message
when running chirouter::

    CRITIC Error while processing POX message.
    CRITIC Error while receiving messages from POX

Try stopping chirouter and mininet, and then running this::

    sudo mn -c

This will reset Mininet to a clean configuration. Next, try re-running the chirouter and mininet commands as usual.


Unexpected UDP packets on port 67
---------------------------------

If you are running Mininet on your own machine (as opposed to inside a VM), certain traffic from your machine can leak
into Mininet. Most notably, a Linux machine running Network Manager (as most Ubuntu distros do) will probably try to
send DHCP requests (on UDP port 67) to the network interfaces created by Mininet, and these will show up in your logs.
You can safely ignore them, but you may want to consider using our provided VM, which will provide a more controlled
environment on which to run Mininet.


Always create protocol headers from scratch
-------------------------------------------

Whenever you are creating a protocol header, it is good practice to create it from scratch, instead of trying to reuse
an existing header. For example, suppose you receive an IP datagram that will cause an ICMP reply to be sent. You may
be tempted to take the IP header, make any necessary modifications in-place, and create a new payload. This is very
error-prone, specially if you do this at various points in your code. It is better to have a separate function
that will create a new protocol header, forcing you to think about the exact values you need to provide
in every field of the header, than to try to reuse existing headers.

Note: this does not apply to IP forwarding, where the existing IP header is kept largely intact, except for some
well-defined modifications.


Common Pitfalls
---------------

* **Computing a checksum over a pointer instead of what the pointer points to**: Suppose you have the following variable::

    iphdr_t *hdr;

  And that you have malloc'd and populated the values in the IP header. A common mistake is to call the ``cksum`` function like this::

      cksum(hdr, sizeof(hdr))

  This will compute a checksum over 4 or 8 bytes, because ``hdr`` is a pointer, and its size is 4 or 8 bytes. Make sure you pass the correct size to ``cksum``. For an IP header, you would call ``cksum`` like this::

      cksum(hdr, sizeof(iphdr_t))

* **Computing ICMP header sizes**: Related to the above, you cannot use ``sizeof(icmp_packet_t)``, since ``icmp_packet_t`` is a ``union`` type,
  and will likely yield an incorrect size. You should manually compute the size of your ICMP packet.


* **Forgetting to use htons, htonl, etc.**: Remember that the values in the protocol headers have to be in *network order*, and
  you must use functions like htons and htonl to convert from host order to network order (and ntohs and ntohl to convert from
  network order to host order)

* **... except with checksums**: The ``cksum`` function already produces a checksum in network order. There is no need to convert it from host order to network order.
