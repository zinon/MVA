#!/bin/sh

categ=$1

root -b -l << EOF
gSystem->Load("ApplicationClass_C.so")
ApplicationClass t
t.Loop("A", "$categ")
EOF

