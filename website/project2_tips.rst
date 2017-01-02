Project 2 Tips
==============

Before you get started
----------------------

- Make sure you've read all the pages listed under "General" in the main `Projects <projects.html>`_
  page.
- Double-check that your repository has a single ``chirc`` directory in it, and that the chirc 
  files are in that directory. If the chirc files (``README``, ``src/``, ...) are in the top 
  level of your repository, they will not be graded. Make sure you follow the exact instructions 
  in `Uploading the initial code to your repository <initial_code.html>`_.

Interpreting RFC 793
--------------------

In this project, you will be implementing TCP, which is specified in `RFC 793 <http://tools.ietf.org/html/rfc793>`_.
Like many network protocols, certain aspects of the specification may be unclear. When you run into such an issue,
you should first check `RFC 1122 <http://tools.ietf.org/html/rfc1122>`_: it provides corrections and clarifications 
on RFC 793. If you are still unclear on how to proceed, then ask on Piazza: we will provide an ex cathedra ruling 
on how you should interpret the RFC.

That said, there are parts of the RFC that *do* provide unambiguous formulas. Sometimes, students will tweak this formulas as they try to debug their code (e.g., using <= instead of <). This may make your code work for the issue you are trying to resolve, but will probably cause issues down the road.

Finally, it is important that you implement TCP as specified in the RFC, not your interpretation of TCP (based on class notes and examples online). Replicating the behaviour of simple examples (like the 3-way handshake) may work for simple operations, but is not a good strategy for implementing all of TCP. 


Writing the Packet Arrival Handler
----------------------------------

Writing the "packet arrival handler" (i.e., how TCP reacts when a packet arrives) is actually pretty simple: you just have to translate pages 64-75 of the RFC into code. A common pitfall is to write this handler as a gigantic if-else statement (with each branch corresponding to a TCP state) where you implement your interpretation of what should happen in each state when a packet arrives. Pages 64-75 methodically describe how to process a packet. Although some parts of it do involve branching by state, you should not write a gigantic if-else as the main structure of your packet arrival handler. As noted above, it is important that you follow the RFC, not your high-level understanding of how TCP must work.


Common Pitfalls
---------------

* **Not initializing the sequence number in the buffer**: You need to initialize the initial sequence number of the buffers with ``circular_buffer_set_seq_initial``. If you do not, functions ``circular_buffer_first`` and ``circular_buffer_next`` will return incoherent values.

  Take into account that the initial sequence number of the buffers should be the same as the first sequence number of sendable/received *data*. So, it would not be exactly ISS/IRS, because those are actually the first "byte" used by the SYN (but which do not represent any actual data). So, you would initialize them to ISS+1 and IRS+1.

* **Sending only one packet when segmentizing**: Whenever you process the send buffer, you should always send as many packets as possible without exceeding the receiver's advertised window. A common pitfall is to correctly identify that the send buffer contains more than one MSS of data, but then sending only that first MSS, instead of sending as many packets allowed by SND.WND.

* **Not setting/reading the window variables**: Every TCP packet you send must include a valid value for SEG.WND. This is true regardless of whether the size of the receive buffer has changed since the last TCP packet, and regardless of whether the packet carries a payload or not. The value of SEG.WND is always set to the available space in the receive buffer.

  Similarly, the value of SND.WND is always updated when you receive a valid TCP packet.

* **Not delaying the FIN packet**: When an APPLICATION_CLOSE event happens, you *only* send a FIN packet if the send buffer is empty. If the send buffer still has unacknowledged/unsent data, you don't send the FIN packet until the send buffer is empty.
