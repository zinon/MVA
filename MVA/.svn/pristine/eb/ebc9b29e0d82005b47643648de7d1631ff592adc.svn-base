#These lines change the values of NTrees, nEventsMin and MaxDepth to the starting or default values for this script to work. 
Start_NTrees=40
Start_nEventsMin=39
Start_MaxDepth=200000
sed "71s/.*/        string  BDT_NTrees              = \"$Start_NTrees\";/" -i TMVAClassificationHadHad3.C
sed "72s/.*/        string  BDT_nEventsMin          = \"$Start_nEventsMin\";/"  -i TMVAClassificationHadHad3.C
sed "73s/.*/        string  BDT_MaxDepth            = \"$Start_MaxDepth\";/" -i TMVAClassificationHadHad3.C
for i in $(seq $Start_NTrees 42)
  do
  next_t=$(( $i + 1 ))
  sed "71s/BDT_NTrees              = \"$i\"/BDT_NTrees              = \"$next_t\"/" -i TMVAClassificationHadHad3.C
  for j in $(seq $Start_nEventsMin 100 1939)
    do
    next=$(( $j + 1 ))
    sed "72s/BDT_nEventsMin          = \"$j\"/BDT_nEventsMin          = \"$next\"/" -i TMVAClassificationHadHad3.C
    #sed "73s/BDT_MaxDepth            = \"$j\"/BDT_MaxDepth            = \"$next\"/" -i TMVAClassificationHadHad3.C ## uncomment this line to and comment out the line above to change between neventsmin and maxdepth.Also change line 12 (for j in...) to $MaxDepth. Or vice versa.
   ${ROOTSYS}/bin/root -l -b <<EOF
.x TMVAClassificationHadHad3.C > tmp.txt
EOF
    echo "NTrees =  $next_t" >> tmp_HadHad3.txt
    echo "nEventsMin =  $next" >> tmp_HadHad3.txt
  
    grep -A 13 'Evaluation results' tmp.txt >> tmp_HadHad3.txt
  done
  sed "72s/BDT_nEventsMin          = \"$next\"/BDT_nEventsMin          = \"Start_nEventsMin/" -i TMVAClassificationHadHad3.C
  #sed "73s/BDT_MaxDepth           = \"$next\"/BDT_MaxDepth            = \"$Start_MaxDepth\"/" -i TMVAClassificationHadHad3.C
done
rm tmp.txt