#include <iostream>
#include <unordered_set>
#include <queue>

using namespace std;

// Function to find page faults using FIFO
int pageFaults(int pageReferences[], int numReferences, int capacity) {
    // To represent the set of current pages, using unordered_set for quick lookups
    unordered_set<int> pageSet;

    // To store the pages in FIFO manner
    queue<int> pageQueue;

    // Start from the initial page
    int pageFaultCount = 0;
    for (int i = 0; i < numReferences; i++) {
        // Check if the set can hold more pages
        if (pageSet.size() < capacity) {
            // Insert it into the set if not already present, indicating a page fault
            if (pageSet.find(pageReferences[i]) == pageSet.end()) {
                // Insert the current page into the set
                pageSet.insert(pageReferences[i]);

                // Increment page fault count
                pageFaultCount++;

                // Push the current page into the queue
                pageQueue.push(pageReferences[i]);
            }
        } else {
            // If the set is full, perform FIFO
            if (pageSet.find(pageReferences[i]) == pageSet.end()) {
                // Get the oldest page from the queue
                int oldestPage = pageQueue.front();

                // Pop the oldest page from the queue
                pageQueue.pop();

                // Remove the oldest page from the set
                pageSet.erase(oldestPage);

                // Insert the current page into the set
                pageSet.insert(pageReferences[i]);

                // Push the current page into the queue
                pageQueue.push(pageReferences[i]);

                // Increment page fault count
                pageFaultCount++;
            }
        }
    }

    return pageFaultCount;
}

// Driver code
int main() {
    int pageReferences[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int numReferences = sizeof(pageReferences) / sizeof(pageReferences[0]);
    int capacity = 4;
    cout << "Number of page faults using FIFO: " << pageFaults(pageReferences, numReferences, capacity) << endl;
    return 0;
}

