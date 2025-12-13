/*
Sursa informatii:
- https://stackoverflow.com
*/

// 1.

abstract class Avion {
  abstract fun descriere()
}

class AvionCalatori : Avion() {
  override fun descriere() {
    println("Avion de calatori - Boeing")
  }
}

class AvionLupta : Avion() {
  override fun descriere() {
    println("Avion de lupta - F16")
  }
}

class AvionTransport : Avion() {
  override fun descriere() {
    println("Avion de transport - Cargo")
  }
}

object AvionFactory {
  fun createAvion(tip: String): Avion? {
    return when(tip) {
      "calatori" -> AvionCalatori()
      "lupta" -> AvionLupta()
      "transport" -> AvionTransport()
      else -> null
    }
  }
}

/*
PROS:
- separa crearea obiectelor de utilizare
- cod extensibil
- reduce dependentele

CONS:
- mai multe clase
- complexitate mai mare
*/


// 2.

class Pizza {
  var blat: String = ""
  var sos: String = ""
  val toppinguri: MutableList<String> = mutableListOf()

  fun afisare() {
    println("Pizza:")
    println(" Blat: $blat")
    println(" Sos: $sos")
    print(" Toppinguri: ")
    for(t in toppinguri)
      print("$t ")
    println("\n")
  }
}

abstract class PizzaBuilder {
  abstract fun setBlat()
  abstract fun setSos()
  abstract fun addTopping()
  abstract fun getPizza(): Pizza
}

class MargheritaBuilder : PizzaBuilder() {
  private val p = Pizza()

  override fun setBlat() {
    p.blat = "subtire"
  }

  override fun setSos() {
    p.sos = "rosii"
  }

  override fun addTopping() {
    p.toppinguri.add("mozzarella")
    p.toppinguri.add("busuioc")
  }

  override fun getPizza(): Pizza {
    return p
  }
}

class QuattroStagioniBuilder : PizzaBuilder() {
  private val p = Pizza()

  override fun setBlat() {
    p.blat = "pufos"
  }

  override fun setSos() {
    p.sos = "rosii"
  }

  override fun addTopping() {
    p.toppinguri.add("sunca")
    p.toppinguri.add("ciuperci")
    p.toppinguri.add("masline")
    p.toppinguri.add("anghinare")
  }

  override fun getPizza(): Pizza {
    return p
  }
}

class PizzaDirector {
  fun buildPizza(builder: PizzaBuilder) {
    builder.setBlat()
    builder.setSos()
    builder.addTopping()
  }
}

/*
PROS:
- control pas cu pas
- usor de creat obiecte complexe
- permite configuratii custom

CONS:
- multe clase
- cod mai lung
*/


// 3.

object Logger {
  init {
    println("Sistemul de Jurnalizare a pornit.")
  }

  fun log(mesaj: String) {
    println("[LOG] $mesaj")
  }
}

/*
PROS Singleton:
- un singur punct de acces
- economie de memorie
- control total asupra instantei

CONS Singleton:
- greu de testat
- dependenta globala
- poate deveni anti-pattern
*/


fun main() {

  println("--- 1. FACTORY ---")
  val a1 = AvionFactory.createAvion("calatori")
  val a2 = AvionFactory.createAvion("lupta")
  val a3 = AvionFactory.createAvion("transport")

  a1?.descriere()
  a2?.descriere()
  a3?.descriere()

  println("\n--- 2. BUILDER ---")
  val director = PizzaDirector()

  val m = MargheritaBuilder()
  director.buildPizza(m)
  val p1 = m.getPizza()
  p1.afisare()

  val q = QuattroStagioniBuilder()
  director.buildPizza(q)
  val p2 = q.getPizza()
  p2.afisare()

  println("--- 3. SINGLETON ---")

  val log1 = Logger
  val log2 = Logger

  log1.log("Salut din prima referinta")
  log2.log("Salut din a doua referinta")

  println("${System.identityHashCode(log1)} vs ${System.identityHashCode(log2)}")
}
