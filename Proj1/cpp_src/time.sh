for file in teste_*.txt; do
    echo "-----------------------"
    echo $file
    echo $file >> tempo3.txt
    { time ./a.out < $file; } 2>> tempo3.txt
done
