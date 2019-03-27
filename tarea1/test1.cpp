#include<iostream>
#include <ctime>
#include <ratio>
#include <chrono>
using namespace std;

const int Size = 64500;
static volatile int array[Size];
int Iterations = 1000;
//65536

static void test_function(void)
{
    for (int i = 0; i < Iterations; i++){
        for (int x = 0; x < Size; x++)
          array[x]++;
    }
}

int main(){
    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    test_function();

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    std::cout << "It took me " << time_span.count() << " seconds.";
    std::cout << std::endl;
    
}
