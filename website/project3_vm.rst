Project 3 VM
==============


http://mirror.cs.uchicago.edu/techstaff/cs121-aut-15-final.ova

https://www.classes.cs.uchicago.edu/archive/2015/fall/12100-1/install-guide/index-download.html

Except:

- Download latest version (not 5.0.4 specifically)

OS X

- Skip steps 8, 9, 16-

Windows

- Skip 7, 8, 14-


On an Internet-connected machine

sudo apt-get update
sudo apt-get install traceroute

git clone https://github.com/uchicago-cs/chirouter-reference.git
git clone https://github.com/mininet/mininet.git

cd mininet/
git checkout -b 2.2.1 2.2.1
util/install.sh -nfv


If you're going to use VM purely as mininet machine:

Switch to Host mode.

- File -> Preferences -> Network -> Host-only Networks
- Click on the plus icon.

On the bottom left corner, right click on the Network icon (
the
two computer icons). Or, right click, Settings -> Network.

Attached to: Host-only Adapter.

Note: You may need to restart your networking (on the VM, click
on the Ubuntu network icon on the top right corner, click on "Wired connection 1").
If that doesn't work, restart the VM.

sudo stop network-manager
sudo ifconfig eth0 up
sudo dhclient eth0

ifconfig eth0

Address will likely be an address like 192.168.56.101. Verify that
you can ping it from your host address.




