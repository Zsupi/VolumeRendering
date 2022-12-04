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
        * ✅ Marching cubes
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
        * ✅ Ray Casting
            * [pic](./Pics/raycasting.svg)
                * [ref](https://martinopilia.com/posts/2018/09/17/volume-raycasting.html)
            * [pic](./Pics/Jaw_Skin.jpg)
                * [ref](https://web.cs.wpi.edu/~matt/courses/cs563/talks/powwie/p1/ray-cast.htm)
            * [pdf](./Docs/vis03-rc.pdf)
            * [link](https://web.cs.wpi.edu/~matt/courses/cs563/talks/powwie/p1/ray-cast.htm)
                * Célja, hogy lehetőseget adjon 3 dimenziós adatok kirajzolására gometriai primitívek nélkül.
                * Megoldást nyújthat az SF technológiák izo-felület generálásának legnagyobb hátrányára, mégpedig hogy nem csak egy vékony felszíni rétegét jeleníti meg a vizsgált térnek. Így az anyag minőségét (pl.: átlátszóság) is egyszerően tudjuk szemléltetni.
                * A legtöbbet használt térfogati vizualizációra használt ray casting a Blinn/Kajiya modellre épít.
                * Csillapitás stb ha nem elég amit írtam
            * [link](https://martinopilia.com/posts/2018/09/17/volume-raycasting.html)
                * Az algoritmushoz szükséges, hogy a viewport minden pixeléből képezzünk egy sugarat. Minden sugár esetében meg kell vizsgálnunk, hogy az az adott térfogati adathalmaz tekitetében melyik ponton érkezik be és melyik ponton távozik.
                * Ha ezt a két pontot ismerjük, triviális mintavételezni, és az összegyűjtött értékeket felhasználni az árnyalás végrehajtásához.
                * Az egyik legegyszerűbb változata a ray castingnak a two-pass ray casting. A technika neve abból ered, hogy a renderelést 2 GPU drawcall segítségével valósítjuk meg.
                    * Először a kiszámoljuk a sugár korábban említett bemeneti és kimeneti pontját.
                    * Ezután a bemeneti pontjait egy A framebufferbe, kimeneti pontjait egy B framebufferbe tároljuk el.
                    * A következő hívásban egy teljes képernyű méretű vászon minden pixelében mintát veszünk a korábban említett textúrából (A framebuffer és B framebuffer), ezek nyújtják a sugarunk kezdő és végpontjait. Ha a kezdő és végpont koordinátája megegyezik abban az esetben a pixelhez képzett sugár nem találata el az objektumot.
                    * Ezután végig iterálunk kellűen kicsi lépésekkel a kezdő és végpont között, majd mintavételezzül minden pontban a volumetrikus adatot.
                * Bár ez a legegyszerűbb megközelítés, a kétszeres renderelés nem nyújt optimális megoldást. Egy hívásban ezt a két pontot egy, a térfogati adatot kellően közelítő geometriai objektum metszéspontjaival tudjuk elérni. Ennek legegyszerűbb esete e kocka.
                * Ebben az esetben a kocka és a pixelből képzett sugár (félegyenes) 2 metszéspontja adja a sugár kezű és végpontját.
        * Splatting:
            * [pdf](./Docs/lacroute_thesis.pdf)
        * Sheare-wrap:
            * [pdf](https://www3.cs.stonybrook.edu/~qin/courses/visualization/visualization-shear-warping.pdf)
            * [videó](https://www.youtube.com/watch?v=17uH8PZnWts&ab_channel=BobLaramee)
* Metaball **(5 oldal)**
    * ✅ Bevezetés:
        * [pdf](./Docs/Image-Space_GPU_Metaballs_for_Time-Dependent_Parti.pdf)
            * A metaball technikát Blinn mutatta be először mulekuláris modellek megjelenítéséhez. Blinn eredetileg a metballokat blob-oknak hívta.
                * [ref](http://papers.cumincad.org/data/works/att/6094.content.pdf)
            * A metaballok megjelenítésére, a volume renderinghez hasonlóan, 2 lehetőségünk van: vagy izo-felületet generálunk a metaballok felszínéből, vagy ray marching és sűrűségfüggvények segítségével jelenítjük meg azokat.
            * Mataballok tekintetében az image-space alapú algoritmusok (például Ray Marching) sokkal szebb eredényt, simább felületet tudnak megjeleníteni.
        * [pdf](http://cg.iit.bme.hu/~szecsi/cikkek/metaball12/meta.pdf)
            * A metaballok részecske szimulációk, lágytestek és implicit felületek megjelenítésnek széles körben elterjedt eszköze.
            * A metaballok felületének leképzéséhez használt algoritmusok (pl: korábban bemutatott Marching Cubes) voxelizációs folyamatának köszönhetően szögletesnek mondható jelenséget tudnak okozni nagy méretű mintavételezésnél, emelett nagy felbontás mellett nagy memóriát és hosszú számítást igényelnek.
        *[pic](./Pics/Screenshot%202022-12-03%20201249.png)
            * [ref](https://www.diva-portal.org/smash/get/diva2:833519/FULLTEXT01.pdf)
        * Minden metaballt egy density-function, azaz sűrűségfüggvény alapján határozunk meg amit a kamerapozícióból indított sugár valamennyi pontjában ellenőrzünk.
    * ✅ RayMarching:
        * ✅ Mi a raymarching:
            * [video](https://www.youtube.com/watch?v=BNZtUB7yhX4&ab_channel=SimonDev)
                * Egy jól ismert algoritmus komplex testek kirajzolására, melyhez elegendő információ, egy pont és egy objektum felületének távolsága, a Ray Marching.
                * A Ray Marching signed distance function-ökre, azaz előjeles távolságfüggvényekre épít. Ha például egy kört szeretnénk kirajzolni, akkor a következő távolságfüggvényt kell alkalmaznunk.
                * A Ray Marchingot természetesen tudjuk akár 3 dimenziós térben is alkalmazni.
            * [link](https://iquilezles.org/articles/rmshadows/)
                * Ray Marching mindezek mellett lehetőséget ad nekünk, hogy szinte ingyen tudjunk lágy árnyékokat számolni.
                * Az ehhez használt legegyszerűbb eljárás, ha egy az adott felületi metszéspontból a fényforrás felé mutató irányvektor irányába elindulunk. Ha közben eltaláljuk a világ egy objektumát, akkor árnyékolhatjuk az adott interszektált pontot.
                * Az árnyékolás egy implementációja Sphere Tracing alkalmazásával.
        * ✅ Signed distance functions
            * [link](https://jamie-wong.com/2016/07/15/ray-marching-signed-distance-functions/#signed-distance-functions)
                * Az egyenlet egyik hatása, ha az adott pont (melyre a képletet alkalmaztuk) az objektum belsejében található, a végeredmény negatív lesz. Ezert nevezik előjeles távolságfüggvénynek
            * [Távolság-függvények](https://iquilezles.org/articles/distfunctions/)
            * [pic](https://iquilezles.org/articles/smin/)
        * ✅ Normál vektor:
            * Az eltalált objektum adott pontjában felvett normál vektorát, úgy tudjuk kiszámolni, hogy a metszéspontból az X és Y tengely irányába elmozdulunk kellően kicsi epszilon nagyságot, majd vesszük az így kialakult két vektor keresztszorzatát.
            * Az kiszámolt normálvektorok segítségével már könnyedén tudjuk akár árnyalni is a megjelenített metaballokat.
        * ✅ Sphere tracing:
            * [video](https://www.youtube.com/watch?v=BNZtUB7yhX4&ab_channel=SimonDev)
                * Az signed distance functionnak (SDF) segítségével a megjelenítni kívánt világ bármely pontjából meg tudjuk mondani, hogy mekkora távolságra van a legközelebbi objektum.
                * Ha ezt a kamera pozíciójából indított sugár egy tetszőleges pontjára alkalmazzuk, akkor meg tudjuk ezzel állapítani, hogy a onnan mekkora távolságot haladhatunk előre a sugár irányvektorának irányába.
                * Ha a legközelebbi objektumtól mért távolság elérte a megadott epszilon küszöbértéket, akkor eltaláltuk az objektumot.
                * A Ray Marchingnak ezt a változatát Sphere Tracingnek nevezik.
                * A Sphere tracing sokkal gyorsabb lefutást eredményez, hiszen nem csak kellően kicsi távolságot járunk be minden sugár irányába ezáltal.
                * [pic](https://www.researchgate.net/figure/Illustration-of-the-sphere-tracing-algorithm-in-2D_fig1_329152931)
    * Sűrűségfüggvények:
        * [Összefoglaló](./Docs/master%20thesis.pdf)
            * A metaballokkal való modellezés kulcsfontosságú elemei a sűrűségfüggvények.
        * Blinn:
            * [pdf](./Docs/Image-Space_GPU_Metaballs_for_Time-Dependent_Parti.pdf)
                * Blinn eredeti ötlete onnan származott, hogy a molekulák izo-felületét szerette volna megjeleníteni egy elektron sűrűségfüggvényének segítségével. Magát a képletet a hidrogén atom sűrűség függvényéből származtatta.
        * Wyvill:
            * [ref](https://www.academia.edu/5738656/Animating_soft_objects)
        * Nishimura:
            * >fi⁢(r)={1-3⁢(rRi)2 if (0≤r<R3)32⁢(1-(rRi))2 if (R3≤r≤Ri)(2)
            * Nishura egy kvadratikus térfüggvény hasznalt az egyes metaballok megjelenítéséhez
        * [ref](./Docs/357306.357310.pdf)
            * A Metaballok egy halmazát az egyes Metaballok sűrűségfüggvényei értékeinek összegzésével reprezentálhatjuk.
            * A felület ezután a abban a pontban megjeleníthető, amely kielégíti a következő egyenletet
            [pdf](./Docs/master%20thesis.pdf)
                * Ahogy az ábrákon is látható az különböző sőrőségfüggvények mind máshogy közelíti meg a metaball kirajzolását és annak, J.F.  Blinn szavaival élve, "bllobiness" megjelenését.
                * Az ábrákat azonban közelebbről vizsgálva mind hasonló eredményt mutatnak, tehát ennek követkézményeképp, a különböző térfüggvények hasonló metaballokat kell eredményezniük
            * [pic](./Pics/Screenshot%202022-12-04%20011638.png)
                * [ref](./Docs/master%20thesis.pdf)
    * Optimalizálás **(5 oldal)**
        *Bevezetés:
            * [pdf](http://cg.iit.bme.hu/~szecsi/cikkek/metaball12/meta.pdf)
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
    * Marching Cube

## 7. Összegzés **(1 oldal)**

## 8. Köszönetnyilvánítás **(1 oldal)**

## 9. Irodalomjegyzék **(2 oldal)**

## 10. Függelék **(2 oldal)**

* UML diagram
* Signed distance functions

## Sum

> * Elvárt: 40
> * Tervezett: 53 oldal
