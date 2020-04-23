# Labo "Tri de texte intelligent"

## Objectifs
Les principaux buts de ce travail de laboratoire sont de :
- utiliser les chaînes de caractères et les tableaux,
- tester votre code.

## Durée
La durée encadrée de ce labo est de 4 x 45 minutes.

## Qualité du code C
-  un commentaire au début du fichier source devra mentionner le nom du labo, votre nom et prénom,
-  un commentaire à la fin du fichier source devra exposer les tests que vous avez réalisés,
-  si nécessaire, quelques commentaires pourront être placés dans le code source afin d'aider le lecteur à comprendre,
-  nommez correctement vos variables,
-  choisissez correctement les types de données,
-  respectez les noms imposés pour les fonctions,
-  lors de toute saisie de valeur numérique, vous devez prendre les précautions d'usage pour un fonctionnement correct, même si l'utilisateur saisit un donnée inadaptée.

## Cahier des charges

Vous devez programmer un logiciel en C permettant de trier des chaînes de caractères passées en arguments au programme.

Il y a deux tris à implementer:
 - alphabétique : les chaines sont triées d'après les caractères ASCII,
 - numérique : les chaines sont triées par ordre croissants des nombres dans les chaines.

Le programme doit fonctionner peu importe le nombre de chaine à trier, et la taille maximale d'une chaîne (`\0` inclus) est de 128 caractères.

Plusieurs couples d'options (courte et longue) peuvent être passés au programme :
- `-h` ou `--help` affichent l'aide,
- `-c` ou `--count` affichent le nombre de chaines de caractères saisie,
- `-a` ou `--alpha` trient les chaines saisie selon l'ordre alphabétique,
- `-n` ou `--num` trient les chaines saisie selon l'ordre numérique.

L'affichage des chaînes triées sera réalisé **exactement** comme indiqué ci-dessous.

```bash
> ./app --alpha Track99 Track100 Track101                                        
Track100, Track101, Track99.
```

```bash
> ./app --num Track99 Track100 Track101                                         
Track99, Track100, Track101.
```

```bash
> ./app --num Track_2_99 Track_2_100 Track_2_101                                      
Track_2_99, Track_2_100, Track_2_101.
```

```bash
> ./app --count Track99 Track100 Track101
count: 3
```

```bash
> ./app --help
Usage: ./app [option] [strings]...

Option  Long option             Effect
-h      --help                  Displays this.
-a      --alpha                 Sorts according to ASCII table.
-n      --numeric               Sorts according to numbers in strings
-c      --count                 Displays number of strings.
```

<div style="page-break-after: always;"></div>

## Prototypes des fonctions imposées

Pour l'affichage du "comment" utiliser le programme, option `--help` :
```C
void usage(const char* app_name);
```

Pour l'affichage des `num_names` noms contenus dans le tableau `names` :
```C
void print_names(const uint32_t num_names, char* names[]);
```

Pour les tris des `num_names` noms contenus dans le tableau `names` :
```C
int sort_names(const uint32_t num_names, char* names[], action_type action);
```

`action_type` est un type énuméré indiquant l'option saisie par l'utilisateur.

## Code retour du programme

| N° | cas | code retour |
|---|---|---|
|1| option --help | 0 |
|2| aucune option | 254 |
|3| option --alpha suivie d'aucune chaîne | 253 |
|4| option --num suivie d'aucune chaîne | 253 |
|5| option --alpha suivie d'au moins 1 chaine | 0 |
|6| option --num suivie d'au moins 1 chaine | 0 |
|7| option --count suivie d'au moins 1 chaine | nombre de chaînes |

## Test du programme
Insérez, sous la forme d'un commentaire à la fin de votre code source, la copie des tests que vous avez effectués (copier-coller des informations visibles dans le terminal).

Pour afficher le code retour, utilisez la commande suivante dans le terminal `echo $?`

```bash
> ./app --count Track99 Track100 Track101                           
count: 3

> echo $?
3
```
