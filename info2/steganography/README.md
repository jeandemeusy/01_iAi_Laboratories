# Stéganographie <!-- omit in toc -->

- **Durée**: 2 périodes + environ 3h à la maison
- **Date de rendu**: dimanche avant minuit
- **Format**: travail individuel

## Contenu <!-- omit in toc -->

- [Objectifs](#objectifs)
- [Fichiers BMP](#fichiers-bmp)
- [Méthode](#m%c3%a9thode)
- [Directives](#directives)
- [Exécutable](#ex%c3%a9cutable)
- [Détails](#d%c3%a9tails)
- [Déroulement](#d%c3%a9roulement)
- [Rapport de test](#rapport-de-test)
- [Debug dans VsCode](#debug-dans-vscode)
- [Indices](#indices)
- [Encryption (Bonus)](#encryption-bonus)

## Objectifs

Ce travail pratique s'intéresse à la [stéganographie](https://fr.wikipedia.org/wiki/St%C3%A9ganographie) plus particulièrement dans des fichiers [BMP](https://en.wikipedia.org/wiki/BMP_file_format). La stéganographie est une technique ancienne permettant de dissimuler un message dans un objet, ici un fichier image. 

Le programme sur lequel vous contribuerez permettra d'encoder et de décoder des messages textes dans des fichiers BMP.

À titre d'exemple, et pour attiser votre curiosité, l'image suivante disponible dans `assets/elephant.bmp` contiens un message caché. Saurez-vous le trouver ?

![elephant](assets/elephant.bmp)

## Fichiers BMP

Un fichier BMP est composé de trois parties : 

1. Un en-tête de fichier contenant la taille du fichier et le format de l'image.
2. Un en-tête d'information contenant des informations sur l'image.
3. L'image à proprement parler sous forme d'une matrice.

Le fichier `bmp.h` contient les deux structures d'en-tête et la structure `BMP` utilisée pour charger en mémoire un fichier BMP. L'exemple suivant utilise la bibliothèque BMP pour faire un miroir horizontal d'une image :

```c
#include <stdio.h>
#include <assert.h>

#include "bmp.h"

int main()
{
    BMP *bmp = load_bmp("assets/blanche.bmp");

    // Ensure it is a 24-bit image
    assert(bmp->info.bit_per_pixels == sizeof(Pixel24Bits) * 8);

    // Create a matrix pointer
    int w = bmp->info.width, h = bmp->info.height;
    Pixel24Bits(*data)[h][w] = (Pixel24Bits(*)[h][w])bmp->data;

    // Flip image horizontally
    for (int col = 0; col < h; col++) {
        for (int row = 0; row < w / 2; row++) {
            Pixel24Bits *a = &(*data)[col][row];            
            Pixel24Bits *b = &(*data)[col][w - row];
            Pixel24Bits c = *a; *a = *b; *b = c;
        }
    }

    save_bmp(bmp, "flipped-blanche.bmp");
}
```

## Méthode

Chaque pixel de l'image, lequel peut-être encodé en 4-bit, 8-bit, 24-bits ou 32-bits, contient une information de couleur dont le bit de poids faible peut facilement être modifié sans altérer visiblement l'image. On peut par exemple essayer de forcer le bit de poids faible d'une image 8-bit ou 24-bit à zéro (voir sur Wikipedia comment est encodé un pixel selon le nombre de bits par pixel) et tenter d'y voir une différence. Vous pouvez essayer de modifier plus d'un bit et voir à partir de quand l'image est vraiment altérée.
```c
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main()
{
    BMP *bmp = load_bmp("assets/blanche.bmp");

    if (!(bmp->info.bit_per_pixels == 8 || bmp->info.bit_per_pixels == 24))
        exit(EXIT_FAILURE);

    for (int i = 0; i < bmp->info.image_size; i++)
        bmp->data[i] &= ~0x01;

    save_bmp(bmp, "altered-blanche.bmp");
}
```

Cette méthode de stéganographie, très faible du point de vue cryptographique, consiste donc à substituer le LSB de chaque valeur colorimétrique de l'image par un bit du message à encoder. Il faudra donc 8 informations colorimétriques pour encoder un byte du message, sachant qu'une image 24-bit à trois informations colorimétriques d'un byte chacune (R,V,B) par pixel.

Admettons que l'on souhaite encoder la valeur `0xaf` qui en binaire s'écrit : `10101111`, il faudra modifier 8 bytes de l'image. À la fin du message encodé, le caractère '\0' sera inséré comme sentinelle pour détecter la fin du message lors du décodage du message. 

Ainsi, pour une image couleur 24 bits on aura modifié les informations suivantes :

```text
Pixel Couleur LSB
  0   Bleu    1   |
  0   Vert    0   |
  0   Rouge   1   |
  1   Bleu    0   | Valeur '\xaf' 
  1   Vert    1   |
  1   Rouge   1   |
  2   Bleu    1   |
  2   Vert    1   |
  2   Rouge   0  |
  3   Bleu    0  |
  3   Vert    0  |
  3   Rouge   0  | '\0', sentinelle de fin de message
  4   Bleu    0  |
  4   Vert    0  |
  4   Rouge   0  | 
  5   Bleu    0  |
```

Vous l'aurez compris, un message pourra comporter toutes les valeurs de 1 à 255, mais pas le 0 qui est utilisé comme sentinelle, ce qui convient parfaitement pour encoder des messages texte.

## Directives

Les fichiers sources permettant de lire une image BMP en mémoire sont fournis `bmp.c` et `bmp.h` vous n'avez pas à y toucher. 

Vous devez créer les fichiers `steganography.c` et `steganography.h` qui devront contenir les fonctions suivantes : 

```c
/** 
 * Encode message into BMP using LSB of pixels as carrier.
 * @param bmp BMP image loaded in memory
 * @param message String containing the message to encode
 */
void encode(BMP *bmp, char* message);

/** 
 * Decode an encoded message from a BMP using pixel's LSB 
 * as carrier.
 * 
 * @param bmp BMP image loaded in memory with embedded message
 * @param message Buffer to save the decoded message
 * @param size Maximum size of the destination message buffer
 * @return Effective size of the message, '\0' included.
 */
int decode(BMP *bmp, char* message, size_t size);
```

Vous devez également compléter `main.c` pour que le programme fonctionne comme décrit ci-dessous en supportant les arguments `--encode` et `--decode` mais également les options courtes `-e` et `-d`. Par défaut, en l'absence de `-e` et `-d` le programme se comportera en mode *encodage* comme si `-e` était présent.

Votre programme doit afficher comme à l'accoutumée sa version et son aide avec `--version` et `--help`. 

N'oubliez pas l'en-tête de vos fichiers.

N'oubliez pas de protéger vos fichier `.h` contre la réentrance.

## Exécutable

L'exécutable prendra en argument le nom du fichier d'entrée et sur l'entrée standard le message à encoder. La ligne d'usage du programme est la suivante :

```
./steg [-e][-d] <input_filename> [<output_filename>]
```

Nous lirons entre crochets les options optionnelles courtes et entre chevrons les noms de fichiers à fournir. Le message est injecté sur `stdin`. 

Le fichier de sortie est donc optionnel et si `-e` est présent, mais que le fichier de sortie n'est pas mentionné, la sortie BMP est redirigée vers la sortie standard. Dans ce cas, si `-d` est aussi présent, le message décodé sera redirigé sur la sortie d'erreur. Il y a donc 7 cas possibles :


| Options    | Nom fichier de sortie | Image   | Message |
| ---------- | --------------------- | ------- | ------- |
| `-e`, `-d` | Oui                   | Fichier | Stdout  |
| `-e`       | Oui                   | Fichier | -       |
| `-e`       | Non                   | Stdout  | -       |
| `-e`, `-d` | Non                   | Stdout  | Stderr  |
| `-d`       | -                     | -       | Stdout  |
|            | Oui                   | Fichier | -       |
|            | Non                   | Stdout  | -       |


Les options `-e` et `--encode` sont équivalents, l'une est la forme courte plus simple à écrire, mais moins lisible.

Voici un exemple d'utilisation :

```console
$ ./steg --encode assets/blanche.bmp cipher.bmp <<< "Un message secret"
$ ./steg --decode cipher.bmp
Un message secret
```

Dans le cas ou le message à encoder est trop long pour l'image, un message d'erreur sera affiché sur `stderr` et le programme se terminera. Par exemple pour `assets/test.bmp` qui a une taille de 8x8x3, le message aura une taille maximale de 191 caractères ASCII plus la sentinelle terminale `\0`.

## Détails

Pour plus de détails, on se propose de comparer les deux images avant et après avoir encodé le message `abc` : 

```console
$ diff <(cat assets/black.bmp | hexdump -bv) <(./steg -e assets/black.bmp <<< "abc" | hexdump -bv)
4,6c4,6
< 0000030 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 001
< 0000040 001 001 000 000 000 000 000 000 000 000 000 000 000 000 000 000
< 0000050 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000 000
---
> 0000030 000 000 000 000 000 000 000 001 001 000 000 000 000 001 000 001
> 0000040 001 000 000 000 001 000 000 001 001 000 000 000 001 001 000 000
> 0000050 000 000 001 000 001 000 000 000 000 000 000 000 000 000 000 000
```

Le programme `diff` affiche les différences entre deux fichiers d'entrée passés comme arguments. L'écriture `<( )` permet d'exécuter le contenu de la parenthèse et d'injecter le résultat dans un fichier temporaire passé comme argument au programme. Dans notre exemple on passe comme premier argument le nom d'un fichier temporaire contenant `cat assets/black.bmp | hexdump -bv`, soit le contenu filtré avec `hexdump -bv` qui affiche chaque byte sous forme octale. Le second argument `./steg -e assets/black.bmp <<< "abc" | hexdump -bv` contient cette même image avec le message caché à l'intérieur : `abc`. 

En binaire `a` vaut `01100001`. On peut aisément observer `000 001 001 000 000 000 000 001` à l'adresse `0x36`. On se rappelle que l'offset du début de l'image BMP est indiquée dans l'en-tête à l'adresse `10`, laquelle est bien `0x36` : 

```console
$ cat assets/black.bmp | hexdump -s10 -n4
000000a 0036 0000
```

En utilisant ces outils, en particulier `hexdump` vous pouvez faciliter les étapes de débug de votre programme. 

Utilisez les images `assets/black.bmp` et `assets/test.bmp` comme images de test.

## Déroulement

1. Prendre connaissance de la donnée.
2. Prendre connaissance des critères d'évaluation `criteria.yml`.
3. Bien lire et comprendre les repères théoriques de ce `README.md`.
4. Essayer de comprendre comment fonctionne `bmp.c`.
5. Créer le fichier `steganography.h`, insérer les prototypes et l'en-tête.
6. Créer le fichier `steganography.c`, implémenter `encode` et `decode`.
7. Tester vos fonctions avec les images de test.
8. Tenter de décoder le message de l'image `assets/elephant.bmp`.
9. Ajouter la lecture des arguments dans votre programme principal.
10. Supporter `-e`, `--encode`, `-d` et `--decode`.
11. Respecter les 7 cas de fonctionnement du programme.
12. Tester l'affichage des éventuels messages d'erreurs sur `stderr`. 
13. Supporter `--help` et `--version`.
14. Tester votre programme.
15. Rédiger un rapport de test `REPORT.md`.

## Rapport de test

Votre rapport de test contient vos observations et le résultat de vos tests. Il contiendra une introduction, une analyse et une conclusion.

## Debug dans VsCode

Vous pourriez avoir besoin d'avancer en pas-à-pas. Visual Studio Code permet de compiler votre programme et le déboguer grâce aux deux fichiers `.vscode/build.json` et `.vscode/launch.json`. Ce dernier configure l'exécution du code. Vous pouvez manuellement configurer le nom de l'exécutable et quels sont les arguments passés au programme lors de l'exécution en mode pas à pas : 

```json
"program": "${workspaceFolder}/steg",
"args": ["--encode", "assets/blanche.bmp", "output.bmp"],
```

Dans le cas de la lecture depuis `stdin` vous devez entrer manuellement votre message dans la fenêtre de terminal et insérer un **EOF** avec `<CTRL>+<D>`.

Alternativement, vous pouvez directement passer une chaîne avec : 

```json
"args": ["--encode", "assets/blanche.bmp", "output.bmp", "<<<", "abc"],
```

## Indices

- Les deux fonctions `encode` et `decode` sont assez courtes et ne devraient pas dépasser les 10-15 lignes chacune. Vous pouvez facilement les tester en vous inspirant des exemples donnés dans ce fichier `README.md`. 
- La lecture des arguments devrait vous être familière, vous pouvez réutiliser le code de vos travaux précédents pour accélérer votre développement.
- Un `Makefile` est fourni. La commande `make` vous permet de compiler tous les fichiers `.c` disponibles en un exécutable nommé `steg`.
- Utilisez `clang-format` pour formater votre code et ne pas perdre des points à cause de l'indentation.
- N'oubliez pas de rajouter votre rapport de test à Git avec `git add REPORT.md`.
- N'oubliez pas de faire des `commits` et des `push` réguliers.

## Encryption (Bonus)

Parfois, il serait trop risqué de caché un message dans une image sans le chiffer au préalable néanmoins un programme se doit d'être KISS (Keep It Simple Stupid) et il est préférable de dépendre d'autres programmes qui sont spécialisés dans le chiffrement de le déchiffrement de messages. On se propose ici de mettre à profit votre outil de stéganographie pour chiffrer des codes secrets. 

Vous aurez besoin de plusieurs outils :

- ``base64`` pour convertir un contenu binaire en un fichier ASCII
- ``mcrypt`` un outil de cryptographie pour chiffrer/déchiffrer un message

Vous pouvez installer ces outils avec : 

```console
$ sudo apt-get install mcrypt coreutils
```

Par exemple si vous souhaitez chiffrer le message "Les chants les plus désespérés sont les chants les plus beaux", utilisé durant la bataille de Normandie pour déclencher le "Plan Violet" dont l'action fut la destruction de lignes de communication des P.T.T. vous pouvez utiliser la commande suivante :

```console
$ echo "Les chants les plus désespérés sont les chants les plus beaux" | mcrypt -a blowfish | hexdump -C
Enter the passphrase (maximum of 512 characters)
Please use a combination of upper and lower case letters and numbers.
Enter passphrase:
Enter passphrase:

Stdin was encrypted.
00000000  00 6d 03 40 62 6c 6f 77  66 69 73 68 00 38 00 63  |.m.@blowfish.8.c|
00000010  62 63 00 6d 63 72 79 70  74 2d 73 68 61 31 00 15  |bc.mcrypt-sha1..|
00000020  aa 8e f7 61 e6 0b 2e b0  5b 56 db 8a c2 bb fd 0e  |...a....[V......|
00000030  9c c7 7c e7 73 68 61 31  00 db 00 9b 58 dc ea 28  |..|.sha1....X..(|
00000040  16 1b 1a 22 88 f8 49 2e  cb 7c 76 03 e5 d1 b1 17  |..."..I..|v.....|
00000050  c1 aa 26 aa 42 4d c7 f9  21 3e 18 a0 4e d4 76 1d  |..&.BM..!>..N.v.|
00000060  ec aa 6d eb ed 21 6b 6b  d5 d2 ba 93 16 df 40 15  |..m..!kk......@.|
00000070  f7 d9 cd e8 d5 5f dc 95  a6 0c 83 5d 57 16 48 e2  |....._.....]W.H.|
00000080  6e 39 6b dc 6b f4 7c ff  b7 03 f8 11 e0 2c 59 7f  |n9k.k.|......,Y.|
00000090  66 b5 de a5 54 70 7c 5f  91                       |f...Tp|_.|
00000099
```

Ici la clé de chiffrement (*passphrase*) est `bonjour`, et l'algorithme de chiffrement est `blowfish`, un algorithme de chiffrement assez connu. On observe dans le résultat de `hexdump` que le message chiffré est binaire, car la plupart des caractères ne sont pas imprimables. Or, dans votre programme de stéganographie, vous utilisez une sentinelle `\0` qui est malheureusement utilisée dans ce code par exemple à l'adresse 0x38. Pour contourner ce type limitation, une approche simple est d'utiliser l'encodage [Base64](https://fr.wikipedia.org/wiki/Base64) qui permet de convertir un contenu binaire en n'utilisant que 64 caractères imprimables ASCII. 

```console
$ base64 <<< "\x12\x00\x12abc"
XHgxMlx4MDBceDEyYWJjCg==
```

Ainsi votre message codé peut être compatible avec votre outil de stéganographie :

```console
$ echo "Les chants les plus désespérés sont les chants les plus beaux" |  MCRYPT_KEY=bonjour mcrypt -a blowfish -q | base64 | tee cipher.txt
AG0DQGJsb3dmaXNoADgAY2JjAG1jcnlwdC1zaGExABVS8wiD09hnQDuI9FpEI340vTrzk3NoYTEA
XXhCa5I8ae0K6N5oLF/7MkPt+83Aa2/ztUuUcXlnKeddhZd9zg6c1Fs3saWMkKW+orGN+SKVYOCa
8HaX4i1KUTDQa7DX2gb/KUtIEZFr62OxCusD6Wi0ZdrRKvboe0el
```

Notons ici que le programme `tee` ne fait que dupliquer le contenu reçu sur `stdin` sur `stdout` et dans le fichier passé en paramètre `cipher.txt`. Ce dernier contient donc le message chiffré encodé en Base64. 

Et bien entendu ce message peut être déchiffré :

```console
$ cat cipher.txt | base64 --decode | MCRYPT_KEY=bonjour mcrypt -d -q
Les chants les plus désespérés sont les chants les plus beaux
```

Maintenant que l'on sait chiffrer et déchiffrer un message, il est possible de cacher un message codé dans une image :

```console
$ echo "Le petit chat est mort" | mcrypt -a enigma | base64 | ./steg assets/blanche.bmp --encode > blanche.bmp
Enter the passphrase (maximum of 512 characters)
Please use a combination of upper and lower case letters and numbers.
Enter passphrase:
Enter passphrase:

Stdin was encrypted.
```

Vous pouvez maintenant transmettre l'image `blanche.bmp` sans risque que le message soit décodé facilement, car si quelqu'un essaie juste votre programme, il obtiendra un message abscons :

```console
$ ./steg --decode blanche.bmp
AG0DQGVuaWdtYQANAHN0cmVhbQBtY3J5cHQtc2hhMQAVSW8HmxSkwdDKB99rSSMZndXFkmpzaGEx
AFyLNccU195mbUo6SJgDvOXBI4zh5ugk2qdoLAf4hlkELkPFfoC1ce9Yi9E=
```

Il faudra donc le passer dans `base64 -d` puis dans `mcrypt -d`. 

Arrivez-vous maintenant à décoder le message de l'image ?

Pour obtenir ce bonus, vous devrez donner un exemple dans votre rapport de test.
