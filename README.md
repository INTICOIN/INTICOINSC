INTICOIN CORE
+AD0APQA9AD0APQA9AD0APQA9-

http://www.inticoin.com/

What is INTICOIN?
-------------

INTICOIN is a new blockchain based on Qtum which uses Bitcoin Core and integrates Ethereum based smart contracts. It implements an extensible design which is capable of adding more VMs, enabled primarily through the Account Abstraction Layer, which allows for an account based virtual machine to function on a UTXO based blockchain. 


Quickstart
----------
+ACMAIwAj- Build on Ubuntu

    This is a quick start script for compiling INTICOIN on Ubuntu

    sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils git cmake libboost-all-dev
    sudo apt-get install software-properties-common
    sudo add-apt-repository ppa:bitcoin/bitcoin
    sudo apt-get update
    sudo apt-get install libdb4.8-dev libdb4.8dev

    +ACM- If you want to build the Qt GUI:
    sudo apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler

    git clone https://github.com/INTICOIN/INTICOIN --recursive
    cd INTICOIN

    +ACM- Note autogen will prompt to install some more dependencies if needed
    ./autogen.sh
    ./configure --disable-shared --enable-static 
    make -j2

+ACMAIwAj- Build on OSX

The commands in this guide should be executed in a Terminal application.
The built-in one is located in +AGA-/Applications/Utilities/Terminal.app+AGA-.

+ACMAIwAjACM- Preparation

Install the OS X command line tools:

+AGA-xcode-select --install+AGA-

When the popup appears, click +AGA-Install+AGA-.

Then install +AFs-Homebrew+AF0-(https://brew.sh).

+ACMAIwAjACM- Dependencies

    brew install cmake automake berkeley-db4 libtool boost --c++10- --without-single --without-static miniupnpc openssl pkg-config protobuf qt5 libevent imagemagick --with-librsvg

NOTE: Building with Qt4 is still supported, however, could result in a broken UI. Building with Qt5 is recommended.

+ACMAIwAjACM- Build INTICOIN CORE

1. Clone the INTICOIN source code and cd into +AGA-INTICOIN+AGA-

        git clone --recursive https://github.com/INTICOIN/INTICOIN
        cd INTICOIN

2.  Build INTICOIN CORE:

    Configure and build the INTICOIN binaries as well as the GUI (if Qt is found).

    You can disable the GUI build by passing +AGA---without-gui+AGA- to configure.

        ./autogen.sh
        ./configure
        make

3.  It is recommended to build and run the unit tests:

        make check

+ACMAIwAj- Run

Then you can either run the command-line daemon using +AGA-src/inticoind+AGA- and +AGA-src/inticoin-cli+AGA-, or you can run the Qt GUI using +AGA-src/qt/inticoin-qt+AGA-

For in-depth description of Sparknet and how to use INTICOIN for interacting with contracts, please see +AFs-sparknet-guide+AF0-(doc/sparknet-guide.md).

License
-------

INTICOIN is GPLv3 licensed.

Development Process
-------------------

The +AGA-master+AGA- branch is regularly built and tested, but is not guaranteed to be
completely stable. +AFs-Tags+AF0-(https://github.com/INTICOIN/INTICOIN/tags) are created
regularly to indicate new official, stable release versions of INTICOIN.

The contribution workflow is described in +AFs-CONTRIBUTING.md+AF0-(CONTRIBUTING.md).
