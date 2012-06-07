lh-vector
=========

The Lemke Howson algorithm simulated with the use of covering vectors.

Changes:
============
- Rational numbers consist of multiple precision (mp.h) numbers for its
  numerator and denominator.
- Minor adjustments were made to Lemke's algorithm (lemke.h), and the
  Lemke-Howson algorithm (inlemkehowson.c) as well to compensate
  for the above change.

Test:
=========
- The above changes were also tested with the previous version of the
  program, and confirmed that they both gave the same results.