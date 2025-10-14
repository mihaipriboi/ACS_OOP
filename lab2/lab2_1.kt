import java.time.LocalDateTime
import java.time.format.DateTimeFormatter

class TimeLogger {
  init {
    val now = LocalDateTime.now()
    val formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm:ss")
    println("Object created on: ${now.format(formatter)}")

    val h: Int = 23 - now.hour
    val m: Int = 59 - now.minute
    val s: Int = 59 - now.second
    println("Time left until the end of the day: $h hours, $m minutes, $s seconds")
  }
}

fun main() {
  val obj = TimeLogger()
}