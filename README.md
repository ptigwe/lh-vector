lh-vector
=========

The Lemke Howson algorithm simulated with the use of covering vectors.

Changes:
============
- Added the functionality to compute all equilibrium reachable from the
  artificial equilibrium. The final output shows the number of equilibria
  which were discovered, after which it displays all the negative indexed
  equilibria along with the number of the positive indexed equilibria which
  it is linked to with a given missing label (where the format k->i means 
  the k-th label leads to the i-th positively indexed equilibrium). This 
  is then followed by the list of positively linked equilibria, and the 
  number of the negatively indexed equilibria it is linked to with a given 
  label (same format applies).