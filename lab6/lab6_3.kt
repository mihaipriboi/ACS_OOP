interface iLogger {
  fun logMessage(msg: String)
}

abstract class Dispozitiv {
  protected var numeDispozitiv: String = ""

  fun getNume(): String { return numeDispozitiv }

  abstract fun esteConectat(): Boolean
}

class Imprimanta(nume: String) : iLogger, Dispozitiv() {
  private var conectat: Boolean = false

  init {
    numeDispozitiv = nume
  }

  fun conectare() {
    conectat = true
    logMessage("Imprimanta este acum conectata.")
  }

  fun deconectare() {
    conectat = false
    logMessage("Imprimanta a fost deconectata.")
  }

  override fun logMessage(msg: String) {
    println("[LOG $numeDispozitiv]: $msg")
  }

  override fun esteConectat(): Boolean {
    return conectat
  }
}

fun main() {
  val hp = Imprimanta("HP LaserJet")

  println("Nume dispozitiv: ${hp.getNume()}")

  if(!hp.esteConectat())
    println("Dispozitivul nu este conectat.")

  hp.conectare()

  if(hp.esteConectat())
    println("Dispozitivul este acum conectat.")

  hp.logMessage("Se printeaza un document test.")
  hp.deconectare()
}
