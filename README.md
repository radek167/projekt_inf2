Radosław Leszczyński<br>
gr.1a, ARiSS<br>
sem. 3<br>
<br>
Projekt z przedmiotu Informatyka II - Projekt w C++ dla semestru 3.<br>

<br>Przedstawionym projektem stanowi gra Arkanoid napisana w języku C++ z wykorzystaniem biblioteki SFML w wersji 3.0.<br>
<br>
Gra polega na odbijaniu piłki przy pomocy paletki sterowanej klawiaturą poprzez przyciski WASD lub strzałkami. Celem rozgrywki jest osiągnięcie jak najwyższego wyniku. <br>
Za każdą zniszczoną cegiełkę gracz otrzymuje punkty (10p). Gra kończy się, gdy piłka spadnie poniżej paletki i wypadnie poza ekran gry.<br>
Ponadto podczas rozgrywki możliwe są do zdobycia bonusy. Pojawiają się one po zniszczeniu klocka (szansa 20%). Bonusami są powiększenie paletki, bądź tryb "EasyMode", który polega na obniżeniu poziomu rozgrywki (klocki, które mają wytrzymałość większą niż 1, są zmieniane na poziom 1). <br>
<br><br>
Za pomocą menu można uruchomić grę (za pomocą "Nowa gra"), wczytać zapis gry ("Wczytaj grę"), sprawdzić ostatnie wyniki w tabeli wyników ("Ostatnie wyniki"), oraz wyjść z gry. 
<br>
<br> Objaśnienie kolorów klocków:<br>
Zielony klocek - wytrzymałość 1<br>
Żółty klocek - wytrzymałość 2<br>  
Czerwony klocek - wytrzymałość 3<br>
Bonus - mniejszy kwadratowy klocek spadający<br>


<br>
Sterowanie:<br>
WASD lub strzałki - poruszanie paletką<br>
ESC - powrót do menu<br>
F5 - zapis stanu gry<br>
<br>

Umieszczone pliki w repozytorium stanowią jednolity projekt C++ otwieralny w programie CLion. <br> W folderze głównym znajdują się wszystkie pliki formatu .cpp i .h niezbędne do kompilacji. <br> 
W folderze "cmake-build-debug" znajduje się plik wykonywalny gry w formacie ".exe" oraz wszystkie potrzebne pliki .dll itp. do funkcjonowania gry. <br>

Istotne jest, aby podczas uruchomienia projektu np. w Clion, zmienić ściezkę umiejscowienia SFML na dysku na własną. 

