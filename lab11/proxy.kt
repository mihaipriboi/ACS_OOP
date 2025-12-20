import java.util.*

interface FibonacciProvider {
  // Returns the nth Fibonacci number
  fun getNumber(index: Int): ULong
}

// Real Subject
class HeavyFibonacciGenerator : FibonacciProvider {

  // 100 million integers * 8 bytes = ~800MB of RAM
  val sequence: ULongArray
  val MAX_SIZE = 100000000
  val MOD = 1000000000000000009UL

  constructor() {
    println("Allocating 800MB and calculating 100M numbers...\n")

    val start = System.nanoTime()

    sequence = ULongArray(MAX_SIZE)

    sequence[0] = 0UL
    sequence[1] = 1UL
    for(i in 2 until MAX_SIZE)
      sequence[i] = (sequence[i - 1] + sequence[i - 2]) % MOD

    val end = System.nanoTime()
    val elapsed = (end - start) / 1_000_000_000.0

    println("Done! Calculation took $elapsed seconds.\n")
  }

  override fun getNumber(index: Int): ULong {
    if(index < 0 || index >= MAX_SIZE) {
      throw IndexOutOfBoundsException("Index out of bounds!")
    }
    return sequence[index]
  }
}

// Proxy
class FibonacciProxy : FibonacciProvider {

  var realGenerator: HeavyFibonacciGenerator? = null

  override fun getNumber(index: Int): ULong {
    if(realGenerator == null) {
      println("First request received. Initializing heavy generator...\n")
      realGenerator = HeavyFibonacciGenerator()
    }

    return realGenerator!!.getNumber(index)
  }
}

fun main() {
  val fib: FibonacciProvider = FibonacciProxy()

  while(true) {
    println("What Fibonacci number would you like to request?\n")
    val input = readLine() ?: break
    val n = input.toIntOrNull() ?: break

    try {
      println("Thinking...\n")
      val value = fib.getNumber(n)
      println("[Fibonacci $n] = $value\n")
    } catch (e: Exception) {
      System.err.println(e.message)
      break
    }
  }

  return
}
