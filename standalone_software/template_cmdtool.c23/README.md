# Template commandline tool
This is a template for commandline programs. This means it has a commandline argument parser and a simple operation to do on files. This is a template to interact with files.
## build instructions
To build: ```make```
To cleanup: ```make clean```
To execute ```make run```
To run clang tidy ```make check```
There are also unittests in tests.mak and can be run in the same way as the normal build instructions but run it as ```make -ftests.mak``` with your target of choice like all, clean, run, or check.
