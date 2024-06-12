# PST Modern Cryptography
- GUILLARD Nicolas
- DAUBIGNÉ Méline
- IZARD Antoine
- MOISIS Nolann



## Mini AES

Instance
```
  4 * * * * (message)
  4 * * * * (clé)
```
Nombre de ronde
```
  int roundCount = *;
```
Compilation 
(Allez dans le dossier Mini-AES)
```
  gcc -O3 *.c -lm
  ./a.out
```

## ToyCipher

Décommenter une des trois lignes
```
  #define SBoxLineaire (Sortie dans le fichier linearProbability.txt)
  #define SBoxDifferential (Sortie dans le fichier differentialProbability.txt)
  #define ToyCipherHRPD (Sortie dans le terminal)
```
Compilation 
(Allez dans le dossier ToyCipher)
```
  gcc -O3 *.c -lm
  ./a.out
```

## Biclique

Compilation 
(Allez dans le dossier AES_Biclique)
```
  gcc -O3 *.c -lm
  ./a.out
```
## Lien Presentation comme le salon

https://www.canva.com/design/DAGDPYWCdeQ/ciZl1-cmZQhfDqDobIgDgQ/edit?utm_content=DAGDPYWCdeQ&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton