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

Resetting Mininet
-----------------

If, at any point, Mininet starts behaving in an unexpected manner, specially if you see the following error message
when running chirouter::

    CRITIC Routing table included interface eth1, but received no such interface from POX
    CRITIC Error while processing POX message.
    CRITIC Error while receiving messages from POX

Try stopping chirouter, POX, and mininet, and then running this::

    sudo mn -c

This will reset Mininet to a clean configuration. Next, try re-running the POX, Mininet, and chirouter commands as usual.

29 bytes?
---------

An ARP message is 28 bytes long, but you may observe that some of your *inbound* ARP messages are 29 bytes long. You can safely ignore this,
as long as you only process the first 28 bytes of the ARP message. Take into account that when you generate an ARP message,
you must make sure it's 28 bytes long.

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
