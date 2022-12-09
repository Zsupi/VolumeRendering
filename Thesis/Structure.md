# 2022 Szakdolgozat

> [Segítség](https://www.scribd.com/document/257034196/Utmutato-vegz%C5%91s-informatikus-es-villamosmernok-hallgatoink-szamara-BME-VIK-2011)

## 1. Formai információk **(6 oldal)**

* Fedlap **(1 oldal)**
* Diplomaterv feladatkiírás **(1 oldal)**
* Tartalomjegyzék **(1 oldal)**
* Önálló munka nyilatkozat **(1 oldal)**
* Absztrakció *(angol, magyar)* **(2 oldal)**
    * csak sugárkövetésen alapuló megközelítések optimalizálása

## 2. Bevezetés **(1 oldal)**

[ref](https://www.flushinghospital.org/newsletter/history-of-medical-imaging-a-brief-overview/#:~:text=The%20concept%20of%20medical%20imaging,photosensitive%20plate%20placed%20behind%20it.)

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

## 4. Előzmények *(irodalomkutatás)* **(15 oldal)** **(jelenleg: 12 oldal)**

* ✅Volume rendering
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
* ✅RayMarching
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
* ✅Metaball
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
    * ✅ Sűrűségfüggvények:
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
    * ✅Optimalizálás **(5 oldal)**
        * ✅ Bevezetés:
            * [pdf](./Docs/eg08_metaballs.pdf)
                * A sugárkövetésen alapuló technikák elsődlegesen a megjelenített kép felbontásától függnek.
                * Ezek az algoritmusok képesek sima felületeket akár nagy felbontásban is megjeleníteni, akár kisebb objektumokra is.
                * Azonban ez általában nagy számítási kültséggel jár.
            * [pdf](./Docs/Karakteranimacio-altal-vezerelt.pdf)
                * Nagy számú Metaballok esetén valós időben önmagában nem alkalmazható.
                * A valós idejű kép előállításának érdekében különböző gyorsítási technikákat szükségés alkalmaznunk.
            * [link](https://learnopengl.com/Guest-Articles/2020/OIT/Introduction)
                * Az A-Buffer és S-Buffer algoritmusok pixelenkénti akár többszintes információk tárolására alkalmasak.
                * A két eljárást legtöbbet az order independet transparancy, avagy a sorrend független átlátszóság elérésére használják.
            * [link](https://dl.acm.org/doi/pdf/10.1145/800031.808585)
                * Az eltárolt információk alapján lehetőségünk van ezeket e technológiákat a pixelenkénti releváns metaballok előszűrésére hesználni.
        * A-Buffer:
            * [pic](./Pics/Screenshot%202022-12-04%20145646.png)
                * [ref](https://www.geeksforgeeks.org/a-buffer-method/)
            * [link](https://www.geeksforgeeks.org/a-buffer-method/)
                * Az A-Buffer metódus a számítógépes grafikában általában egy rejtett objektumok detektálási metódus, amely közepes méretű virtuális memóriával rendelkező környezetekre alkalmas.
                * A módszert Anti-Aliased vagy Area-Averaged bufferként is ismerik
                * Az algoritmus 2 kulcsfontosságú struktúrális elemre épít. Az egyik struktúrális elem egy 2 dimenziós tömb, a másik pedig egy láncolt lista.
                * A 2 dimenziós tömb mérete a megjeleníteni kívánt kép pixeleinek számával egyenlő. Minden eleme (legegyszerűbb esetben) egy előjel nélküli egész számot tárol. Ez a szám jelenti az általa reprezentált pixelhez tartozó láncolt lista első elemének azonosítóját.
                * A láncolt lista egy eleme 2 relevásn információt tárol. Egyrészt tartalmazza az általa reprezentált objektum tulajdonságait, például az Objektum színét, kamerától való távolságát vagy pozícióját, másrészt a láncolt lista következő elemét.
                * Az algoritmus egyik legnagyobb hátránya, hogy nagy mennyiségű adat vagy nagyobb felbontás esetén sok memóriára van szükség. A lefoglalt memória mennyiségén javíthatunk ha megadjuk, a pixelenkénti maximális lefoglalható memória nagyságát. Ebben az esetben rendezést szükséges alkalmaznunk, hogy a maximális mérető elemek közé elsősorban a kamerához közelebb lévő objektumok kerüljenek be.
                * Ámbár ez javít a memóriahasználaton, figyelembe kell vennünk, hogy ez a megközelítés nem minden esetben jelent számunkra megoldást. Lehetnek olyan szituációk, amikor értékes információt vesztünk el ezáltal.
            * [pdf](./Docs/tvcg-kbuffer.pdf)
                * A rendezésen nagymérető objektum-halmaz esetén javíthatunk, ha a láncolt lista struktúrát lecseréljük egy bináris fa struktúrára.
            * [pdf](./Docs/Karakteranimacio-altal-vezerelt.pdf)
        * S-Buffer:
            * [pdf](./Docs/eg2012_s-buffer.pdf)
                * Az A-Buffer memóriaigényes negatívumára megoldást nyújthat az S-Buffer. Az S-Buffer egy hatékony és memóriabarát algoritmus, amely az A-Buffer architektúrájára epül, anélkül hogy láncolt listákat és fix hosszúságú tömböket használna.
                * az A-Bufferhez képest egyel több renderelési lépést hajtunk végre, amelyben megvizsgáljuk pontosan mekkora memóriára van szükségünk.
                * Megfigyelhetjük hogy ámbár memóriahasználatban sikerült javulást elérnünk, a plusz egy renderelési hívással nagy mértékű lassulást is tapasztalhatunk.
        * Említésre méltó algoritmusok:
            * [pdf](./Docs/eg08_metaballs.pdf)
                * Kanamori és társai az egyes pixelekhez tartozó objektumok számának csökkentése mellett a metaballok felületének gyors tesztelésével közelítették meg a problémát.
            * [pdf](http://cg.iit.bme.hu/~szecsi/cikkek/metaball12/meta.pdf)
                * A késöbbiekben az algoritmuson L. Szécsi és D. Illés, az eljárás legköltségesebb aspektusának, a Bezier Clippingnek, köbös sűrűségfüggvény közelítéssel való lecserlésével gyorsítottak.

## 5. Tervezés **(22 oldal)** **(jelenleg: 14 oldal)**

* ✅Framework **(2 oldal)**
    * Bevezetés
        * GLEW és Freeglut nyújtotta lehetőségeket
        * jegyzet:
            * A projekthez a "boilerplate" kódok elrejtése (Shaderek betöltése, erőforrások bindolása), a könnyebb bővíthetőség és átláthatóbb struktúra érdekében készítettem egy egyszerűbb keretrendszert, amely statikus könyvtárként (lib) kerül be a projektbe.
            * A keretrendszer egyszerűbb geometriák kirajzolása mellett segíti a fejlesztőt a háttérben történő OpenGL hívások elrejtésével
            * A vektorok és mátrixok struktúrált kezelése érdekében az OpenGL-hez készített GLM könyvtárat használom.
    * Fontosabb elemei
        * Program:
            * Uniformok memóriahelyének cachelése
            * Sahderek betöltése és bekötése
        * Uniformok
        * Textúrák
            * stb_image
                * [ref](https://solarianprogrammer.com/2019/06/10/c-programming-reading-writing-images-stb_image-libraries/)
        * Bufferek
            * Általános
                * Az OpenGL bufferei kezelésének öszetett kódjára elkészített Buffer osztályok Victor Gordan struktújára épülnek, ezzel megkönnyítve azok menedzselését.
                * Ezen közül a két legfontosabb említésre méltó osztály az SSBO és az ACBO.
                * Victor Gordan bufferei
            * SSBO
                * std430-as SSBO
                    *[ref](https://www.khronos.org/opengl/wiki/Interface_Block_(GLSL)#Memory_layout)
                * [ref](https://www.khronos.org/opengl/wiki/Shader_Storage_Buffer_Object)
* ✅Volume rendering **(1 oldal)**
    * Eleinte egyszerű lineáris Ray Marching
        * Adatok Ellenőrzésére
    * Későbbiekben Metaballok
    * Bounding box:
        * [pdf *(4.1.1)*](./Docs/FULLTEXT01.pdf)
* ✅Metaball **(6 oldal)**
    * ✅Bevezető
        * Wyvill
            * [ref](https://www.academia.edu/5738656/Animating_soft_objects)
    * ✅Sűrűségfüggvények
        * Wyvill
            * [pdf](http://cg.iit.bme.hu/~szecsi/cikkek/metaball12/meta.pdf)
                * az egyik legszélesebb körben ahsznált sűrűségfüggvény a Wyvill hatod fokú egyenlete. A megközelítés előnye, hogy véges Rj támogatása van pj(r) = 0. r>= Rj esetén. Ezen kívül r < Pj esetén pedig polinomiális képlettel megadható egyenlet jellemzi, amely biztosítja az egyszerű kiértékelést.
                * Ezeket az előnyöket Perlin ötöd fokú változata is biztosítja, viszont észrevehetjük, hogy Wyvill és társai által definiált képlet minden vektorhosszúságot tartalmazó tagja páros hatványkitevőn szerepel. Ennek köszönhetően a képletet átalakítva elkerülhetjük a gyökvonásból eredő számítási időt.

            ``` cpp
                float wyvillMetaball(float distance, float radius) {
                    if (distance > pow(radius, 2)){
                        return 0.0f;
                    }

                    float fi = 1.0f - 3 * distance / pow(radius, 2) + 3 * pow(distance, 2) / pow(radius, 4) - pow(distance, 3) / pow(radius, 6);
                    return fi;
                }

                float wyvillMetaballTest(vec3 p, vec4 metaballCenter) {
                    float mannhattanistance = dot(p - metaballCenter, p - metaballCenter);
                    float f = wyvillMetaball(mannhattanistance, 0.2f);
                    return f;
                }
            ```

    * ✅Raymarching
        * Lineáris ray marching kellően kicsi lépéssel
        * Sphere marching
            * képlet step-hez
        * 6x6x6-os kocka fps-el
    * ✅Modell felépítése:
        * CPU
        * Compute Shader
            * [link](https://www.khronos.org/opengl/wiki/Compute_Shader)
            * Megszokott megjelenítő csővezetéktől függetlenül fut
            * A Compute shadernek nincsenek a felhasználó által definiált bemeneti, viszont beépített bemenetekkel rendelkezik. Ha a shadernek égis szüksége lenne bemeneti értékekre, akkor például textúrákkal és Shader Storage Bufferekkel megadhatjuk azokat neki. Ehhez hasonlóan egy Compute Shader számításainek kimeneteit szintén egy képpel vagy SSBO-val tudjuk elérni.
            * A Compute Shader Work Groupokból épül fel. A Felhasználó definiálhatja, hogy a hány Work Groupot szeretne futtatni. Ezek futásának sorrendje nem egyenletes, tehát például lehetséges, hogy a (2,4,5)-ös után az (1,1,1)-es Work Group kerül lefutásra.
            * Egy Work Groupon belül akár több Shader Invokáció is lehet. A különböző invokációk egymástól eltérően és párhuzamosan futnak.
        * GPU
            * SSBO-val
            * Kódrészlet
* ✅A-Buffer **(5 oldal)**
    * Bevezetés
    * Felépítés
        * Bevezetés
            * Pixel, Linked List SSBO
            * Az A-Buffer struktúrája három Shader Storage Bufferből és egy Atomic Counter Bufferből épül fel.
            * A három SSBO a screenBuffer, a linkedListBuffer és positionBuffer nevekre hallgatnak. A linkedListBuffer elemei uvec2 típusúak, a és a láncolt lista egyes elemeit reprezentálják. Az elemek első adattagja tárolja a láncolt listában őt megelőző elem indexét, második eleme a láncolt listához tartozó metaball indexe. A screenBuffer előjel nélküli egész számok segítségével tárolja a pixelhez tartozó láncolt lista utolsó elemét. PositionBuffer a Compute Shader által elkészített Metaballok pozícióit tárolja.
            * Az Atomic Counter Bufferre a Compute Shaderhez hasonlóan a láncolt lista bufferének megfelelő kezelése miatt van szükség.
            * [kép a felépítésről]
            * ABuffer osztály
                * SSBO struktúra
                * Az A-Bufferhez használt buffereket egy ABuffer osztályba struktúráltam.
    * Feldolgozás
        * Billboardok
        * Adatok feldolgozása
            * ábra a felépítésről
    * Megjelenítés
        * flow chart a technika mőködéséről

## 6. Értékelés **(4 oldal)**

* Specifikáció:
    * processzor: AMD Ryzen 9 5980HS 3.30 GHz
    * Videókártya: AMD Radeon Graphics
    * VRAM: 512 MB
    * RAM: 32GB
    * Windows 11
    * C++20
    * GLSL version 430
* Átlag FPS mataballszámoktól függően

* Eredmény:
    * Az Orvosi térfogati adatok Metaballokkal történő kirajzolása fizikailag szimulálható állapotot eredményeznek. Kellően nagy Metaball-szám esetén az eredmény pontos és részletes képet tud adni.
    * A továbbiakban megvizsgáljuk a Metaballok optimalizált mérési adatait.
    *[kép]
    * A mérési adatokból láthatjuk, hogy a teszteléshez használt laptop videókártyájának memóriája már 8000 Metaball esetén is szinte teljes kihasználás alatt van.
    * A mért értékek jól prezentálják az A-Buffer algoritmus legnagyobb hátrányát, a túlzott memóriahasználatot. Már 8000 Metaball mellett is elérte a teszteléshez használt laptop videókártyá-memóriájának maximumát.
    * A mérési adatokból láthatjuk, hogy 8000 Metaballt interakcióra képes állapotban tudunk megjeleníteni. Az A-Buffer struktúrált adatainak összeállítása a mérési adatok alapján eltérő Metaball-számokat vizsgálva elenyésző különbségeket tapasztalunk.
    * Ezek alapján levonható a következtetés, hogy az algoritmus szűk keresztmetszetét a memóriából származó korlátok és a pixelenként nagyszámban eltárolt metaballok megjelenítése adja.

## 7. Továbbfejlesztési lehetőségek

* Az előző fejezet végén elemzett problémák

* RayMarching:
    * A megalkotott algoritmus szűk keresztmetszetét a sugárkövetés nagy számításigénye adja.
    * Ennek megoldására a jövőben egy szécsi László polinomiális approximációját alkalmazni.
* A-Buffer:
    * Bináris fa struktúra láncolt lista helyett
    * //Bufferek inicializálása fix méretű tömbökkel//
    * S-Bufferhez hasonlóan egy további renderelési ütemben szeretném az adott pixelhez tartozó maximális metaball számot meghatározni, melynek segítségével egy rendezett fa struktúrát szeretnék felépíteni. Ha az adott pixel elérte maximális elemszámat, akkor a legnagyobb elemet lecserélve adja hozzá az új metaball azonosítót.
* Framework:
    * Inkrementálisan vizualizált objektumok megjelenítése
* Marching Cube

* [szecsi]
* [ref](./Docs/tvcg-kbuffer.pdf)
* [ref](https://hu.weblogographic.com/difference-between-binary-search-and-linear-search-1730)

## 8. Összegzés **(1 oldal)**

## 9. Köszönetnyilvánítás **(1 oldal)**

## 10. Irodalomjegyzék **(2 oldal)**

## 11. Függelék **(2 oldal)**

* UML diagram
* Signed distance functions

## Sum

> * Elvárt: 40
> * Tervezett: 53 oldal
