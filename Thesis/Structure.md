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
    * Bevezetés:
        * [Volume rendering felhasználás](https://developer.nvidia.com/gpugems/gpugems/part-vi-beyond-triangles/chapter-39-volume-rendering-techniques)
        * [VolumeRendering definíció](https://www3.cs.stonybrook.edu/~mueller/papers/volvisOverview.pdf)
    * Teknikák (**[Összefoglaló *(2.1)*](./Docs/lacroute_thesis.pdf)**):
        * Marching cubes
            * [pdf](./Docs/paper_jbcs_november2012.pdf)
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
    * Sűrűségfüggvények ([Összefoglaló](./Docs/master%20thesis.pdf)):
        * Blinn:
            * [ref](./Docs/357306.357310.pdf)
        * Wyvill:
            * [ref](https://www.academia.edu/5738656/Animating_soft_objects)
* Optimalizálás **(5 oldal)**

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
