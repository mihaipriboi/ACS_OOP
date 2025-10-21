1. Să se realizeze o clasă Exchange care are ca atribut money. Atributul money se setează prin constructor. Valoarea dată la constructor trebuie sa fie una generată random între 0-5000. Creați un numar de obiecte egal cu data curentă obiecte și afișați numărul de obiecte care au money mai mare de 3000. (să se folosească static member doar pentru contor). 2.5p [fără Kotlin]

2. Să se realizeze o clasă Student. Această clasă trebuie să aibă următoarele atribute: nume, prenume, CNP, anul nașterii toate de tipul private, dar și numele facultății și anul înființării acesteia (tot private). 
- Creați o funcție care să genereze automat CNP-uri. Explicați algoritmul din spate.
- Creați metodele de get și set pentru Student. 0.5p
- Creați o metodă care să întoarcă sexul studentului în funcție de CNP. 0.5p
- Creați o metodă care să întoarcă vârsta studentului. 0.5p
- Creați o metodă care să întoarcă diferența de ani dintre anul înființării facultății și data nașterii studentului. 0.5. p
Utilizați this Pointer. 0.5p  Testați codul creând mai mulți studenți.
NU VA PUNETI CNP-UL VOSTRU!

3. [5p]. Se va  crea o clasă ContBancar care modelează un scenariu real. Construiti o clasă robustă care gestionează conturi bancare, separând datele specifice fiecărui cont de cele comune tuturor conturilor. Cerințe:
- Clasa ContBancar: Va avea datele membre private: string titularCont & double sold
- Constructorul: Va primi titularul și soldul inițial pentru a crea un nou cont.
- Metode de Acces (Getters): getTitular(): Returnează numele titularului & getSold(): Returnează soldul curent. - - - - Important: Ambele metode trebuie marcate ca const. De ce? Pentru că ele doar "citesc" starea contului, nu o modifică. Este o promisiune de siguranță.
- Metode pentru Tranzacții: depune(double suma): Adaugă suma specificată la sold & retrage(double suma): Scade suma din sold, dar doar dacă există fonduri suficiente. Dacă nu, afișează un mesaj de eroare și soldul rămâne neschimbat.
- Date Partajate (Membru static): Toate conturile dintr-o bancă au aceeași dobândă. Vom modela acest lucru cu un membru private static double rataDobanda.
- Acțiuni la Nivel de Clasă (Metode static): Adaugă o metodă public static void seteazaRataDobanda(double rataNoua). Această metodă va fi folosită de "bancă" pentru a schimba dobânda pentru toate conturile existente și viitoare. Se va apela direct pe clasă: ContBancar::seteazaRataDobanda(...). Adaugă o metodă non-statică numită aplicaDobanda(). Aceasta calculează dobânda pentru contul curent (sold * rataDobanda) și o adaugă la sold.

3. [5p]. Testarea în main:
- Creează cel puțin două obiecte ContBancar (cont1, cont2) cu titulari și solduri diferite.
- Efectuează câteva operații de depunere și retragere pe ambele conturi. Afișează soldurile după fiecare operație folosind getter-ele const. Afișează soldurile inițiale. Apoi, "banca" decide să mărească dobânda. Apelează metoda statică: ContBancar::seteazaRataDobanda(0.07);.
- Apelează metoda aplicaDobanda() pentru fiecare cont în parte.
- Afișează din nou soldurile. Vei observa că ambele conturi au beneficiat de noua rată a dobânzii, demonstrând puterea membrilor static.
