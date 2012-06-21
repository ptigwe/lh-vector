lh-vector
=========

The Lemke Howson algorithm simulated with the use of covering vectors.

Changes:
============
- Added tests for the paths for the 6x6 cyclic polytope, with the missing
  labels 1 _'path/path-input'_ and 12 _'path/path-input12'_

- Modified the _'path/gen-path'_ script, the generated path for each of the
  labels is stored in _'path/lh-inputk'_, where k is either 1 or 12, and the
  output from _'../inlh -i'_ is stored in _'path/lh-outputk'_