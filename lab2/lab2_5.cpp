#include <stdio.h>

class Motor {
public:
  Motor() { printf("Motor pornit\n"); }
  ~Motor() { printf("Motor oprit\n"); }
};

class Masina {
private:
  Motor motor;
public:
  Masina() { printf("Masina asamblata\n"); }
  ~Masina() { printf("Masina dezasamblata\n"); }
};

int main() {
  Masina masinaMea;
  /* Output:
  Motor pornit
  Masina asamblata
  Masina dezasamblata
  Motor oprit
  */
  /* De ce:
  Cand este creat obiectul masinaMea, mai intai se creeaza obiectul motor
  pentru ca membrii unei clase sunt initializati in ordinea in care sunt
  declarati in clasa, dupa care se executa corpul constructorului. Deci,
  constructorul clasei Motor este apelat inaintea constructorului clasei
  Masina. La distrugerea obiectului masinaMea, destructorul clasei Masina
  este apelat primul, urmat de destructorul clasei Motor, deoarece membrii
  sunt distrusi in ordinea inversa a initializarii lor.
  */
  return 0;
}