class Volume {
  fun display() {
    println("Metoda display afiseaza volumul geometric.")
  }

  fun display(side: Double) {
    val volume = side * side * side
    println("Volumul cubului cu latura %.2f este: %.2f".format(side, volume))
  }

  fun display(radius: Double, isSphere: Boolean) {
    if (!isSphere) return

    val volume = (4.0 / 3.0) * Math.PI * radius * radius * radius
    println("Volumul sferei cu raza %.2f este: %.2f".format(radius, volume))
  }

  fun display(baseLength: Double, height: Double) {
    val volume = (1.0 / 3.0) * baseLength * baseLength * height
    println("Volumul piramidei cu latura bazei %.2f si inaltimea %.2f este: %.2f".format(baseLength, height, volume))
  }
}

fun main() {
  val vol = Volume()

  vol.display()
  vol.display(3.0) // Cub cu latura 3.0
  vol.display(2.0, true) // Sfera cu raza 2.0
  vol.display(4.0, 5.0) // Piramida cu latura bazei 4.0 si inaltimea 5.0
}