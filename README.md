Titlu proiect: Virus vs. Antivirus - Hangman IT Edition

Jocul „Virus vs. Antivirus” este o reinterpretare interactivă a jocului Hangman, cu o tematică IT. În locul unui om spânzurat, jucătorul intră în rolul unui antivirus care trebuie să elimine un virus informatic prin ghicirea unui cuvânt secret. Fiecare greșeală duce la creșterea infectării sistemului, iar la eșec total, sistemul „se prăbușește” într-o simulare de ecran albastru (BSOD). Jocul este dezvoltat în limbajul C folosind biblioteca ncurses pentru o interfață vizuală interactivă în terminal.

1.  Funcționalități principale 
-Generarea unui cuvânt secret – Un cuvânt este ales aleatoriu dintr-o listă predefinită de termeni IT (ex: „firewall”, „trojan”, „malware”).
-Afișarea progresului jucătorului 
– Literele ghicite sunt dezvăluite, iar cele necunoscute rămân ascunse sub _. 
-Sistem de greșeli și infectare – La fiecare greșeală, un virus grafic va „infecta” mai mult ecranul. 
-Interfață interactivă cu ncurses – Ecranul jocului este actualizat fără să fie nevoie de apăsarea Enter, făcând experiența mai dinamică. 
-Mesaje dinamice– Afișează mesaje precum „System infected! ⚠️” la fiecare greșeală și „Virus eliminated! 💾✅” la câștig. 
-Finalizare joc – Dacă jucătorul ghicește cuvântul, jocul afișează un mesaj de victorie. Dacă pierde, sistemul „se prăbușește” cu o simulare de ecran albastru (BSOD).

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

-Desenarea interfeței: Se afișează cuvântul cu literele ghicite. Se actualizează desenul virusului. Se afișează mesajele corespunzătoare progresului.

-Finalizarea jocului: Dacă toate literele sunt ghicite → „Virus eliminated!” Dacă se atinge numărul maxim de greșeli → „SYSTEM FAILURE” + simulare de BSOD.

3.Elemente speciale și efecte vizuale Pentru a face jocul mai interactiv, ncurses ne permite să implementăm: 
-Animarea virusului: Pe măsură ce se fac greșeli, un virus ASCII se mărește pe ecran. 
-Highlight pe litera introdusă: Cursorul poate evidenția ultima literă introdusă. 
-Efect de „ecran stricat”: Cu cât sunt mai multe greșeli, cu atât apar mai multe caractere haotice pe ecran.

Acest joc oferă o experiență captivantă printr-o tematică inovatoare, utilizând ncurses pentru o interfață mai atractivă în terminal. Implementarea este simplă, dar permite extinderi ulterioare pentru a crește complexitatea și interactivitatea. „Virus vs. Antivirus” nu este doar un simplu Hangman, ci un concept modernizat care combină educația cu divertismentul! Let's fight the virus! 💾🚀
