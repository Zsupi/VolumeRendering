# 2022 Szakdolgozat

> [Segítség](https://www.scribd.com/document/257034196/Utmutato-vegz%C5%91s-informatikus-es-villamosmernok-hallgatoink-szamara-BME-VIK-2011)

## 1. Formai információk **(6 oldal)**

* Fedlap **(1 oldal)**
* Diplomaterv feladatkiírás **(1 oldal)**
* Tartalomjegyzék **(1 oldal)**
* Önálló munka nyilatkozat **(1 oldal)**
* Absztrakció *(angol, magyar)* **(2 oldal)**

## 2. Bevezetés **(1 oldal)**

* Tervezés célja
    * Orvosi térfogati adatok megjelenítése fizikailag egyszerűen szimulálható módon
    * Valós időben
* Feladat indokoltsága
* Feladat felosztása:
    * Szakdolgozat két jól elkülöníthető részre bontható, a fizikai reprodukcióra alkalmas megjelnítés és a térfogati adat szimulálása az anyag adott pontban mintavételezett sűrűsége alapján.
    * Én feladatom az adatok vizuálása volt.
* Diplomaterv felépítése:
    * A továbbiakban a feladathoz szükséges forrásokat és kutatásokat szeretném bemutatni, majd utána az általam megvalósított módszerrel folyatni.

## 3. Feladatkiírás részletezése **(1 oldal)**

* Térfogati illumináció:
    * Metaballok:
        * wyvill desinity
        * Lágy testek
        * Részecskék
    * Raymarching
        * Metaballok-hoz
    * A-Buffer:
        * Valós időhöz
        * Optimalizáláshoz

## 4. Előzmények *(irodalomkutatás)* **(15 oldal)**

* Volume rendering **(5 oldal)**
    * ✅ Bevezetés:
        * [Volume rendering felhasználás](https://developer.nvidia.com/gpugems/gpugems/part-vi-beyond-triangles/chapter-39-volume-rendering-techniques)
        * Definíció:
            * [pdf](https://www3.cs.stonybrook.edu/~mueller/papers/volvisOverview.pdf)
            * [pdf](https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=274942&tag=1)
            * [pdf](https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=267473)
            * [pdf](./Docs/234313.234383.pdf)
            * [pdf](./Docs/paper_jbcs_november2012.pdf)
    * ✅ Teknikák (**[Összefoglaló *(2.1)*](./Docs/lacroute_thesis.pdf)**):
        * Marching cubes
            * [pdf](./Docs/paper_jbcs_november2012.pdf)
                * A térfogati adatok minden voxele feldolgozásra kerül.
                * Minden vertex elemre a mintavételezett adatot ellenőrizzük, ha az egy megadott *h* küszöb felett van, akkor az izo-felület külső, egyéb esetben belő elemének jelöljük.
                * Ezután háromszögek generálásával közelítjük az izo-felületet
                * Egy cellából a hároszögeket egy 15 elemű look-up table használatával generáljuk le.
                * Az algoritmust az üres cellák kíszűrésével gyorsíthatjuk.
            * [link](https://www.cs.carleton.edu/cs_comps/0405/shape/marching_cubes.html)
                * A eredmény pontosságát növelhetjük a Marching Cube-ok számának növelésével vagy az kocka metszéspontjainak elmozdításával.
            [link](https://code-specialist.com/python/marching-cubes-algorithm)
                * Minden megvizsgált cellának 8 csúcsa a korábban említett 2 értéket veheti fel (belül, vagy kívül). Ez összesen 2^8 = 256 különböző esetet eredményezhet.
                * A 256 eset közül viszont vannak, olyanok amelyek egymás szimetrikus megfelelői vagy komplemeterei. Így egy voxelhez összesen 15 különböző, egyedi esetet tudunk megfeleltetni.
                * Minden esethez generálunk egy egyedi azonosítót az alapján, hogy az adott cella mely csúcspontja a 2 érték melyikét vette fel.
                * Az eredmény pontosságát növelhetjük azal hogy az elkészített háromszög pontjait nem mintavételezett kocka éleinek középpontjába, hanem annak egy olyan pontjába, amely kellően közelíti a h határértéket.
                * Az algoritmus könnyen párhuzamosítható, hiszen minden kocka független egységként kezelhető.
            [pic](./Pics/Type-of-surface-combinations-for-the-marching-cube-algorithm-The-black-circles-means.png)
                * [ref](https://www.researchgate.net/figure/Type-of-surface-combinations-for-the-marching-cube-algorithm-The-black-circles-means_fig2_282209849)
            * Addition:
                * Az eljárás alapját egymástól független elemek (kockák) adják, ennek köszönhetően könnyen párhuzamosítható amivel könnyedén segíthetjük az algoritmus teljesítményét, emellett az üres cellák kiszőrésével is sokat javíthatunk ezen.
        * Ray Casting
            * [pdf](./Docs/vis03-rc.pdf)
        * Raymarching
            * [videó](https://www.youtube.com/watch?v=BNZtUB7yhX4&t=4s&ab_channel=SimonDev)
            * [Marcing vs Casting 1](https://www.kodeco.com/books/metal-by-tutorials/v2.0/chapters/18-rendering-with-rays)
            * [Marcing vs Casting 2](https://stackoverflow.com/questions/67347177/what-is-the-difference-between-ray-tracing-ray-casting-ray-marching-and-path-t)
            * [Távolság-függvények](https://iquilezles.org/articles/distfunctions/)
        * Splatting:
            * [pdf](./Docs/lacroute_thesis.pdf)
        * Sheare-wrap:
            * [pdf](https://www3.cs.stonybrook.edu/~qin/courses/visualization/visualization-shear-warping.pdf)
            * [videó](https://www.youtube.com/watch?v=17uH8PZnWts&ab_channel=BobLaramee)
        * Metaball:
            * Kisebb leírás
            * Utána nagyobb felyezet
* Metaball **(5 oldal)**
    * Bevezetés:
        * [pdf](./Docs/Image-Space_GPU_Metaballs_for_Time-Dependent_Parti.pdf)
    * Sűrűségfüggvények ([Összefoglaló](./Docs/master%20thesis.pdf)):
        * Blinn:
            * [ref](./Docs/357306.357310.pdf)
        * Wyvill:
            * [ref](https://www.academia.edu/5738656/Animating_soft_objects)
        * Nishiruma:
            * >fi⁢(r)={1-3⁢(rRi)2 if (0≤r<R3)32⁢(1-(rRi))2 if (R3≤r≤Ri)(2)
    * Optimalizálás **(5 oldal)**
        *Bevezetés
        * A-Buffer:
            * [pdf](./Docs/tvcg-kbuffer.pdf)
            * [link](https://www.geeksforgeeks.org/a-buffer-method/)
        * S-Buffer:
            * [pdf](./Docs/eg2012_s-buffer.pdf)
        * Bezier görbe alapú megjelenítés:
            * [pdf](./Docs/eg08_metaballs.pdf)

## 5. Tervezés **(22 oldal)**

* Framework **(4 oldal)**
* UML diagram **(1 oldal)**
* Volume rendering **(5 oldal)**
    * Bounding box:
        * [pdf *(4.1.1)*](./Docs/FULLTEXT01.pdf)
* Raymarching **(3 oldal)**
    * Algoritmus
* Metaball **(4 oldal)**
* A-Buffer **(5 oldal)**

## 6. Értékelés **(4 oldal)**

* A-Buffer:
    * Memóriahasználat (visual studio profiler)
    * Komplexitás
        * Bufferek inicializálásának ideje (mérd meg)
    * Átlag FPS mataballszámoktól függően
* Továbbfejlesztési lehetőségek:
    * A-Buffer:
        * Bináris fa struktúra láncolt lista helyett
        * //Bufferek inicializálása fix méretű tömbökkel//
    * Framework:
        * Inkrementálisan vizualizált objektumok megjelenítése

## 7. Köszönetnyilvánítás **(1 oldal)**

## 8. Irodalomjegyzék **(2 oldal)**

## 9. Függelék **(1 oldal ?)**

## Sum

> * Elvárt: 40
> * Tervezett: 53 oldal
