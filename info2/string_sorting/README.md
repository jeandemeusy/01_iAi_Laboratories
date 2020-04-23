# Labo01 "Tri de texte intelligent"

## **Objectifs**
Les principaux buts de ce travail de laboratoire sont de :
- utiliser les chaînes de caractères et les tableaux,
- tester votre code.

## **Durée**
La durée encadrée de ce labo est de 4 x 45 minutes.

## **Qualité du code C**
-  un commentaire au début du fichier source devra mentionner le nom du labo, votre nom et prénom,
-  un commentaire à la fin du fichier source devra exposer les tests que vous avez réalisés,
-  si nécessaire, quelques commentaires pourront être placés dans le code source afin d'aider le lecteur à comprendre,
-  nommez correctement vos variables,
-  choisissez correctement les types de données,
-  respectez les noms imposés pour les fonctions,
-  lors de toute saisie de valeur numérique, vous devez prendre les précautions d'usage pour un fonctionnement correct, même si l'utilisateur saisit un donnée inadaptée.

## **Cahier des charges**

Vous devez programmer un logiciel en C permettant de trier des chaînes de caractères passées en arguments au programme. L'affichage des chaînes triées sera réalisé **exactement** comme indiqué ci-dessous.

Il y a deux tri à implementer:
 - alphabétique : les chaines sont triées d'après les caractères ASCII.
 - numérique : les chaines sont triées en considérant les nombres présents dans les chaines comme tel, puis les tris par ordre croissant.



Le programme doit fonctionner peu importe le nombre de chaine à trier.
	
La taille maximale d'une chaîne (`\0` inclus) est de 128 caractères.

```bash
> ./app --alpha chaine12 chaine2 chaine1                                           
chaine1, chaine12, chaine2.
```

```bash
> ./app --num chaine12 chaine2 chaine1                                           
chaine1, chaine2, chaine12.
```

```bash
> ./app --num chaine12 chaine2 chaine1 chaine_longue                                       
chaine1, chaine2, chaine12, chaine_longue.
```

```bash
> ./app --num chaine1temp1 chaine1temp2 chaine1temp12                                   
chaine1temp1, chaine1temp2, chaine1temp12.
```

```bash
> ./app --count chaine12 chaine2 chaine1
count: 3
```

```bash
> ./app --help
Usage: ./app [options] [strings]...

Option  Long option             Effect
-a      --alpha                 ...
-n      --numeric               ...
```

<div style="page-break-after: always;"></div>

## **Prototypes des fonctions imposées**

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

Pour l'affichage de l'aide 
```C
int usage(char* app_name);
```

## **Code retour du programme**

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
> ./app --count chaine12 chaine2 chaine1                               
count: 3

> echo $?
3
```
