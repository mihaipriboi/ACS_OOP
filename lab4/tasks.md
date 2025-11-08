1. 4p [Kotlin] Realizați o clasă Beer, care să conțină atributele type și origin (ambele string și să fie protected). Clasa trebuie să aibă:
Un constructor default
Un constructor care va inițializa toți parametrii
Metode de get pentru cei doi parametrii
 Din clasa Beer derivați alte 3 clase printr-o moștenire private. Fiecare va avea un tip diferit de etichetă pe sticlă
Tipul A: etichetă pătrată (private length)
Tipul B: etichetă rotundă și transparentă (private radius)
Tipul C: în formă de triunghi dreptunghic (private base și height)
Fiecare clasă va avea constructori default și constructori cu parametrii care să seteze fiecare atribut.
Fiecare clasă trebuie să aibă o metodă de a întoarce aria etichetei, a tipului și a originii.

2. 3p  Modelați din natură un exemplu de moștenire multiplă (multiple inheritance) care să conțină constructor default. 

3. 3. 3P 
Clasa Baza:
Creează o clasă Baza cu 3 metode simple. Fiecare metodă afișează doar numele ei (de ex. "Apel Baza::metodaPublica").
public void metodaPublica()
protected void metodaProtected()
private void metodaPrivata()
Clasa DerivataProtected:
Moștenește protected din Baza (class DerivataProtected : protected Baza).
În interiorul clasei (în secțiunea public), scrie o metodă void testAccesInterior() care încearcă să apeleze toate cele 3 metode din Baza: metodaPublica(), metodaProtected(), metodaPrivata().
Clasa DerivataPrivata:
Moștenește private din Baza (class DerivataPrivata : private Baza).
Similar, scrie o metodă public void testAccesInterior() care încearcă să apeleze toate cele 3 metode din Baza.

Testul în main:
Creează un obiect DerivataProtected objProt;.
Încearcă să apelezi objProt.metodaPublica(). Compilează?
Apelează objProt.testAccesInterior().
Creează un obiect DerivataPrivata objPriv;.
Încearcă să apelezi objPriv.metodaPublica(). Compilează?
Apelează objPriv.testAccesInterior().
Intrebari
În testAccesInterior din ambele clase derivate, care dintre cele 3 apeluri nu a compilat și de ce?
În main, de ce apelul objProt.metodaPublica() nu a compilat, deși era public în Baza?
De ce objPriv.metodaPublica() nu a compilat? 

