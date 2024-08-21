### Note cali v2 
Oproti první verzi je kalkulačka předělaná do frameworku Qt díky kterému je kalkulačka rychlejší a kompatibilní s linuxem i windowsem. Také přidávám další funkce jako syntaktické zvýrazňování.

> [!WARNING]
> I když kalkulačka je pořád ve vývoji, většina funkcí je plně funkčních a pod linuxem testována.\
> Pokud ovšem chcete kalkulačku používat na windows doporučuji, první verzi která je dokončená [NoteCali](https://github.com/Tolomaj/NoteCali/tree/withControler). Ta však nebude až na bugy udržovaná a nové funkce z v2 nedostane.

## Kompilace
Kompilování je testováné pouze na linuxu. \
Pokud chcete kompilovat pro windows použijte wsl nebo rovnou použijte předkompilované.

#### Kompilace pro linux:
```
make
```
Vytvoří v adresáři ./output/ spustitelný soubor **main** a rovnou ho spustí.\
Ve složce ./output/ také vznikde složka /tmp/ která obsahuje soubory vzniklé při kompilaci. Tu i se všemi vygenerovanými soubory odstraníte pomocí :
```
make clear
```

#### Kompilace pro windows (na linuxux nebo wsl):
```
make windows
```
Take vytvoří v adresáři output spustitelný soubor **main** ale soubor nespouští.