abstract class Beer(
  val type: String = "Unknown",
  val origin: String = "Unknown"
) {
  abstract fun getLabelArea(): Double

  fun displayInfo() {
    println("Type: $type, Origin: $origin, Label Area: ${"%.2f".format(getLabelArea())}cm^2")
  }
}

class BeerTypeA(
  type: String = "Unknown",
  origin: String = "Unknown",
  private val length: Double = 0.0
) : Beer(type, origin) {
  override fun getLabelArea(): Double {
    return length * length
  }
}

class BeerTypeB(
  type: String = "Unknown",
  origin: String = "Unknown",
  private val radius: Double = 0.0
) : Beer(type, origin) {
  override fun getLabelArea(): Double {
    return Math.PI * radius * radius
  }
}

class BeerTypeC(
  type: String = "Unknown",
  origin: String = "Unknown",
  private val base: Double = 0.0,
  private val height: Double = 0.0
) : Beer(type, origin) {
  override fun getLabelArea(): Double {
    return 0.5 * base * height
  }
}

fun main() {
  val beerA = BeerTypeA("Calsberg", "Denmark", 5.0)
  beerA.displayInfo()

  val beerB = BeerTypeB("Timisoreana", "Romania", 3.0)
  beerB.displayInfo()

  val beerC = BeerTypeC("Guinness", "Ireland", 4.0, 6.0)
  beerC.displayInfo()
}