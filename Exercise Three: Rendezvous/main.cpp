/*!
   \mainpage Lab 3 Rendezvous
   \copyright This code is covered by the GNU general public license v3.0
   \author Molin Sun and Joseph
   \date 12/11/2020
*/
#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <chrono>

/*! \class Signal
    \brief An Implementation of a Rendezvous using Semaphores

   Uses C++11 features such as mutex and condition variables to implement an example of a rendezvous for threads

*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
/*! \fn void taskOne(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore>  secondSem, int delay)
    \brief This function will print "Task One has arrived!" and "Task One has left!" to screen
    \param firstSem the first semaphore to control the flow
    \param secondSem the second semaphore to control the flow
    \param delay refer to how many second the task will delay

    
    This function will print "Task One has arrived!" firstly. And then after the second semaphore is signaled, it will print "Task One has left".
*/ 
void taskOne(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore>  secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task One has arrived! "<< std::endl;
  firstSem->Wait();
  secondSem->Signal();
  //THIS IS THE RENDEZVOUS POINT!
  std::cout << "Task One has left!"<<std::endl;
}
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
/*! \fn void taskTwo(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore>  secondSem, int delay)
    \brief This function will print "Task Two has arrived!" and "Task Two has left!" to screen
    \param firstSem the first semaphore to control the flow
    \param secondSem the second semaphore to control the flow
    \param delay refer to how many second the task will delay

    
    This function will print "Task Two has arrived!" firstly. And then after the first semaphore is signaled, it will print "Task Two has left".
*/ 
void taskTwo(std::shared_ptr<Semaphore> firstSem, std::shared_ptr<Semaphore> secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task Two has arrived "<<std::endl;
  //THIS IS THE RENDEZVOUS POINT!
  firstSem->Signal();
  secondSem->Wait();
  std::cout << "Task Two has left "<<std::endl;
}

int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem1( new Semaphore);
  std::shared_ptr<Semaphore> sem2( new Semaphore);
  int taskOneDelay=5;
  int taskTwoDelay=1;
  /**< Launch the threads  */
  threadOne=std::thread(taskTwo,sem1,sem2,taskTwoDelay);
  threadTwo=std::thread(taskOne,sem1,sem2,taskOneDelay);
  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();
  return 0;
}
