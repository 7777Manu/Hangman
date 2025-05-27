Virus vs. Antivirus – Hangman IT Edition

Jocul „Virus vs. Antivirus” este o reinterpretare interactivă a jocului Hangman, cu o tematică IT. În locul unui om spânzurat, jucătorul intră în rolul unui antivirus care trebuie să elimine un virus informatic prin ghicirea unui cuvânt secret. Fiecare greșeală duce la creșterea infectării sistemului, iar la eșec total, sistemul „se prăbușește” într-o simulare de sistem infectat (BSOD). Jocul este dezvoltat în limbajul C folosind biblioteca ncurses pentru o interfață vizuală interactivă în terminal.

1.  Funcționalități principale 
-Ghicirea cuvintelor IT: Cuvintele sunt extrase aleator din fișiere dedicate pe nivele de dificultate (ușor, mediu, greu).
-6 încercări maxime: Jucătorul are până la 6 greșeli înainte ca sistemul să fie infectat complet.
-Niveluri de infecție: Pentru fiecare greșeală, virusul crește în dimensiune și amenințare, ilustrat prin animații ASCII.
-Ecran Blue Screen of Death (BSOD): Dacă jucătorul eșuează, apare o simulare stilizată a BSOD-ului cu mesaje amuzante.
-Mesaj de victorie: Dacă jucătorul ghicește cuvântul, apare o animație de „explozie” și confirmarea eliminării virusului.

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
