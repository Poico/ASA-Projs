for i in $(seq 50000 100 100000); 
    do echo $i;
	   ./gen_tuganet $i $i 100 1 1000 > tests/testfile$i 
done

for file in tests/testfile*; 
    do echo "-----------------------"; 
    echo $file >> time_tests.txt;
    { time ./grafos_covid < $file; } 2>> time_tests.txt; 
done