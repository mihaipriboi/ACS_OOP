1. [În Laborator] Să se implementeze o clasă cu constructor default care să afișeze data curentă (ziua și ora) în momentul instanțierii și să se calculeze câte ore mai sunt până la finalul zilei. [Kotlin]

2. Să se implementeze o clasă Motorbike. Această clasă trebuie să aibă constructori multiplii (minim 4). Constructorii trebuie să fie definiți în afara clasei. Clasa Motorbike trebuie să aibă minim 4 atribute și un constructor să fie de tipul default. Creați un obiect pentru fiecare constructor.  [pentru Kotlin, creati o clasa Motorbike care sa aiba primary și secondary constructor și creați 2 obiecte cu fiecare din constructori]

3. a) Să se implementeze o clasă Sibling. Atributele din interiorul clasei vor fi cele de nume,  prenume și vârstă, toate alocate prin intermediul pointerilor. Pentru această clasă trebuie să aveți și un copy constructor. Creați un obiect sibling1. Creați un obiect sibling2 cu ajutorul copy constructorului și faceți update la prenume și vârstă. Afișați atributele fiecărui obiect.

b) Folosiți un LLM (precum Gemini sau ChatGPT) cu următorul prompt (în engleză, pentru rezultate mai bune):

"Write a C++ class named Student. It should have a std::string for the name and a dynamic array of floats to store grades. Include a constructor that takes the name and the number of grades, and a destructor to clean up the memory."Creați un obiect Student, numit student1, cu câteva note. Creați un al doilea obiect Student, student2, copiindu-l pe primul: Student student2 = student1. Modificați o notă pentru student2. Afișați notele pentru ambii studenți, student1 și student2. Explicți outputul și reparați codul în caz că nu funcționează cum trebuie.

4. ManagerFișier (Principiul RAII în acțiune)
Acest exercițiu demonstrează principiul RAII (Resource Acquisition Is Initialization) folosind o resursă care nu este memoria. Creați o clasă C++ numită ManagerFișier. Constructorul primește ca argument un const char* nume_fisier și deschide un fișier pentru scriere folosind std::ofstream. La succes, va afișa mesajul "Fișier deschis." O metodă void scrie(const std::string& mesaj) scrie o linie de text în fișier. Destructorul trebuie să închidă fișierul și să afișeze mesajul "Fișier închis." Funcția main: În main, creați o instanță a clasei ManagerFișier într-un bloc de cod ({ ... }). Apelați metoda scrie. Observați cum fișierul este închis automat atunci când obiectul iese din scope.

5. Creați o clasă Motor cu un constructor implicit care afișează "Motor pornit" și un destructor care afișează "Motor oprit".
Creați o clasă Mașină care are ca membru privat un obiect de tip Motor (de ex., Motor motor;).
Constructorul clasei Mașină va afișa "Mașină asamblată", iar destructorul va afișa "Mașină dezasamblată".
În main, creați o instanță a clasei Mașină, de exemplu: Mașină mașinaMea;.
Care este outputul exact al programului? De ce?

*toate exercițiile trebuie să aibă și destructorii definiți

