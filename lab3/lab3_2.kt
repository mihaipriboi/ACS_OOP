class Student {
  private var nume: String
  private var prenume: String
  private var CNP: String
  private var anul_nasterii: Int
  private var nume_facultate: String
  private var anul_infiintarii: Int

  private fun genereazaCNP(): String {
    /*
    SAALLZZJJNNNC
    S - sexul si secolul nasterii
        1,2 - secolul 19 (1800-1899) (1-masculin, 2-feminin)
        3,4 - secolul 20 (1900-1999) (3-masculin, 4-feminin)
        5,6 - secolul 21 (2000-2099) (5-masculin, 6-feminin)
    AA - ultimele doua cifre ale anului nasterii
    LL - luna nasterii
    ZZ - ziua nasterii
    JJJ - codul judetului
    NNN - numar de ordine
    C - cifra de control
        primele 12 cifre sunt inmultite cu un vector de constante
        (279146358279) si se face suma rezultatelor
        suma se imparte la 11, restul este cifra de control
    */

    var S: String
    val an = anul_nasterii

    S = when(an) {
      in 1800..1899 -> if ((0..1).random() == 0) "1" else "2"
      in 1900..1999 -> if ((0..1).random() == 0) "3" else "4"
      in 2000..2099 -> if ((0..1).random() == 0) "5" else "6"
      else -> "0"
    }

    val AA = String.format("%02d", an % 100)
    val LL = "01"
    val ZZ = "01"
    val JJJ = "001"
    val NNN = "001"

    // Cifra de control
    val CNP_partial = S + AA + LL + ZZ + JJJ + NNN
    val constante = "279146358279"

    var suma = 0
    for(i in 0 until 12)
      suma += (CNP_partial[i].digitToInt()) * (constante[i].digitToInt())

    var C = suma % 11
    if(C == 10) C = 1

    return CNP_partial + C.toString()
  }

  /* Constructors */
  constructor() {
    this.nume = "Anonim"
    this.prenume = "Anonim"
    this.anul_nasterii = 2000
    this.nume_facultate = "Necunoscut"
    this.anul_infiintarii = 2000
    this.CNP = genereazaCNP()
  }

  constructor(
    nume: String,
    prenume: String,
    anul_nasterii: Int,
    nume_facultate: String,
    anul_infiintarii: Int
  ) {
    this.nume = nume
    this.prenume = prenume
    this.anul_nasterii = anul_nasterii
    this.nume_facultate = nume_facultate
    this.anul_infiintarii = anul_infiintarii
    this.CNP = genereazaCNP()
  }

  /* Setters */
  fun setNume(nume: String) {
    this.nume = nume
    this.CNP = genereazaCNP()
  }

  fun setPrenume(prenume: String) {
    this.prenume = prenume
    this.CNP = genereazaCNP()
  }

  fun setAnulNasterii(anul_nasterii: Int) {
    this.anul_nasterii = anul_nasterii
    this.CNP = genereazaCNP()
  }

  fun setNumeFacultate(nume_facultate: String) {
    this.nume_facultate = nume_facultate
  }

  fun setAnulInfiintarii(anul_infiintarii: Int) {
    this.anul_infiintarii = anul_infiintarii
  }

  /* Getters */
  fun getNume(): String { return this.nume }
  fun getPrenume(): String { return this.prenume }
  fun getCNP(): String { return this.CNP }
  fun getAnulNasterii(): Int { return this.anul_nasterii }
  fun getNumeFacultate(): String { return this.nume_facultate }
  fun getAnulInfiintarii(): Int { return this.anul_infiintarii }
  
  fun getSex(): String {
    val S = this.CNP[0]
    return if (S.digitToInt() % 2 == 1) "Masculin" else "Feminin"
  }

  fun getVarsta(): Int {
    val currentYear = java.util.Calendar.getInstance().get(java.util.Calendar.YEAR)
    return currentYear - this.anul_nasterii
  }

  fun getDiferentaAni(): Int {
    return kotlin.math.abs(this.anul_infiintarii - this.anul_nasterii)
  }

  fun displayInfo() {
    println("Nume: ${this.nume}")
    println("Prenume: ${this.prenume}")
    println("CNP: ${this.CNP}")
    println("Anul nasterii: ${this.anul_nasterii}")
    println("Nume facultate: ${this.nume_facultate}")
    println("Anul infiintarii: ${this.anul_infiintarii}")
    println("Sex: ${getSex()}")
    println("Varsta: ${getVarsta()}")
    println("Diferenta ani: ${getDiferentaAni()}\n")
  }
}

fun main() {
  val st1 = Student("Zanoaga", "Ovidiu", 2007, "UPB", 1818)
  val st2 = Student()
  val st3 = Student("Klimt", "Gustav", 1960, "ASE", 1913)

  st1.displayInfo()
  st2.displayInfo()
  st3.displayInfo()

  st2.setNume("Musk")
  st2.setPrenume("X Æ A-12")
  st2.setAnulNasterii(2020)
  st2.setNumeFacultate("SpaceX University")
  st2.setAnulInfiintarii(2020)
  st2.displayInfo()

  println("Schimbare anul nasterii pentru st3 (se va schimba si prima cifra):")
  println(st3.getCNP())
  st3.setAnulNasterii(2000)
  println(st3.getCNP())
}