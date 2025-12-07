# Bus Trip Reservation Application

## Autentificare, Autorizare și Login

### Ce este autentificarea și autorizarea

- **Autentificare:** procesul prin care un sistem verifică identitatea unui utilizator. Practic, sistemul trebuie să știe că “tu ești cine spui că ești”. În aplicație, autentificarea se realizează prin **email + parolă**, criptată și comparată cu hash-ul stocat în CSV.  

- **Autorizare:** procesul prin care sistemul decide ce resurse sau acțiuni poate efectua un utilizator autenticat. De exemplu, în aplicație:
  - **Operatorul** poate adăuga și șterge curse.
  - **Utilizatorii normali** pot căuta curse și rezerva locuri, dar nu pot modifica cursele existente.  

- **Login:** este actul efectiv prin care un utilizator se autentifică. Login-ul presupune:
  1. Introducerea **email-ului** și **parolei**.
  2. Validarea datelor împotriva bazei de date / fișierului de stocare.
  3. Dacă datele sunt corecte, se creează o sesiune sau token de acces.
  4. Dacă datele sunt incorecte, se aruncă erori și utilizatorul nu poate accesa resursele.

---

### Cum se realizează login-ul într-o aplicație

Un flow standard:

1. Utilizatorul completează **formularul de login**.
2. Aplicația **preia email-ul și parola**.
3. Parola este **hashed** folosind o funcție criptografică (ex: SHA256, bcrypt, HMAC-SHA256) combinată cu un key/nonce.  
4. Sistemul compară hash-ul rezultat cu cel stocat în baza de date/CSV.
5. Dacă hash-urile corespund:
   - Login reușit.
   - Se creează sesiunea utilizatorului (ex: `currentUser` în memorie).  
6. Dacă hash-urile nu corespund:
   - Login eșuat.
   - Se afișează mesaj de eroare corespunzător.

---

### Metode suplimentare de securitate

- **Salt și Key unice:** fiecare utilizator are un salt unic sau key, astfel încât hash-ul parolei să fie diferit chiar dacă mai mulți utilizatori au aceeași parolă.
- **Password Strength Validation:** verificarea complexității parolei (lowercase, uppercase, cifre, caractere speciale, lungime minimă) pentru a preveni parole slabe.
- **Rate Limiting:** blocarea încercărilor multiple consecutive de login eșuate pentru a preveni atacuri brute-force.
- **Two-Factor Authentication (2FA):** pe lângă parolă, utilizatorul trebuie să introducă un cod temporar (ex: SMS, email sau aplicație 2FA).
- **Hashing algoritmic sigur:** bcrypt, Argon2 sau HMAC cu key pentru a nu stoca parola în clar.
- **Logging și monitorizare:** pentru detectarea tentativelor suspecte de login.

---

### Diagrama de clase

```plaintext
+-----------------+
|      User       |
+-----------------+
| - username      |
| - email         |
| - key           |
| - passwordHash  |
+-----------------+
| +getUsername()  |
| +getEmail()     |
+-----------------+

          ^
          |
          |
+-----------------+
|   AuthManager   |
+-----------------+
| - users         |
+-----------------+
| +login()        |
| +registerUser() |
+-----------------+

+-----------------+
|      Trip       |
+-----------------+
| - tripID        |
| - fromCity      |
| - toCity        |
| - date          |
| - time          |
| - seatsTotal    |
| - seatsAvailable|
+-----------------+
| +display()      |
+-----------------+

          ^
          |
          |
+-----------------+
|   TripManager   |
+-----------------+
| - trips         |
+-----------------+
| +addTrip()      |
| +removeTrip()   |
| +searchTrips()  |
| +reserveSeat()  |
+-----------------+
```

- `User` reprezintă utilizatorii și operatorii.
- `AuthManager` gestionează login și register, păstrând lista de utilizatori.
- `Trip` reprezintă o cursă.
- `TripManager` gestionează toate cursele și rezervările.

---

### Observații

- Aplicația **nu stochează niciodată parola necriptată**.  
- Operatorul și utilizatorii normali au **roluri diferite**, ceea ce permite autorizarea acțiunilor.  
- Flow-ul complet poate fi testat prin:
  - Creare cont operator / user
  - Login operator -> add/remove trips
  - Login user -> search trips -> reserve seat
  - Tratarea excepțiilor pentru parole slabe, email duplicat, trip inexistent etc.