#include<iostream>
#include <ctime>
#include <ratio>
#include <chrono>
using namespace std;

int f(int a, int b){
    int c = a+b;
    return c;
}

int main(){
    const int SIZE = 1000;
    double array[SIZE][SIZE];

    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    for (int col = 0; col < SIZE; col++){
        for (int row = 0; row < SIZE; row++)
            array[row][col] = f(row, col);
    }

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    std::cout << "It took me " << time_span.count() << " seconds.";
    std::cout << std::endl;
    // better order
    high_resolution_clock::time_point t3 = high_resolution_clock::now();

    for (int row = 0; row < SIZE; row++){
        for (int col = 0; col < SIZE; col++)
            array[row][col] = f(row, col);
    }

    high_resolution_clock::time_point t4 = high_resolution_clock::now();

    duration<double> time_span2 = duration_cast<duration<double>>(t4 - t3);

    std::cout << "It took me " << time_span2.count() << " seconds.";
    std::cout << std::endl;

}
