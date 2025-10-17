#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <cstring>
#include <cstdlib>
using namespace std;

// ---------------- GLOBAL VARIABLES ----------------
vector<int> histogram(1001, 0);  // Frequency of stopping times (0–1000)
int COUNTER = 1;                 // Shared counter for next number
int N;                           // Upper limit of range
int T;                           // Number of threads
bool useLock = true;             // Control locking mode

mutex mtx;                       // Global mutex

// ---------------- FUNCTION: Compute Collatz stopping time ----------------
int collatzStoppingTime(long long n) {
    int count = 0;
    while (n != 1) {
        n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
        count++;
        if (count > 1000) break; // Prevent overflow in histogram
    }
    return count;
}

// ---------------- FUNCTION: Get next number safely ----------------
bool getNextNumber(int &num) {
    if (useLock) {
        lock_guard<mutex> lock(mtx);
        if (COUNTER > N) return false;
        num = COUNTER++;
    } else {
        if (COUNTER > N) return false;
        num = COUNTER++;
    }
    return true;
}

// ---------------- FUNCTION: Worker thread ----------------
void worker() {
    int num;
    while (getNextNumber(num)) {
        int stopTime = collatzStoppingTime(num);
        if (stopTime <= 1000) {
            if (useLock) {
                lock_guard<mutex> lock(mtx);
                histogram[stopTime]++;
            } else {
                histogram[stopTime]++; // Unsafe when -nolock used
            }
        }
    }
}

// ---------------- MAIN FUNCTION ----------------
int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: ./mt-collatz N T [-nolock]" << endl;
        return 1;
    }

    N = atoi(argv[1]);
    T = atoi(argv[2]);
    if (argc == 4 && strcmp(argv[3], "-nolock") == 0)
        useLock = false;

    // ---------------- TIME START ----------------
    auto start = chrono::high_resolution_clock::now();

    // ---------------- CREATE THREADS ----------------
    vector<thread> threads;
    for (int i = 0; i < T; i++)
        threads.emplace_back(worker);

    for (auto &th : threads)
        th.join();

    // ---------------- TIME END ----------------
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    // ---------------- PRINT HISTOGRAM ----------------
    for (int i = 0; i <= 1000; i++)
        cout << i << "," << histogram[i] << endl;

    // ---------------- PRINT TIME TO STDERR ----------------
    cerr << N << "," << T << "," << elapsed.count() << endl;

    return 0;
}