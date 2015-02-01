#!/bin/sh

root -b << EOF
.L mva.C
mva t
t.Loop(0)
EOF

