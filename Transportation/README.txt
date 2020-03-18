                              AUM SRI SAI RAM

Transportation Algorithm Implementation:

AIM:
      To find the optimum cost of transportation(Transfer b/w given sources and destinations).

INPUT:
      Number of sources(m), Number of destinations(n),
      Cost of tranportation from source i to destination j,
      Total availability at source i,
      Total availability at destination j.

      Input is taken from the file in the following manner:

      |m n            |
      |c c c .... c  S|
      |c c c .... c  S|
      |: : : .... :  :|
      |: : : .... :  :|
      |: : : .... :  :|
      |: : : .... :  :|
      |c c c .... c  S|
      |D D D .... D  D|



IMPLEMENTATION:
               [SOME FUNCTIONS]:
                    


OUTPUT:
       The program outputs:
       1. The modified tableu at each iteration
              Each tableau consists of quantity, cost, basic/nonbasic information for each of the possible routes (ie. source i to destination j).
       2. The Final Tableu
              Final tableu consists of the quantity to be supplied from source i to destination j, for each i,j.
       3. The Final cost:
              It is the cost of tranportation if the supplied quantities are as shown in the previous tableau.
