abstract class Book(
  private var _title: String,
  private var _pages: Int
) {
  abstract fun displayInfo()

  fun getTitle(): String { return _title }
  fun getPages(): Int { return _pages }
}

class Novel(
  t: String,
  pag: Int,
  private var genre: String
) : Book(t, pag) {

  override fun displayInfo() {
    println("Roman: ${getTitle()}")
    println("Gen: $genre")
    println("Pagini: ${getPages()}\n")
  }
}

class Reader {
  fun readBook(book: Book) {
    println("Cititorul citeste: ${book.getTitle()}")
    println("Numarul de pagini citite: ${book.getPages()}")
  }
}

fun comparePages(b1: Book, b2: Book) {
  if(b1.getPages() > b2.getPages())
    println("'${b1.getTitle()}' are mai multe pagini decat '${b2.getTitle()}'.")
  else if(b1.getPages() < b2.getPages())
    println("'${b1.getTitle()}' are mai putine pagini decat '${b2.getTitle()}'.")
  else
    println("'${b1.getTitle()}' si '${b2.getTitle()}' au acelasi numar de pagini.")
}

fun main() {
  val dune = Novel("Dune", 412, "Science Fiction")
  val stapanulInelelor = Novel("Stapanul Inelelor", 1178, "Fantasy")

  val ptrBook1: Book = dune
  val ptrBook2: Book = stapanulInelelor

  ptrBook1.displayInfo()
  ptrBook2.displayInfo()

  comparePages(dune, stapanulInelelor)
  println()

  val reader = Reader()
  reader.readBook(dune)
}
