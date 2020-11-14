/*!
   \mainpage Lab 4 Mutual Exclusion
   \copyright This code is covered by the GNU general public license v3.0
   \author Molin Sun and Joseph
   \date 12/11/2020
*/
#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 100;
int sharedVariable=0;


/*! \fn void updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates)
    \brief This function will loop i++ untill i=numUpdates
    \param firstSem to control the flow

    This function will print "Task One has arrived!" firstly. And then after the second semaphore is signaled, it will print "Task One has left".
*/ 
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates){

 
  for(int i=0;i<numUpdates;i++){
    //UPDATE SHARED VARIABLE HERE!
    firstSem->Signal();
    sharedVariable++;
    firstSem->Wait();
  }

}


int main(void){
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Semaphore> aSemaphore( new Semaphore(1));
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(updateTask,aSemaphore,1000);
  }
  std::cout << "Launched from the main\n";
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
