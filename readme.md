Wszystko było testowane na procesorze cztero rdzeniowym i5 RAM=4GB

# Mnożenie macierzy kwadratowej przez wektor
* wielkość macierzy 4000
* liczba procesów 4

### Rozwiązanie MPI
czas obliczeń = 0.40

### Rozwiązanie sekwencyne 
czas obliczeń = 0.063981

### Wniosek
Zbyt wiele komunikacji na tak prostych działaniach.

# Monte Carlo
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





