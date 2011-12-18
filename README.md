RiverModel written in CPython - Version 1.0.0
===================================

Purpose
-------

RiverModel is a simulator for the carbon flow in the Mississippi river. The first model was written in NetLogo(see http://ccl.northwestern.edu/netlogo/) and
it took 4.5 days to simulate a year of carbon flow in the river. The goal of this project is to reduce the runtime to ~1 hour while preserving the same functionalities.
We are implementing the new version in C and using Python for the user interface. The current version takes ~10 hours to simulate a year long of carbon flow.

Table of Contents
-----------------

* [Requirements](#requirements)
* [Running the Model](#running)
* [Implementation](#implementation)
* [Testing](#testing)
* [Team](#team)

<a name="requirements"/>
Requirements
------------

You will need Python2.7(http://www.python.org/getit/releases/2.7/), gcc (http://gcc.gnu.org/) and C to run/modify the model.
We are also using the libaries:
  * Python Imaging Library: http://www.pythonware.com/products/pil/
  * Jython: http://www.jython.org/

<a name="running"/>
Running the Model
-----------------

You can run the model as follows:
  $ pwd
  $ /Users/efekarakus/USGS
  $ cd main/model/
  $ make
  $ cd ../
  $ python main.py

<a name="implementation"/>
Implementation
--------------

<a name="testing"/>
Testing
-------

<a name="team"/>
Team
----
  * Efe Karakus: efekarakus@gmail.com
  * Nathan DeGrand: degrand1@illinois.edu
  * Tom Loboda: loboda1@illinois.edu
  * Chris Freund: freund3@illinois.edu
