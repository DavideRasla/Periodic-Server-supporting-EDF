	Tools for (Hierarchical) Schedulability Analysis

This is a short and informal description of the tools used in the
Component Based Software Design course, for schedulability analysis
(of fixed-priority real-time tasks).
The tools can be downloaded from http://retis.santannapisa.it/~luca/CBSD.

To use the tools, enter the "Analysis" directory (as you already did, since
you are reading this file!) and build the analysis tools by typing "make".
You can now use:
   - sbf_test to print the supplied bound function for a periodic server
     with given parameters
   - tda_test to check the schedulability of a taskset (see the examples
     in "TSs") with a fixed priority scheduler. The program prints a lot
     of information about the scheduling points, the demand bound function
     (workload) for each task in the various points, etc...
   - h_test to check the schedulability of a taskset with a periodic server
     having the specified parameters.

Some exercises for you:
1) Try to plot the sbf for a periodic server; then, use sbf_test to
   generate it and compare your plot with the output of sbf_test.
   Hint: you can use "./sbf_test 8 12 > sbf_8_12.txt" to save the
   sbf of an (8,12) periodic server in "sbf_8_12.txt", and you can
   use gnuplot ("plot 'sbf_8_12.txt'") to plot it.
   Try with different values of Qs and Ts.
2) Check the schedulability of various tasksets. Compare your
   analysis with the results printed by tda_test
3) Check the schedulability of the previous tasksets with a periodic
   server having various parameters. Compare your analysis with the
   results printed by h_test
) Write a simple script (or program) that given a tasksets checks its
  schedulability with a periodic server having various parameters,
  printing the values (Qs,Ts) that make the taskset schedulable
