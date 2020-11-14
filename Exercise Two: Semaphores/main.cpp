/*!
   \mainpage Lab 2 Semaphores
   \copyright This code is covered by the GNU general public license v3.0
   \author Molin Sun and Joseph
   \date 12/11/2020
*/
#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <unistd.h>
/*! \class Signal
    \brief An Implementation of Threads Using Semaphores 

   Uses C++11 features such as mutex and condition variables to implement Semaphores in thread functions 

*/
/*! displays a message first*/
/*! \fn void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay)
    \brief This function will print "I must print first" to screen
    \param delay refer to how many second the task will delay
    \param theSemaphore use to control the flow

    This function will print "I must print first" to the screen after the delay.
    And we will use semaphore to control the flow to make sure tasks can execute in correct order 
*/ 
void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay){
  sleep(delay);
  std::cout <<"I ";
  std::cout << "must ";
  std::cout << "print ";
  std::cout << "first"<<std::endl;
  theSemaphore->Signal();
}
/*! displays a message second*/
/*! \fn void taskTwo(std::shared_ptr<Semaphore> theSemaphore)
    \brief This function will print "I will apear second" to screen
    \param theSemaphore use to control the flow
    
    This function will print "I must print first" to the screen after semaphore is signaled.
    And we will use semaphore to control the flow to make sure tasks can execute in correct order 
*/ 
void taskTwo(std::shared_ptr<Semaphore> theSemaphore){
  theSemaphore->Wait();
  std::cout <<"This ";
  std::cout << "will ";
  std::cout << "appear ";
  std::cout << "second"<<std::endl;
}


int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem( new Semaphore(0));
  /**< Launch the threads  */
  int taskOneDelay=5;
  threadOne=std::thread(taskTwo,sem);
  threadTwo=std::thread(taskOne,sem,taskOneDelay);
  std::cout << "Launched from the main\n";
   /**< Wait for the threads to finish */
  threadOne.join();
  threadTwo.join();
  return 0;
}
