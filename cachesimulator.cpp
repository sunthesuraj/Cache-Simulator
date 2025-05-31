// user Defined DS
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
struct CacheLine {
    bool valid;
    unsigned int tag;
    CacheLine() : valid(false), tag(0) {}
};
//Cache Set Representation
class CacheSet {
    public:
        vector<CacheLine> lines;
        unsigned int associativity;
        CacheSet(unsigned int assoc) : associativity(assoc) {
            lines.resize(associativity);
        }
    
        bool access(unsigned int tag) {
            for (int i = 0; i < associativity; ++i) {
                if (lines[i].valid && lines[i].tag == tag) {
                    // Cache hit
                    return true;
                }
            }
            return false; // Cache miss
        }
    
        void insert(unsigned int tag) {
            // Simple LRU replacement: evict the first line
            for (int i = 0; i < associativity - 1; ++i) {
                lines[i] = lines[i + 1];
            }
            lines[associativity - 1].valid = true;
            lines[associativity - 1].tag = tag;
        }
};
//Cache Class
class Cache {
    private:
        unsigned int numSets, blockSize, associativity;
        vector<CacheSet> sets;
        unsigned int hits, misses;
    
    public:
        Cache(unsigned int cacheSize, unsigned int blockSize, unsigned int associativity) 
            : blockSize(blockSize), associativity(associativity), hits(0), misses(0) {
    
            numSets = cacheSize / (blockSize * associativity);
            sets.reserve(numSets);
            for (unsigned int i = 0; i < numSets; ++i) {
                sets.push_back(CacheSet(associativity));
            }
        }
    
        unsigned int getIndex(unsigned int address) {
            return (address / blockSize) % numSets;
        }
    
        unsigned int getTag(unsigned int address) {
            return (address / blockSize) / numSets;
        }
    
        void access(unsigned int address) {
            unsigned int index = getIndex(address);
            unsigned int tag = getTag(address);
    
            if (sets[index].access(tag)) {
                ++hits;  // Cache hit
            } else {
                ++misses;  // Cache miss
                sets[index].insert(tag);
            }
        }
    
        void printStats() {
            unsigned int total = hits + misses;
            double hitRate = (total == 0) ? 0.0 : (double)hits / total * 100;
          cout << "Total Accesses: " << total << "\n";
            cout << "Hits: " << hits << "\n";
            cout << "Misses: " << misses << "\n";
            cout << "Hit Rate: " << hitRate << "%\n";
        }
    };
//Main Function to Simulate Cache

int main() {
    unsigned int cacheSize = 16 * 1024;  // 16KB cache
    unsigned int blockSize = 64;         // 64 Bytes per block
    unsigned int associativity = 4;      // 4-way set associative

    Cache cache(cacheSize, blockSize, associativity);

    ifstream traceFile("trace.txt");
    string line;
    while (getline(traceFile, line)) {
        istringstream iss(line);
        char op;
        unsigned int address;

        if (iss >> op >> hex >> address) {
            cache.access(address);
        }
    }

    cache.printStats();
    return 0;
}

    