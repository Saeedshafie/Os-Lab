package com.techvidvan.semaphore;
import java.util.concurrent. * ;


class SharedResource {
  static int count = 0;
}

class MyThread extends Thread {
  Semaphore semaphore;
  String threadName;
  public MyThread(Semaphore semaphore, String threadName) {
    super(threadName);
    this.semaphore = semaphore;
    this.threadName = threadName;
  }@Override
  public void run() {
    if (this.getName().equals("Thread1")) {
      System.out.println("Starting " + threadName);
      try {
        // get a permit.
        System.out.println(threadName + " is waiting for a permit.");

        //Acquire the lock
        semaphore.acquire();

        System.out.println(threadName + " gets a permit.");

        // Access
        // other waiting threads will wait
        for (int i = 0; i < 5; i++) {
          SharedResource.count++;
          System.out.println(threadName + ": " + SharedResource.count);

          //Allowing a context switch if possible.for thread B to execute
          Thread.sleep(10);
        }
      }
      catch(InterruptedException exc) {
        System.out.println(exc);
      }

      // Release the permit.
      System.out.println(threadName + " releases the permit.");
      semaphore.release();
    }

    // Run by thread B
    else {
      System.out.println("Starting " + threadName);
      try {
        // get a permit.
        System.out.println(threadName + " is waiting for a permit.");

        // acquiring the lock
        semaphore.acquire();

        System.out.println(threadName + " gets a permit.");

        // Now, accessing the shared resource.
        // other waiting threads will wait.
        for (int i = 0; i < 5; i++) {
          SharedResource.count--;
          System.out.println(threadName + ": " + SharedResource.count);

          Thread.sleep(10);
        }
      }
      catch(InterruptedException exc) {
        System.out.println(exc);
      }
      // Release the permit.
      System.out.println(threadName + " releases the permit.");
      semaphore.release();
    }
  }
}
//Main
public class SemaphoreDemo {
  public static void main(String args[]) throws InterruptedException {

    Semaphore semaphore = new Semaphore(1);


    MyThread t1 = new MyThread(semaphore, "Thread1");
    MyThread t2 = new MyThread(semaphore, "Thread2");

    t1.start();
    t2.start();

    // wait
    t1.join();
    t2.join();

    //count will always be 0 after both threads complete their execution
    System.out.println("count: " + SharedResource.count);
  }
}