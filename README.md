# Duomen-siuntimo-grei-io-matuoklis


Šios užduoties tikslas sukurti programą, naudojant C programavimo kalbą, kuri
nustatytų interneto duomenų parsisiuntimo ir išsiuntimo greitį.

Atliekant užduotį, reikia panaudoti šias bibliotekas:
 libcurl
 getopt
 cJSON

Pridedamas papildomas failas pavadinimu speedtest_server_list.json. Šiame faile
yra pateiktas serverių sąrašas, kurie leidžia atlikti duomenų siuntimo testus. Kai kurie
serveriai esantys sąraše gali būti nebe veiksnūs.

Programa turi gebėti atlikti šiuos veiksmus:

 Atlikti duomenų parsiuntimo greičio nustatymo testą;

 Atlikti duomenų išsiuntimo greičio nustatymo testą;

 Atlikti geriausio serverio pagal vietovę nustatymą;

 Atlikti vietovės nustatymą (susirasti API, kuris leistų nustatyti vietovę);

 Atlikti visą testą automatizuotai;

Turi būti galimybė atlikti kiekvieną veiksmą pasirinktinai. Atliekant ne pilną testą, o
pasirenkant individualų veiksmą, reikia įvertinti kokius parametrus reikia perduoti,
kad tą veiksmą būtų galima atlikti. Pvz. Atliekant duomenų parsisiuntimo greitį, šiam
veiksmui reikia nurodyti kokį serverį naudoti.

Jeigu atliekamas automatizuotas testas, turi būti sudaryta atitinkama veiksmų seka,
kad visi veiksmai būtų atliekami logiškai.

Duomenų išsiuntimo ir parsiuntimo greitis turi būti išspausdinamas megabitais.
Duomenų išsiuntimo ir parsiuntimo greičio nustatymo testai turi trukti neilgiau 15
sekundžių. Po 15 sekundžių, veiksmas turi būti stabdomas.

Rezultatus išspausdinti veiksmo pabaigoje, jeigu individualus veiksmas yra
atliekamas, kitu atveju po visų veiksmų atlikimo. Viso testo metu informuoti vartotoją
apie programos statusą/eigą.

Išspausdinti šiuos duomenis:
 Duomenų parsisiuntimo greitį;

 Duomenų išsiuntimo greitį;

 Serverį, su kuriuo buvo atliktas testas;

 Vartotojo vietovė. Užtenka valstybės pavadinimo.
Implementuoti programoje klaidų valdymo logiką.
Programos rezultatą patalpinti github repozitorijoje.
Parašyti programos paruošimui Makefile.
