# Extension of a schedulability analysis tool for dynamic priority and check results using KVM environment



This project aims to analyse all the procedures that led to the implementation of a schedulability
checker under both fixed and dynamic priority. Moreover the tool proposed is able to find the optimal
parameters Q an P able to perform a Supplied Bound Function [sbf()] that schedule a component
with his related Demanded Bound Function [dbf()].

A component in this experiment is intended to be a Taskset and the experiment aims to
check various Tasksets with different utilizations with the final goal to do a comparision between
EDF and RM. As final step, in the last section is shown a practical example of schedule with the
founded values using QEMU as virtual environment that runs all the tasks in the taskset acting as a
component scheduled by the host following the values Q and P found by the tool.

# Features!

This tool:

* Using ‘taskgen.py’, generates 10 random taskset composed by N tasks, with utilization from
0.1 to 0.8, inside the folder 'TaskSets'. So creates 10 tasksets with utilization 0.1, another 10
tasksets with utilization 0.2 and so on...;
* For each taskset and for each utilization check the schedulability under RM and EDF with a
periodic server saving the values (Qs,Ts) that make the taskset schedulable into two folders,
'Results_EDF' and 'Results_RM', that contain a file .txt for each utilization with all the
results;
* Using ‘Plot_Graph.py’ calculates the average value for all tasksets for each utilization and
plot the comparison between RM and EDF in a graph.
The experiment can be started using ‘Experiment.sh’.
The folder ‘src’ contains all the code used to implement ‘h_design’ and ‘h_design_RM’
The folder ‘KVM’ contains all the necessary to check the results usin QEMU.

‘Create_My_Test_gz.sh’ a new images test.gz containing the environment and the new taskset
created using ‘Experiment.sh’. Using the script it easy to generate taskset and deploy them
immoderately inside KVM without any manual copy-past.
Note: In the folder is available a file ‘Tree_Structure.txt’ where is described each folder and each
file.
Additional features:
I performed an additional feature in tda_test that now checks the schedulability of a taskset
with both fixed and dynamic priority scheduler, using the Process Demand Critereon for the latter.
Inside the folder ‘./tda_test_extended’ is available the executable and an example of taskset which is
not schedulable under RM, but only under EDF.
The test can be launched in the standard way using
$ /tda_test ts3.txt

### Installation and how to use

**This tool requires Python 3 to run.**

There are two ways to run the experiment. If Experiment.sh is launched with an integer N, with N > 1 as
first argument, it generates inside a directory called 'TaskSets', 8 sub-directories, one for each utilization.
Each directory contains 10 file .txt containing N tasks. For instance:
```sh
$ sh Experiment.sh 5
```

Creates 8 sub-directories with 10 tasksets composed by 5 tasks, in each of them.
Otherwise if the experiment is lunched with ‘0’ or ‘ 1’ as argument, it just plots the average results
using the saved tasksets. For instance:
```sh
$ sh Experiment.sh 0
```
```sh

### Todos

 - Empty 
 

License
----

MIT
