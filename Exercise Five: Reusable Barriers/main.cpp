/*!
   \mainpage Lab 4 Reusable Barriers
   \copyright This code is covered by the GNU general public license v3.0
   \author Molin Sun and Joseph
   \date 19/11/2020
*/
#include "Barrier.h"
#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 10;
int sharedVariable=0;
int count = 0;


/*
void barrierTask(std::shared_ptr<Barrier> theBarrier, int numLoops){

  for(int i=0;i<numLoops;++i){
    //Do first bit of task
    std::cout << "A"<< i;
    //Barrier
    theBarrier.wait();
    //Do second half of task
    std::cout<< "B" << i;
  }
  

}
*/

/*! \fn barrierTask(std::shared_ptr<Semaphore> mutexSem, std::shared_ptr<Semaphore> first, std::shared_ptr<Semaphore> second, int numUpdates)
    \brief This function create a resuable barrier class to control threads

    displays a message that is split in to 2 sections to show how a rendezvous works between N threads.

*/ 
void barrierTask(std::shared_ptr<Semaphore> mutexSem, std::shared_ptr<Semaphore> first, std::shared_ptr<Semaphore> second, int numUpdates){

 
  for(int i=0;i<numUpdates;i++){
    //first 
    std::cout << "1";
    mutexSem->Wait();
    count++;
    if (count == num_threads){
      second->Wait();
      first->Signal();
    }
    mutexSem->Signal();
    //wait print out "1"
    first->Wait();
    first->Signal();
    //second
    std::cout << "2";
    mutexSem->Wait();
    count--;
    if (count == 0){
      
      first->Wait();
      second->Signal();

    }
    mutexSem->Signal();
    //wait print out "2"
    second->Wait();
    second->Signal();
  }

}

int main(void){
  std::vector<std::thread> vt(num_threads);
  //std::shared_ptr<Barrier> aBarrier( new Barrier(num_threads));
  std::shared_ptr<Semaphore> mutexSem(new Semaphore(1));
  std::shared_ptr<Semaphore> first(new Semaphore(0));
  std::shared_ptr<Semaphore> second(new Semaphore(1));
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(barrierTask,mutexSem,first,second,2);
  }
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  //std::cout << sharedVariable << std::endl;
  return 0;
}
