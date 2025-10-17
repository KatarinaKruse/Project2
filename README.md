🧮 Multithreaded Collatz Project
📘 Overview

This project implements a multithreaded Collatz stopping-time calculator.
It computes the Collatz stopping time for every integer from 1 up to a given number N, using T parallel threads.
The program supports two modes:

Locked mode (default): uses a mutex to safely update shared data.

No-lock mode (-nolock): skips synchronization for performance testing.

Results are printed as a CSV histogram to standard output (stdout),
and the runtime (in seconds) is printed to standard error (stderr).

⚙️ Compilation Instructions

To compile the program, simply run:
make

This will create the executable mt-collatz using g++ with threading support.

If you ever need to rebuild from scratch, use:
make clean

🚀 Running the Program

The general usage format is:
./mt-collatz N T [-nolock]
N: the upper limit of integers to test (e.g., 10000)

T: the number of threads to run (e.g., 4)

-nolock (optional): disables locking to test unsafe multithreading performance

Example commands:
./mt-collatz 10000 4 > histogram_locked.csv 2> timing_locked.csv
./mt-collatz 10000 4 -nolock > histogram_nolock.csv 2> timing_nolock.csv

The first command runs the locked version, saving:

The histogram (frequency of stopping times) to histogram_locked.csv

The timing results (N, T, total runtime) to timing_locked.csv

The second command runs the no-lock version for comparison.

📊 Output Details
Histogram CSV (stdout)

Each line represents a stopping time and its frequency:
stopping_time,frequency

Example:
0,0
1,1
2,2
3,5
...

Timing CSV (stderr)

Contains one line with three values:
N,T,seconds

Example:
10000,4,0.0937

💻 Excel Report Instructions

To create an Excel report from the program outputs:

Run both locked and no-lock versions of the program to generate CSV files:

histogram_locked.csv

histogram_nolock.csv

timing_locked.csv

timing_nolock.csv

Open Microsoft Excel or Google Sheets.

Import histogram CSV files into separate sheets.

Create bar charts or line charts comparing frequencies of stopping times.

Create another chart comparing execution times from the timing files.

Label all charts and provide analysis comparing:

Locked vs. no-lock performance

Different thread counts, if multiple values of T are tested

🧠 Discussion Points

Race conditions and the importance of locking for shared variables.

Performance differences between locked and no-lock modes.

How increasing thread count affects runtime efficiency.

Accuracy and consistency of results in different modes.

🧰 File List

mt-collatz.cpp — main program source code

Makefile — builds and cleans the project

histogram_locked.csv, histogram_nolock.csv — output data for Excel

timing_locked.csv, timing_nolock.csv — timing results for performance comparison

README.md — this file, containing setup and report instructions