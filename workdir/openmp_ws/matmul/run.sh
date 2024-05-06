#!/bin/sh
T1='o0'
T2='o2'
T3='openmp'
T4='loop_unrolling'
T5='blocking'
T6='loop_unrolling_and_blocking'



# echo "--- ${T1} ---"
# ./${T1}
echo "--- ${T2} ---"
./${T2}
echo "--- ${T3} ---"
./${T3}
echo "--- ${T4} ---"
./${T4}
echo "--- ${T5} ---"
./${T5}
echo "--- ${T6} ---"
./${T6}
