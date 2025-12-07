import java.io.File
import kotlin.random.Random


data class StudentData(
  val id: String,
  val age: Int,
  val gender: String,
  val studyHours: Float,
  val socialHours: Float,
  val netflixHours: Float,
  val job: String,
  val attendance: Float,
  val sleep: Float,
  val diet: String,
  val exercise: Int,
  val parentsEdu: String,
  val internet: String,
  val mentalHealth: Int,
  val extracurricular: String,
  val score: Float
)

fun String.toStudentData(): StudentData? {
  val tokens = this.split(',')
  if(tokens.size < 16) return null 

  return try {
    StudentData(
      id = tokens[0],
      age = tokens[1].toInt(),
      gender = tokens[2],
      studyHours = tokens[3].toFloat(),
      socialHours = tokens[4].toFloat(),
      netflixHours = tokens[5].toFloat(),
      job = tokens[6],
      attendance = tokens[7].toFloat(),
      sleep = tokens[8].toFloat(),
      diet = tokens[9],
      exercise = tokens[10].toInt(),
      parentsEdu = tokens[11],
      internet = tokens[12],
      mentalHealth = tokens[13].toInt(),
      extracurricular = tokens[14],
      score = tokens[15].toFloat()
    )
  } catch(e: Exception) {
    null 
  }
}

sealed interface Student {
  val data: StudentData

  fun getAge(): Int = data.age
  fun getStudy(): Float = data.studyHours
  fun getSocial(): Float = data.socialHours
  fun getJob(): String = data.job
}

data class StudentPolitehnica(override val data: StudentData) : Student {
  fun computeEfficiency(): Float {
    return data.studyHours - data.socialHours
  }
}

data class StudentMedicina(override val data: StudentData) : Student {
  fun checkStressLevel(): Boolean {
    return data.mentalHealth < 5
  }
}

fun importCsvData(filename: String): List<StudentData> {
  return try {
    File(filename)
      .readLines() 
      .drop(1) 
      .mapNotNull { it.toStudentData() } 
  } catch(e: Exception) {
    throw RuntimeException("File error: ${e.message}") 
  }
}

class StatisticsManager {
  private val students = mutableListOf<Student>()

  fun add(s: Student) {
    students.add(s)
  }

  fun avgAgeMedicina(): Float {
    val medicinaStudents = students.filterIsInstance<StudentMedicina>()
    return if(medicinaStudents.isNotEmpty()) {
      medicinaStudents.sumOf { it.getAge() } / medicinaStudents.size.toFloat()
    } else {
      0f
    }
  }
  
  fun upbStudySocial(): Pair<Float, Float> {
    val politehnicaStudents = students.filterIsInstance<StudentPolitehnica>()
    return if(politehnicaStudents.isNotEmpty()) {
      val count = politehnicaStudents.size.toFloat()
      val s1 = politehnicaStudents.sumOf { it.getStudy().toDouble() }.toFloat()
      val s2 = politehnicaStudents.sumOf { it.getSocial().toDouble() }.toFloat()
      Pair(s1 / count, s2 / count)
    } else {
      Pair(0f, 0f)
    }
  }

  fun countPartTime(): Int {
    return students.count { it.getJob() == "Yes" }
  }
}

fun main() {
  try {
    val allData = importCsvData("student_habits_performance-1.csv")

    val manager = StatisticsManager()

    val random = Random(System.currentTimeMillis()) 

    for(d in allData) {
      val student: Student = if(random.nextBoolean()) { 
        StudentPolitehnica(d)
      } else {
        StudentMedicina(d)
      }
      
      manager.add(student)
    }

    val medieMedicina = manager.avgAgeMedicina()
    println("1) Varsta medie a studentilor de la Medicina: $medieMedicina")

    val (studyUpb, socialUpb) = manager.upbStudySocial()

    println("2) Timp mediu studiu UPB: $studyUpb")
    println("   Timp mediu social UPB: $socialUpb")

    val partTime = manager.countPartTime()
    println("3) Studentii cu job part-time: $partTime\n")

  } catch (e: Exception) {
    System.err.println("Eroare: ${e.message}")
  }
}