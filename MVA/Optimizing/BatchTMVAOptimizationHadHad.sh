#!/bin/sh

cd /afs/cern.ch/work/z/zenon/Physics/Higgs/HSG4/software/hadhad/MultiVariateAnalysis/MVA/Optimizing

echo "starting at "${PWD}

source setup_root.sh

echo "root version "; which root

mkdir -p /tmp/weights

chmod -R 777 /tmp/weights

mkdir -p /tmp/OptClass

chmod -R 777 /tmp/OptClass

root.exe -b -q -l "RunTMVAOptimizationHadHad.C(\"BDT\", \"$1\", \"$2\", \"$3\", \"$4\")"