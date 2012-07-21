lh-vector
=========

The Lemke Howson algorithm simulated with the use of covering vectors.

Changes:
============
- Modified _'labelstest'_ to automatically compute the total number of labels
  to test.
- Added functionality to compute A<sub>B</sub><sup>-1</sup>.
- Added an extra flag '-a' which outputs the value of the covering vector
  and A<sub>B</sub><sup>-1</sup>.
- Added test files which tests the computation of A<sub>B</sub><sup>-1</sup>
  with the initial covering vector to calculate the value of the z0 column
  in the final tableau. The test file _'test/invAB/invABtest'_ checks that
  for all values of the missing label, the computed value for 
  A<sub>B</sub><sup>-1</sup> is correct.
