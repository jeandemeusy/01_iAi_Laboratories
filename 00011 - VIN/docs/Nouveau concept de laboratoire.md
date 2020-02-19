# Nouveaux concepts

## Table des matières
- [Liste des laboratoires](#liste-des-laboratoires)
  * [Interaction avec le controleur et prise de vue](#interaction-avec-le-controleur-et-prise-de-vue)
  * [Calibration et mesures](#calibration-et-mesures)
  * [Canaux RGB](#canaux-rgb)
  * [Détection de forets](#détection-de-forets)
  * [Détection des forets - UI](#détection-des-forets---ui)
  * [Contrôle de marques sur PCB](#contrôle-de-marques-sur-pcb)
  * [Contrôle des défauts sur PCB](#contrôle-des-défauts-sur-pcb)
  * [Labo-Test - Contrôle de marques rouges et bleues](#labo-test---contrôle-de-marques-rouges-et-bleues)
- [Template](#template)
- [Todo](#todo)

## Liste des laboratoires
### Interaction avec le controleur et prise de vue
Faire un tour du matériel ainsi que des différents programmes qui seront utilisés durant les laboratoires au travers d'un laboratoire guidé. Pour cela, un programme template sera fourni aux étudiants afin qu'ils puissent tester l'upload/download de programme dans KEYENCE, comment interagir avec le contrôleur et faire les réglages de l'unité de capture.
- Introduit :
    - le contrôleur KEYENCE et le setup optique
    - le programme KEYENCE VisionTerminal
        - son utilité
        - les différentes fenêtres du programmes
        - comment se connecter à un contrôleur
        - comment enregistrer/charger des configurations
    - le programme KEYENCE VisionEditor
        - son utilité
        - les différents onglets
            - File : présenter les diverses fenêtres
            - Program Setting : présenter les diverses fenêtres
            - Operation Screen Setting & User Layout : expliquer brièvement leur utilité, mais ne pas s'étendre.
- Déroulement : 
    - Discussion : 
        - introduction du laboratoire et description de l'environnement
    - Guidé : 
        - installation (finalisation de l'installation des différents programmes)
        - découverte des différents programmes et de leur utilité
        - connexion du contrôleur aux programmes et upload du programme template
     - Discussion : 
         - présentation de différents objets à capturer et de quels points mettre en valeur.
     - Guidé :
        - Un premier réglage pour un objet pour montrer les différents points de paramètres du contrôleur et du système optique pour faire une bonne prise de vue.
     - Libre : 
        - Réglage du système par les étudiants pour observer les différents objets mis à leur disposition.
- Durée : 2h
- Pré-requis :
    - Fonctionnement de la prise d'image (temps d'ouverture/diaphragme/focale/sensibilité/etc)
- Matériel :
    - programme KEYENCE template qui contient 2-3 fonctions et une UI basiques, mais un bloc capture vierge.

***
            
### Calibration et mesures
Calibrer le système pour corriger la déformation induite par l'optique du système et faire des mesures visuelles à l'échelle et exemptes de déformation
- Introduit :
    - Travail en Simulation uniquement (et pas sur le contrôleur)
    - Image de référence/capture
    - Utilisation des outils longueurs/aire
        - Notion de Scaling
        - Paramétrage des blocs fontionnels génériques
        - Utilisation des ROI dans les blocs fonctionnels
        - Observation des résultats dans les blocs fonctionnels
- Déroulement :
    - Discussion : Introduction du laboratoire
    - Guidé : 
        - processus de calibration du système
        - mesure d'un des objets avec une image dont la déformation est corrigée
    - Libre : mesure de tous les objets sur toutes les images
- Durée : 2h
- Pré-requis :
    - (-)
- Matériel :
    - les images déformées
        
***

### Canaux RGB
Extraire les composantes RGB d'une image. Grâce aux opérations sur les images, extraire les composantes jaune isolée et noire isolée.
Utiliser l'outil built-in d'extraction des couleurs pour effectuer la même chose : facile et rapide !
Une fois les différents cas terminés, implémenter les blocs d'extraction de couleur ainsi que la structure de contrôle dans le programme fourni pour finir par le faire tourner en temps réel sur le contrôleur.
- Introduit :
    - Opérations sur les images et manipulation des variables images
    - Programmation via FlowChart
        - ajout/suppression de blocs
        - variables
        - utilisation des structures de contrôle (branch)
- Déroulement : Séance 1 : 
    - Discussion : 
        - Introduction du labo
        - présentation du CdC
        - discussion sur les cannaux RGB
    - Guidé : 
        - théorie sur les canaux RGB
        - introduction aux opérations sur les images
    - Discussion :
        - réflexion en groupe sur comment faire pour extraire le Rouge uniquement (par exemple)
    - Libre :
        - mise en place de la méthode décrite précédemment et implémentation de tous les cas

- Déroulement : Séance 2 : 
    - Discussion :
        - retour sur ce que les étudiants on fait la dernière fois = contrôle que les étudiants ont tous quelque chose qui fonctionne.
        - explication de l'objectif de la suite du labo
        - présentation des outils de contrôle du flowchart (branch/loop) et de comment les contrôler
    - Libre :
        - implémentation de la partie contrôle de l'application et test de validation avec le setup complet
- Durée : 4h (2x 2h)
- Pré-requis :
    - Théorie RGB
- Matériel :
    - programme KEYENCE : squelette contenant l'UI et les variables de bases à utiliser

***

### Détection de forets
Détecter sur l'image la présence et le type des forets dentaires. L'image affichera 3 types de forets :
- Type 1 : avec un manche en plastique de différentes couleurs et l'épaisseur écrite contre la partie plastique.
- Type 2 : avec un manche en métal et un anneau en plastique coloré (de différentes couleurs).
- Type 3 : avec 2 types de foret : fin ou épais.

Le but est de développer un programme qui détecte le type de foret, et les informations qui permettent de discriminer OK/NOK, telles que la couleurs des divers éléments, la présence de pastille en silicone, l'épaisseur et la longueur des forets.
- Introduit :
    - Outils KEYENCE de détection d'objets sur l'image blob et shapetrax/pattern Match
    - Outil de position adjustment et ses variantes pour les ROI
    - Enregistrement des images de simulation depuis le contrôleur
    - Affichage simple des résultats à l'écran
- Déroulement : Séance 1 :
    - Discussion :
        - Introduction du laboratoire
        - contraintes posées par le CdC
    - Libre : 
        - Réglage des setups des étudiants pour une capture optimale
    - Discussion : 
        - retour sur les tactiques de prises de vues et présentation d'une solution
    - Libre :
        - Prise des images de simulation
    - Guidé : 
        - Démonstration de blob pour détecter des objets
        - Démonstration de ShapeTrax pour détecter le type de foret + image de référence
    - Libre : 
        - Mise en pratique des blocs Blob/ShapeTrax pour détecter les 3 types de forets
    - Discussion : 
        - retour sur les stratégies (être sûr que ça marche chez tout le monde)
        - réflexion sur comment aborder le problème pour optimiser la détection de 3 types de forets sur une image qui contient plusieurs forets de type différents (utilisation de blob + boucles + branch).
    - Libre :
        - réorganisation du code et test pour que ça marche.

- Déroulement : Séance 2 :
    - Guidé : 
        - Démonstration de l'importance de Position Adjust : création d'un outil de mesure d'épaisseur de foret (par exemple) sur un type de foret (Type 3), mais sur les prises d'images différentes (pas sur l'image de référence), la ROI ne suit pas.
        - Démonstration de Position Adjustment pour faire suivre les ROIs .
        - Démonstration de comment utiliser des variables pour paramétrer les blocs.
        - Affichage de résultats simples à l'écran (forets qui a la bonne couleur).
    - Libre : 
        - Création de tous les blocs de contrôle pour remplir le CdC
        - Création des variables de contrôles nécessaires pour les blocs.
- Durée : 4h (en classe) + 4h à la maison
- Pré-requis :
    - Prise de vue
    - Manipulation des variables
    - Programmation en FlowChart
- Matériel :
    - Les forets Dentsply Maillefer

***

### Détection des forets - UI
Reprendre le programme utilisé pour le labo sur les forets dentaire et créer une UI fonctionnelle dessus pour le contrôle des éléments à contrôler, ainsi qu'un affichage temps réel des forets valides et non-valides.

:warning: les étudiants doivent faire une copie de leur labo "Foret" (pour conserver une copie de l'original)
- Introduit :
    - Les éléments pour créer une UI
    - Utilisation des commandes système
- Déroulement :
    - Discussion : 
        - Démonstration du résultat attendu et discussion du CdC
        - Explication du fonctionnement d'une UI classique et des contraintes que cela pose
    - Guidé :
        - Présentation de la fenêtre de customisation d'UI
        - Création de menu ainsi que leur paramétrage et le paramétrage des éléments
            - Les boutons
            - Les drop-down list
        - Utilisation des commandes
    - Autonome : 
        - Remise en forme du code FlowChart et de l'UI + test
- Durée : 2h labo + 2h maison
- Pré-requis :
    - Pattern match
    - Sélection de couleur
    - mesure des longueurs
- Matériel :
    - Forets Maillefer-Dentsply
       
***
      
### Contrôle de marques sur PCB
Lire et contrôler l'exactitude de tous les champs de l'étiquette de la carte à PCB.
- Introduit :
    - Utilisation des blocs OCR et ajouts de nouveaux caractères
    - Utilisation des blocs CodeBarre 1D/2D
    - Manipulation des données "strings" sur contrôleur KEYENCE
- Déroulement :
    - Discussion:
        - Introduction
        - Réflexion sur le CdC et ses contraintes
    - Guidé :
        - Présentation des blocs CodeBarre 1D/2D Attention aux conditions minimales pour un "auto-tuning" fonctionnel.
        - Présentation des blocs OCR et de comment est stockée l'information ensuite
    - Libre :
        - Implémentation du squelette du programme (position adjustment, etc...)
        - Implémentation des différents blocs de contrôle
        - Implémentation du display
        - Test de validation avec le setup complet et les différents PCB
- Durée : 2h
- Pré-requis :
    - Pattern match + position adjustment
    - On-Screen display
- Matériel :

***

### Contrôle des défauts sur PCB
Détection des défauts présents sur une carte à PCB : éléments manquants/fissures/déformation.
- Introduit :
    - Utilisation des différents blocs/image enhance pour la détection de défauts
    - Détection de défaut via soustraction des images
    - Utilisation d'un masque sur une image pour définir des ROI
    - Création d'UI pour le Run Mode pour modifier le type de défaut recherché
- Déroulement :
    - Discussion :
        - Intro
        - Réflexion sur le CdC
        - Réflexion sur la manière de trouver des défauts sur un objet
    - Guidé :
        - Présentation des outils d'image enhance pour la soustraction et pour la mise en évidence des défauts
    - Libre :
        - Implémentation des outils de contrôle
        - Implémentation de l'UI
- Durée : 2h
- Pré-requis :
    - (-)
- Matériel :
    - Images de plus grandes résolutions générées avec Photoshop
        
***

### Labo-Test - Contrôle de marques rouges et bleues
Détection de la présence de marques rouges aux quatres coins des plaques à PCB.
- Pré-requis :
    - Introduction
    - Détection d'objets : blobs/pattern match/ShapeTrax.
    - Position Adjustment et comment le paramétrer
    - Notion des valeurs de jugement (GO/NOK) du contrôleur et comment les activer dans les blocs fonctionnels.
    - Isolation/Extraction des couleurs (introduit dans le labo "Canaux RGB")
- Matériel :
    - Carte à PCB avec des marques rouges.
- Durée : 4h
- Points à tester :
    - Les zones d'intérêts mobiles : prouve que le position adjust fonctionnel
    - Montre une erreur si on met une image complètement rouge comme entrée : si cela ne fait pas d'erreur, c'est que le shapetrax a échoué, mais que la suite n'a pas été effectuée (absence de branch pour gérer le programme)

***

## Template
- Laboratoire :
- Résumé
- Introduit :
- Déroulement :
- Durée :
- Pré-requis :
- Matériel :
    
***

## Todo
- Trouver où intégrer les notions
    - Image enhance
    - Investiguer 
        - Les RECIPE
        - La compilation C
- Marche à suivre des différents points
