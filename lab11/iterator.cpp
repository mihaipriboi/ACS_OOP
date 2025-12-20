#include <iostream>
#include <vector>

using namespace std;

// Iterator
class FibonacciIterator {
public:
  virtual bool hasNext() = 0;
  virtual unsigned long long next() = 0;
  virtual ~FibonacciIterator() = default;
};

// Aggregate
class FibonacciCollection {
public:
  virtual FibonacciIterator* createIterator() = 0;
  virtual ~FibonacciCollection() = default;
};

// Concrete Aggregate
class FibonacciSequence : public FibonacciCollection {
private:
  vector<unsigned long long> sequence;

public:
  FibonacciSequence(int count) {
    sequence.resize(count);

    sequence[0] = 0;
    if(count > 1)
      sequence[1] = 1;

    for(int i = 2; i < count; i++)
      sequence[i] = sequence[i - 1] + sequence[i - 2];
  }

  unsigned long long getNumber(int index) const {
    return sequence[index];
  }

  int size() const {
    return sequence.size();
  }

  FibonacciIterator* createIterator() override;
};

// Concrete Iterator
class SequenceIterator : public FibonacciIterator {
private:
  FibonacciSequence* sequence;
  int index = 0;

public:
  SequenceIterator(FibonacciSequence* seq)
    : sequence(seq) {}

  bool hasNext() override {
    return index < sequence->size();
  }

  unsigned long long next() override {
    return sequence->getNumber(index++);
  }
};

FibonacciIterator* FibonacciSequence::createIterator() {
  return new SequenceIterator(this);
}

int main() {
  FibonacciCollection* fib = new FibonacciSequence(20);
  FibonacciIterator* it = fib->createIterator();

  cout << "Iterating Fibonacci numbers...\n";

  while(it->hasNext()) {
    cout << it->next() << " ";
  }
  cout << '\n';

  delete it;
  delete fib;
  return 0;
}
