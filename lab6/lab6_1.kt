import kotlin.math.*

abstract class City {
  // backing field for name
  private var _name: String = ""
  protected var area: Double = 0.0

  abstract fun displayInfo()
  abstract fun calculateArea()
  abstract fun celebrateFestival()

  // explicit getter/setter
  fun getName(): String { return _name }
  open fun setName(cityName: String) { _name = cityName }
}

class SquareCity(
  cityName: String,
  private var sideLength: Double,
  private var population: Int
) : City() {

  init {
    setName(cityName)
    area = sideLength * sideLength
  }

  override fun displayInfo() {
    println("Square City: ${getName()}, Area: $area, Population: $population")
  }

  override fun calculateArea() {
    area = sideLength * sideLength
  }

  override fun celebrateFestival() {
    println("${getName()} is celebrating the Square Festival!")
  }

  fun setPopulation(pop: Int) { population = pop }
  fun setSideLength(side: Double) { sideLength = side }
}

class CircularCity(
  cityName: String,
  private var radius: Double,
  private var numberOfBridges: Int
) : City() {

  init {
    setName(cityName)
    area = Math.PI * radius * radius
  }

  override fun displayInfo() {
    println("Circular City: ${getName()}, Area: $area, Number of Bridges: $numberOfBridges")
  }

  override fun calculateArea() {
    area = Math.PI * radius * radius
  }

  override fun celebrateFestival() {
    println("${getName()} is celebrating the Circular Festival!")
  }

  fun setNumberOfBridges(bridges: Int) { numberOfBridges = bridges }
  fun setRadius(rad: Double) { radius = rad }
}

class StarCity(
  cityName: String,
  private var armLength: Double,
  private var numberOfWheels: Int,
  private var numberOfDoors: Int
) : City() {

  init {
    setName(cityName)
    area = (5.0 / 2.0) * armLength * armLength * sin(72 * Math.PI / 180)
  }

  override fun displayInfo() {
    println("Star City: ${getName()}, Area: $area, Wheels: $numberOfWheels, Doors: $numberOfDoors")
  }

  override fun calculateArea() {
    area = (5.0 / 2.0) * armLength * armLength * sin(72 * Math.PI / 180)
  }

  override fun celebrateFestival() {
    println("${getName()} is celebrating the Star Festival!")
  }

  fun compareWheelsAndDoors() {
    if(numberOfWheels > numberOfDoors) {
      println("${getName()} has more wheels than doors.")
    } else if(numberOfWheels < numberOfDoors) {
      println("${getName()} has more doors than wheels.")
    } else {
      println("${getName()} has an equal number of wheels and doors.")
    }
  }

  fun setNumberOfWheels(wheels: Int) { numberOfWheels = wheels }
  fun setNumberOfDoors(doors: Int) { numberOfDoors = doors }
}

fun main() {
  val squareCity = SquareCity("SquareVille", 4.0, 1000)
  val circularCity = CircularCity("CircleTown", 3.0, 12)
  val starCity = StarCity("StarCity", 2.0, 7_043_212, 3_912_784)

  squareCity.displayInfo()
  squareCity.celebrateFestival()
  println()

  circularCity.displayInfo()
  circularCity.celebrateFestival()
  println()

  starCity.displayInfo()
  starCity.celebrateFestival()
  starCity.compareWheelsAndDoors()
}
