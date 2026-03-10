#include <iostream>

// Function demonstrating stack array
void stackArrayExample() {
  std::cout << "\n=== Stack Array Example ===\n";
  int stackArray[5]= {1, 2, 3, 4, 5};

  std::cout << "Stack array created (automatically managed)\n";
  std::cout << "First element: " << stackArray[0] << "\n";

  // No need to delete - automatically cleaned up when function returns
}

// Function demonstrating correct heap array usage
void heapArrayCorrect() {
  std::cout << "\n=== Heap Array - CORRECT Usage ===\n";
  int* heapArray= new int[5];

  for (int i= 0; i < 5; i++) {
    heapArray[i]= i * 10;
  }

  std::cout << "Heap array created and initialized\n";
  std::cout << "First element: " << heapArray[0] << "\n";

  delete[] heapArray;  // CORRECT: using delete[] for array
  std::cout << "Heap array properly deleted with delete[]\n";
}

// Function demonstrating MEMORY LEAK (not deleting)
void heapArrayLeak() {
  std::cout << "\n=== Heap Array - MEMORY LEAK (not deleted) ===\n";
  int* heapArray= new int[5];

  for (int i= 0; i < 5; i++) {
    heapArray[i]= i * 20;
  }

  std::cout << "Heap array created but NOT deleted\n";
  std::cout << "First element: " << heapArray[0] << "\n";

  // BUG: Missing delete[] heapArray;
  // Valgrind will report: "definitely lost: X bytes"
}

// Function demonstrating WRONG delete (using delete instead of delete[])
void heapArrayWrongDelete() {
  std::cout << "\n=== Heap Array - WRONG Delete (delete instead of delete[]) ===\n";
  int* heapArray= new int[5];

  for (int i= 0; i < 5; i++) {
    heapArray[i]= i * 30;
  }

  std::cout << "Heap array created\n";
  std::cout << "First element: " << heapArray[0] << "\n";

  delete heapArray;  // BUG: Should be delete[] for arrays!
                     // Valgrind will report: "Mismatched free() / delete / delete []"
}

// Function demonstrating single object with wrong delete[]
void singleObjectWrongDelete() {
  std::cout << "\n=== Single Object - WRONG Delete (delete[] instead of delete) ===\n";
  int* singleInt= new int(42);

  std::cout << "Single int created: " << *singleInt << "\n";

  delete[] singleInt;  // BUG: Should be delete, not delete[]!
                       // Valgrind will report: "Mismatched free() / delete / delete []"
}

struct Node {
  int data;
  Node* next;
};

void indirectlyLost() {
  std::cout << "\n=== INDIRECTLY LOST ===\n";
  Node* head= new Node{1, nullptr};
  head->next= new Node{2, nullptr};
  head->next->next= new Node{3, nullptr};

  // We lose 'head', so all nodes in the chain are lost
  // Valgrind reports:
  // - definitely lost: X bytes (the head node)
  // - indirectly lost: Y bytes (the next nodes)
}
// PURE "Possibly Lost" - pointer still exists at exit
int* interiorPtr= nullptr;
void purelyPossiblyLost() {
  std::cout << "\n=== PURELY Possibly Lost (interior pointer survives) ===\n";
  int* array= new int[10];
  interiorPtr= array + 5;  // Global pointer keeps interior pointer alive!

  // At exit: interiorPtr points to middle
  // Valgrind: "possibly lost" (has interior pointer, but not to start)
}
void possiblyLost() {
  std::cout << "\n=== POSSIBLY LOST ===\n";
  int* array= new int[10];
  array= array + 5;  // Now points to middle of array!

  // At program exit, 'array' points to middle of block
  // Valgrind: "possibly lost: 40 bytes"
  // (it can't be sure if you can still free it)
}

int* globalPtr= nullptr;

void stillReachable() {
  std::cout << "\n=== STILL REACHABLE ===\n";
  globalPtr= new int[10];

  // Program exits with globalPtr still pointing to memory
  // Valgrind: "still reachable: 40 bytes"
  // Not technically a leak (you could still delete it)
  // but you didn't clean up
}

int main() {
  std::cout << "C++ Stack vs Heap Arrays Demonstration\n";
  std::cout << "=======================================\n";

  // Correct usage
  stackArrayExample();
  heapArrayCorrect();

  // Uncomment these ONE AT A TIME to see different valgrind errors:
  // possiblyLost();
  // stillReachable();
  purelyPossiblyLost();
  // indirectlyLost();
  // heapArrayLeak();  // Shows memory leak
  // heapArrayWrongDelete();  // Shows mismatched delete
  // singleObjectWrongDelete();  // Shows mismatched delete[]

  std::cout << "\n=== Program Complete ===\n";
  return 0;
}
