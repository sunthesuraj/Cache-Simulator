# Cache Simulator

This is a simple C++ program that simulates the behavior of a set-associative CPU cache. It reads memory access traces from a file and provides statistics on cache hits and misses.

## Features

- Set-associative cache simulation
- Configurable cache size, block size, and associativity
- Simple LRU (Least Recently Used) replacement policy
- Processes input from a trace file (`trace.txt`)
- Prints summary statistics of cache performance

## Project Structure

- `cachesimulator.cpp`: Main source code implementing the cache simulation
- `trace.txt`: Input file (must be placed in the same directory), containing memory access patterns in the form:
  ```
  R 0x1a2b3c
  W 0x4d5e6f
  ```

## How It Works

1. The cache is initialized with:
   - Cache Size: 16KB
   - Block Size: 64 Bytes
   - Associativity: 4-way set associative

2. Each line in `trace.txt` represents a memory access:
   - The first character indicates a read (`R`) or write (`W`)
   - The second part is the memory address (in hexadecimal)

3. The simulator processes each access and tracks hits and misses.

4. At the end, it outputs:
   - Total accesses
   - Number of hits
   - Number of misses
   - Hit rate percentage

## Compilation

Use a C++ compiler like `g++` to compile the project:

```bash
g++ cachesimulator.cpp -o cachesimulator
```

## Usage

Make sure you have a `trace.txt` file in the same directory. Then run:

```bash
./cachesimulator
```

## Example Output

```
Total Accesses: 1000
Hits: 750
Misses: 250
Hit Rate: 75.00%
```

## License

This project is open-source and available under the MIT License.
