for i in {9..1000}
  do
  next=$(( $i + 1 ))
  sed "661s/NTrees=$i/NTrees=$next/" -i TMVAClassification.C
  ${ROOTSYS}/bin/root -l -b <<EOF
.x TMVAClassification.C("BDT") > tmp.txt
EOF
  echo "NTress =  $next" >> tmp2.txt
  grep -A 13 'Evaluation results' tmp.txt >> tmp2.txt
done

rm tmp.txt
