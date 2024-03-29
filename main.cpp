/*------------------------------------------
 * Name - Ayush Prakash
 * Roll no - CS15BTECH11008
 * Date - 10/02/2017
 * Main Program to show how to use API. 
--------------------------------------------
*/

#include "barrier.h"
#include<iostream>
#include<unistd.h>
#include<cstdlib>
#include<chrono>
#include<thread>
#include<random>
#include<time.h>
#include<fstream>

using namespace std;

//function to test barrier
void BarTest (Barrier *bar, int mean)
{
  ofstream output ("output.txt", ofstream::app);   // Open output file
  
  thread::id thdid = this_thread::get_id();   //Get thread ID

  //Seed according to current time
  int seed = time(NULL);   
  default_random_engine generator(seed);
  //Get exponential distribution
  exponential_distribution<double> distribution (mean);
  double number = distribution(generator);
  chrono::duration<double> period(number);
  //Put to sleep
  this_thread::sleep_for(period);
  
  output<<"Thread before entering barrier: "<<thdid<<"\n";
  output.close();
  bar->barrier_point();
  output.open("output.txt", ofstream::app);
  output<<"Thread after entering barrier: "<<thdid<<"\n";
  output.close();
}

int main()
{
  Barrier bar;
  int n,lambda;
  cout<<"Enter the size of Barrier(N)\n";
  cin>>n;
  cout<<"Enter the average time(lambda)\n";
  cin>>lambda;
  bar.init(n);
  
  thread threads[n];
  
  for(int i=0; i!=n; i++)
    {
      threads[i] = thread(BarTest, &bar, lambda);
    }
  
  for(int i=0; i!=n; i++)
    {
      threads[i].join();
    }
  
  return 0;
}

