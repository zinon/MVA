#!/bin/sh

root -b << EOF
 .L mva.C
mva t
t.Loop()
EOF

