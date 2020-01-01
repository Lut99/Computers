/* TEST_BUFFER.cpp
*    by tHE iNCREDIBLE mACHINE
*
*  A test file for Buffer.cpp.
**/

#include <iostream>
#include <pthread.h>
#include <chrono>
#include <thread>

#include "../lib/Buffer.cpp"

using namespace std;
using namespace DataTypes;

/* Struct for the thread arguments. */
struct ThreadArgs {
    pthread_t id;
    Buffer<int> *buffer;
    bool done;
};

/* Generates a stream of numbers and pushes this to the thread. Notifies the user when it writes. Will have a hiccup (sleep) while writing somewhere down the line. */
void *thread_1(void *arg) {
    cout << "  Created thread 1" << endl;
    cout.flush();

    Buffer<int> *buff = ((ThreadArgs*) arg)->buffer;

    for (int i = 0; i < 50; i++) {
        // Do a sleep somewhere
        if (i == 6) {
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }

        // Wait until we can write
        while (!buff->write(i)) {}

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    cout << "  Thread 1 is finished." << endl;
    cout.flush();

    ((ThreadArgs*) arg)->done = true;

    return NULL;
}
/* Reads a stream of numbers and pushes that to the stdout. Will have a hiccup (sleep) while reading somewhere down the line. */
void *thread_2(void *arg) {
    cout << "  Created thread 2" << endl;
    cout.flush();

    Buffer<int> *buff = ((ThreadArgs*) arg)->buffer;

    for (int i = 0; i < 50; i++) {
        // Do a longer sleep somewhere else
        if (i == 22) {
            std::this_thread::sleep_for(std::chrono::seconds(20));
        }
        
        // Wait until we can read
        int result = -1;
        if (!buff->read(result)) {
            //cout << "Thread 2 is waiting..." << endl;
            while (true) {
                bool can_continue = buff->read(result);
                //cout << "Can we continue? " << can_continue << endl;
                if (can_continue) {
                    break;
                }
            }
            //cout << "Thread 2 is done waiting." << endl;
        }
        // Read to the cout

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    cout << "  Thread 2 is finished." << endl;
    cout.flush();

    ((ThreadArgs*) arg)->done = true;

    return NULL;
}

bool test_drawing() {
    cout << "Testing normal use case (outputting drawing)..." << endl;

    cout << "  Initializing buffer..." << endl;
    Buffer<int> buffer = Buffer<int>(16);

    cout << "  Creating first test thread..." << endl;
    ThreadArgs args1;
    args1.buffer = &buffer;
    args1.done = false;
    pthread_create(&args1.id, NULL, thread_1, (void*) &args1);

    cout << "  Creating second test thread..." << endl;
    ThreadArgs args2;
    args2.buffer = &buffer;
    args2.done = false;
    pthread_create(&args2.id, NULL, thread_2, (void*) &args2);

    // Let the two threads join
    while (!args1.done || !args2.done) {
        cout << buffer.to_string() << endl << "-------------------" << endl << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    pthread_join(args1.id, NULL);
    pthread_join(args2.id, NULL);

    cout << "Success" << endl;

    return true;
}

/* Generates a stream of numbers and pushes this to the thread. Notifies the user when it writes. Will have a hiccup (sleep) while writing somewhere down the line. */
void *thread_1_2(void *arg) {
    cout << "  Created thread 1" << endl;
    cout.flush();

    Buffer<int> *buff = ((ThreadArgs*) arg)->buffer;

    for (int i = 0; i < 64; i++) {
        // Wait until we can write
        while (!buff->write(i)) {}
    }
    cout << "  Thread 1 is finished." << endl;
    cout.flush();

    ((ThreadArgs*) arg)->done = true;

    return NULL;
}
/* Reads a stream of numbers and pushes that to the stdout. Will have a hiccup (sleep) while reading somewhere down the line. */
void *thread_2_2(void *arg) {
    cout << "  Created thread 2" << endl;
    cout.flush();

    Buffer<int> *buff = ((ThreadArgs*) arg)->buffer;

    int *results = new int[64];
    for (int i = 0; i < 64; i++) {
        // Wait until we can read
        int result = -1;
        while (!buff->read(result)) {}

        // Store the values
        results[i] = result;
    }
    cout << "  Thread 2 is finished." << endl;
    cout.flush();

    ((ThreadArgs*) arg)->done = true;

    return (void*) results;
}

bool test_values() {
    cout << "Testing normal use case (outputting numbers)..." << endl;

    cout << "  Initializing buffer..." << endl;
    Buffer<int> buffer = Buffer<int>(16);

    cout << "  Creating first test thread..." << endl;
    ThreadArgs args1;
    args1.buffer = &buffer;
    args1.done = false;
    pthread_create(&args1.id, NULL, thread_1_2, (void*) &args1);

    cout << "  Creating second test thread..." << endl;
    ThreadArgs args2;
    args2.buffer = &buffer;
    args2.done = false;
    pthread_create(&args2.id, NULL, thread_2_2, (void*) &args2);

    // Let the two threads join
    while (!args1.done || !args2.done) {
        //cout << buffer.to_string() << endl << "-------------------" << endl << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    pthread_join(args1.id, NULL);
    void *v_results;
    pthread_join(args2.id, &v_results);
    int *results = (int *) v_results;

    // Show the results
    for (int i = 0; i < 64; i++) {
        cout << "Result: " << results[i] << endl;
    }

    // dealloc
    delete[] results;

    cout << "Success" << endl;

    return true;
}


int main() {
    cout << endl << "### TEST for \"Instruction.cpp\" ###" << endl << endl;
    //test_drawing();
    test_values();
}