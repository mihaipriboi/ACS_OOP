class ContBancar(
  val titularCont: String,
  private var sold: Double
) {
  enum class RetragereStatus {
    SUCCES,
    FONDURI_INSUFICIENTE
  }

  companion object {
    private var rataDobanda: Double = 0.0

    fun seteazaRataDobanda(rataNoua: Double) {
      rataDobanda = rataNoua
    }
  }

  fun depune(suma: Double) {
    sold += suma
  }

  fun retrage(suma: Double): RetragereStatus {
    if(suma > sold) {
      return RetragereStatus.FONDURI_INSUFICIENTE
    } else {
      sold -= suma
      return RetragereStatus.SUCCES
    }
  }

  fun aplicaDobanda() {
    sold += sold * rataDobanda
  }

  fun getTitular(): String {
    return titularCont
  }

  fun getSold(): Double {
    return sold
  }
}

fun main() {
  val cont1 = ContBancar("Liviu", 1000.0)
  val cont2 = ContBancar("Adrian", 2000.0)

  println("Sold initial cont1: ${cont1.getSold()}")
  println("Sold initial cont2: ${cont2.getSold()}")

  cont1.depune(500.0)
  println("Sold cont1 dupa depunere: ${cont1.getSold()}")

  when(cont2.retrage(2500.0)) {
    ContBancar.RetragereStatus.SUCCES ->
      println("Retragere cu succes din cont2.")
    ContBancar.RetragereStatus.FONDURI_INSUFICIENTE ->
      println("Fonduri insuficiente pentru retragere din cont2.")
  }
  println("Sold cont2 dupa tentativa de retragere: ${cont2.getSold()}")

  when(cont2.retrage(1500.0)) {
    ContBancar.RetragereStatus.SUCCES ->
      println("Retragere cu succes din cont2.")
    ContBancar.RetragereStatus.FONDURI_INSUFICIENTE ->
      println("Fonduri insuficiente pentru retragere din cont2.")
  }
  println("Sold cont2 dupa tentativa de retragere: ${cont2.getSold()}")

  ContBancar.seteazaRataDobanda(0.07)

  cont1.aplicaDobanda()
  cont2.aplicaDobanda()

  println("Sold cont1 dupa aplicarea dobanzii: ${cont1.getSold()}")
  println("Sold cont2 dupa aplicarea dobanzii: ${cont2.getSold()}")
}