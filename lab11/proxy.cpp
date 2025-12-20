#include <iostream>
#include <vector>
#include <memory>
#include <chrono>

using namespace std;

class FibonacciProvider {
public:
  // Returns the nth Fibonacci number
  virtual unsigned long long getNumber(int index) = 0;
  virtual ~FibonacciProvider() = default;
};

// Real Subject
class HeavyFibonacciGenerator : public FibonacciProvider {
private:
  // 100 million integers * 8 bytes = ~800MB of RAM
  vector<unsigned long long> sequence;
  const int MAX_SIZE = 100000000; 
  const unsigned long long MOD = 1000000000000000009ULL;

public:
  HeavyFibonacciGenerator() {
    cout << "Allocating 800MB and calculating 100M numbers...\n";

    auto start = chrono::high_resolution_clock::now();

    sequence.resize(MAX_SIZE);

    sequence[0] = 0;
    sequence[1] = 1;
    for(int i = 2; i < MAX_SIZE; i++)
      sequence[i] = (sequence[i - 1] + sequence[i - 2]) % MOD;

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "Done! Calculation took " << elapsed.count() << " seconds.\n";
  }

  unsigned long long getNumber(int index) override {
    if(index < 0 || index >= MAX_SIZE) {
      throw out_of_range("Index out of bounds!");
    }
    return sequence[index];
  }
};

// Proxy
class FibonacciProxy : public FibonacciProvider {
private:
  HeavyFibonacciGenerator* realGenerator = nullptr;

public:
  ~FibonacciProxy() {
    delete realGenerator;
  }

  unsigned long long getNumber(int index) override {
    if(!realGenerator) {
      cout << "First request received. Initializing heavy generator...\n";
      realGenerator = new HeavyFibonacciGenerator();
    }

    return realGenerator->getNumber(index);
  }
};

int main() {
  FibonacciProvider* fib = new FibonacciProxy();

  while(true) {
    cout << "What Fibonacci number would you like to request?\n";
    int n;
    cin >> n;

    try {
      cout << "Thinking...\n";
      unsigned long long value = fib->getNumber(n);
      cout << "[Fibonacci " << n << "] = " << value << "\n";
    } catch (const exception& e) {
      cerr << e.what() << endl;
    }
  }

  delete fib;
  return 0;
}