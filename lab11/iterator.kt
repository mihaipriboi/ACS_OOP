import java.util.*

// Iterator
interface FibonacciIterator {
  fun hasNext(): Boolean
  fun next(): ULong
}

// Aggregate
interface FibonacciCollection {
  fun createIterator(): FibonacciIterator
}

// Concrete Aggregate
class FibonacciSequence(count: Int) : FibonacciCollection {

  val sequence: ULongArray

  init {
    sequence = ULongArray(count)

    sequence[0] = 0UL
    if(count > 1)
      sequence[1] = 1UL

    for(i in 2 until count)
      sequence[i] = sequence[i - 1] + sequence[i - 2]
  }

  fun getNumber(index: Int): ULong {
    return sequence[index]
  }

  fun size(): Int {
    return sequence.size
  }

  override fun createIterator(): FibonacciIterator {
    return SequenceIterator(this)
  }
}

// Concrete Iterator
class SequenceIterator(seq: FibonacciSequence) : FibonacciIterator {

  val sequence: FibonacciSequence
  var index = 0

  init {
    sequence = seq
  }

  override fun hasNext(): Boolean {
    return index < sequence.size()
  }

  override fun next(): ULong {
    return sequence.getNumber(index++)
  }
}

fun main() {
  val fib: FibonacciCollection = FibonacciSequence(20)
  val it: FibonacciIterator = fib.createIterator()

  println("Iterating Fibonacci numbers...\n")

  while(it.hasNext()) {
    print("${it.next()} ")
  }
  println()

  return
}
