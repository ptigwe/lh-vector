lh-vector
=========

The Lemke Howson algorithm simulated with the use of covering vectors.

Changes:
============
- Added the functionality to compute the first set of positively indexed
  equilibrium from the artificial equilibrium. For each equilibrium that
  is computed, it outputs which of the missing labels links it to the 
  artificial equilibrium. Example 4->0, means the missing label 4 leads to
  the artificial equilibrium, otherwise, 5->-1 means 5 leads to some other
  equilibrium which has not yet been computed.
- A test for dxd dual-cyclic polytopes has been added
  _'test/dualcyclic/dualcyclictest'_ to test the fact that all games which
  fall under this category has a unique equilibrium.
- The input format has also been changed to avoid computing only on equilibrium