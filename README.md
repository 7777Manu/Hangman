Virus vs. Antivirus – Hangman IT Edition

Jocul „Virus vs. Antivirus” este o reinterpretare interactivă a jocului Hangman, cu o tematică IT. În locul unui om spânzurat, jucătorul intră în rolul unui antivirus care trebuie să elimine un virus informatic prin ghicirea unui cuvânt secret. Fiecare greșeală duce la creșterea infectării sistemului, iar la eșec total, sistemul „se prăbușește” într-o simulare de sistem infectat (BSOD). Jocul este dezvoltat în limbajul C folosind biblioteca ncurses pentru o interfață vizuală interactivă în terminal.

1.  Funcționalități principale 
-Jucătorul trebuie să ghicească un cuvânt secret (preluat din fișierele de cuvinte pentru diferite nivele de dificultate: ușor, mediu, greu) prin alegerea literelor corecte, evitând astfel „infectarea” sistemului de către virus.
Jocul permite până la 6 greșeli (MAX_TRIES).
-Fiecare literă ghicită corect este afișată pe ecran;
- Literele greșite cresc nivelul de infecție.
-Pentru fiecare greșeală, se afișează un „nivel de virus” în stil progresiv, de la o amenințare minoră până la „SYSTEM FAILURE”.
-Dacă jucătorul face 6 greșeli, sistemul „se prăbușește”, afișând un ecran stil Blue Screen of Death (BSOD) cu mesaje haioase și dramatice.
-Dacă jucătorul ghicește cuvântul complet înainte de a atinge 6 greșeli, apare un mesaj de victorie cu un efect grafic de „explozie” și confirmarea că virusul a fost eliminat.

2.Implementare tehnică

2.1. Biblioteci folosite
stdio.h – Pentru input/output standard.
stdlib.h – Pentru funcționalități de randomizare.
string.h – Pentru manipularea șirurilor de caractere.
time.h – Pentru a genera un seed random.
ncurses.h – Pentru a crea interfața interactivă în terminal.

2.2. Structura programului
-Inițializare joc: Se selectează un cuvânt aleatoriu dintr-o listă de termeni IT. Se inițializează structura cu _ pentru literele neghicite.
-Bucle de joc: Jucătorul introduce o literă. Se verifică dacă litera face parte din cuvânt. Dacă da, se actualizează cuvântul afișat. Dacă nu, virusul „infectează” sistemul mai mult.
-Desenarea interfeței: Se afișează cuvântul cu literele ghicite. Se afișează mesajele corespunzătoare progresului.
-Finalizarea jocului: Dacă toate literele sunt ghicite → „Virus eliminated!” Dacă se atinge numărul maxim de greșeli → „SYSTEM FAILURE” + simulare de BSOD.

3.Elemente speciale și efecte vizuale Pentru a face jocul mai interactiv, ncurses ne permite să implementăm: 
-Animarea progresivă a virusului în ASCII art pe ecran, crescând în dimensiune și severitate odată cu greșelile.
-Evidențierea ultimei litere introduse pentru feedback vizual.
-Efecte de „ecran stricat” ce adaugă caractere haotice pe măsură ce sistemul devine tot mai infectat.

Acest joc oferă o experiență captivantă printr-o tematică inovatoare, utilizând ncurses pentru o interfață mai atractivă în terminal. Implementarea este simplă, dar permite extinderi ulterioare pentru a crește complexitatea și interactivitatea. „Virus vs. Antivirus” nu este doar un simplu Hangman, ci un concept modernizat care combină educația cu divertismentul! Let's fight the virus! 💾🚀
