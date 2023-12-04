for file in tests_gen_left/teste_*.txt; 
    do echo "-----------------------"; 
    echo $file >> time_tests.txt; 
    { time cpp_src/a.out < $file; } 2>> time_tests.txt; 
done
