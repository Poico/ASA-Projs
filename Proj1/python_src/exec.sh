for i in $(seq 1 100); do echo "----" $i;
    g++ -std=c++11 -O3 -Wall -o gen_supermarble gen_supermarble.cpp -lm;
    time
    g++ -std=c++11 -O3 -Wall file.cpp -lm
    ./a.out < supermarble.in > supermarble.out
    done
