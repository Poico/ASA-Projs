for i in $(seq 1000 20 5000); 
    do echo $i; 
    ./gen_supermarble $i $i $i > tests_gen/teste_$i.txt; 
done
