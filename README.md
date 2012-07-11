lh-vector
=========

The Lemke Howson algorithm simulated with the use of covering vectors.

Changes:
============
- Added comments to the .c and .h files.

Compiling:
============
- The program can be compiled using two make rules _'make inglh'_ which
  makes use of the GNUMP library, and _'make inlh'_ which makes use of a
  predefined multiple precision library _'mp.h'_ .
- The programs for needed for testing can be compiled using _'make subdir'_.
- The _'labelstest'_ script runs the program for all possible values of the
  missing label given the maximum value of k and uses the game stored in 
  _'sample-input'_