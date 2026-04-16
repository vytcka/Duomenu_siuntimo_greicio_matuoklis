# Duomen-siuntimo-grei-io-matuoklis

Būtinai turi būti įdiegtos šios bibliotekos:

- `libcurl` — HTTP užklausoms
- `libssl` / `libcrypto` — SSL palaikymui
- `libcjson` — JSON failų apdorojimui
- `libz` — suspaudimui

Ubuntu/Debian sistemoje:
sudo apt install libcurl4-openssl-dev libssl-dev libcjson-dev zlib1g-dev

## Kompiliavimas

Root direktorijoje įveskite:
make

## Naudojimas

./main -du    # atsisiuntimo ir įkėlimo greičių testas
./main -s     # randa geriausią serverį
./main -a     # visas testas su visais serveriais


## Pastabos

Kadangi dauguma serverių nerodo atsisiuntimo ar išsiuntimo duomenų, man nepavyko padaryti „libcurl“ bibliotekos pakankamai jautrios arba pasirinkau netinkamą API funkciją, tačiau pati programa vis tiek pateikia užtrunkanti laiką susiekti su serveriu.
