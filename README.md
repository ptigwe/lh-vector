lh-vector
=========

The Lemke Howson algorithm simulated with the use of covering vectors.

Changes:
============
- Added _'./path/path'_ program, which converts the given Lemke-Howson path to
  an equivalent path for Lemke's algorithm on the LCP. This takes as
  input, the size of the game (m and n), followed by the sequence of
  labels. See _'./path/path-input'_ for an example.
- Added _'./path/gen-path'_, which uses the path program to generate an input
  for the _'./inlemkehowson'_ program. This program assumes that the path
  in the file _'./path/path-input'_ is the path for the game in _'./sample-input'_.
  Once the path has been converted, it stores it in _'./path/path-output'_ and 
  concatenates it with _'./sample-input'_, storing the resulting output in
  _'./path/lh-input'_ which is then passed as input to _'./inlh -i'_