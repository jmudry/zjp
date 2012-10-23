Wszystko było testowane na procesorze cztero rdzeniowym i5 RAM=4GB

# Mnożenie macierzy kwadratowej przez wektor
### Dane
* wielkość macierzy 4000
* liczba procesów 4

### Rozwiązanie MPI
czas obliczeń = 0.40

### Rozwiązanie sekwencyne 
czas obliczeń = 0.063981

### Wniosek
Zbyt wiele komunikacji na tak prostych działaniach.

# Monte Carlo
### Dane
* liczba punktów: 100 000 000 
* liczba procesów: 4

### MPI z generowaniem punktów przez proses 0 i rozsyłanie punktów
czas obliczeń = 6.8 s

### Sekwencyjne 
czas obliczeń = 3.4 s

### MPI - każdy proces generuje sobie liczby 
czas obliczeń = 1.4 s

### wniosek
Testowanie na czterech procesach jest bardziej wydajne niż generowanie punktów przez jeden proces 
gdyż równie dobrze każdy może generować je dla siebie wyliczyć i zapomnieć o nich a musimy deklarować
wielką tablicę i rozsyłać do innych procesów.
Bez różnicy czy mamy metod sekwencyjną czy za pomocą mpi zawsze dostajemy conajmniej dwie dokładne liczby po przecinku.
Liczba punktów losowych zbytnio nie gra roli gdyż zależy to od generatora liczb losowych (ilość różnych).
# Liczenie całkie metodą trapezową
### Dane
* podział na 10000000
* liczba procesów: 4 

### MPI 
czas obliczeń ~ 0.4 s
* przy np = np. 8 
uzyskujemy gorszy w granicach 0.5-0.6 tracimy tu czas na komunikacje oraz jest to jedynie emuloanie procesu  bo sam w sobie nie ma 4 procesorów
* przy np=2 
mamy również gorsze rozwiązanie około 0.6 gdyż nie wykorzystaliśy do końca procesora:)

### Sekwencyjne 
czas obliczeń ~ 0.86s

### wniosek 
Jak widać w tym przypadku mamy lepsze rozwiązanie poprzez mpi 
Dla podziału dziesięciokrotnie większym otrzymujemy czasy: mpi: ~7s sekwencyjne: 11s czyli podobnie jak wyżej;)
Wynik w obu przypadkach bardzo zadowalający. Oczywiście nie różni sie.






