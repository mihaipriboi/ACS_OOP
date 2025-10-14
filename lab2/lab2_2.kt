class Motorbike(var brand: String, var model: String, var year: Int, var engineCC: Double) {
  constructor(brand: String, model: String) : this(brand, model, 0, 0.0)

  fun displayInfo() {
    println("Motorbike Information:")
    println("Brand: $brand")
    println("Model: $model")
    println("Year: $year")
    println("Engine CC: $engineCC\n")
  }
}

fun main() {
  val bike1 = Motorbike("Yamaha", "MT-07", 2020, 689.0)
  bike1.displayInfo()

  val bike2 = Motorbike("Kawasaki", "Ninja 650")
  bike2.displayInfo()
}