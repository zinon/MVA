#!/bin/sh

queue=2nd

# l1=5; l2=200

#l1=205; l2=400

# l1=405; l2=600

# l1=605; l2=800

# l1=805; l2=1000

l1=1005; l2=1200

# t1=1; t2=200

t1=601; t2=2000

for (( c=$t1; c<$t2; c = c + 2 ))
do
   let j=($c+1)
   echo  bsub  -q $queue -J opt_${c}_${j}_${l1}_${l2} BatchTMVAOptimizationHadHad.sh $c $j $l1 $l2
   
done
