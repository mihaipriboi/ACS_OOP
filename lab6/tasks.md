3p Lab Creați o clasă abstractă City  care să aibă 3 metode diferite. Realizați trei clase care să moștenească clasa City și să implementeze cele 3 metode pure virtual function.
3p Realizați un exemplu legat de cărți în care să implementați:
Friend class
Friend function
Virtual function 
3p Creează o "interfață" C++ (clasă cu doar funcții virtuale pure) numită iLogger cu o metodă virtual void logMessage(string msg) = 0;.
Creează o clasă abstractă hibrid numită Dispozitiv care are un membru protected: string numeDispozitiv și o funcție implementată string getNume(). Dar are și o funcție virtuală pură virtual bool esteConectat() = 0;.
Creează o clasă Imprimanta care moștenește ambele: public iLogger și public Dispozitiv. Implementează toate funcțiile necesare.
