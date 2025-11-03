# Backlight Boat Panel

## Description du projet

Ce projet est un projet destiné à expliquer le processus de création d'un panneau de commande électrique rétroéclairé pour un bateau. Le panneau permet de gérer l'alimentation (**on/off seulement**) de certains instruments du bateau.
Le panneau contient aussi des fusibles pour tous les équipements qu'il permet d'actionner.

En plus des interrupteurs, le panneau permet de **gérer la luminosité** du rétroéclairage et affiche périodiquement (toutes les 3 minutes) l'état de la batterie : **Puissance, Intensité, Tension**.
L'affichage des valeurs est effectué sur un afficheur **e-Paper** (ou **e-Ink**), choisi par soucis d'esthétique et de faible consommation.

## Composants (avec liens)

Voici la liste de tous les composants utilisé pour la réalisation de ce panneau :
- 1x [Plaque Plexiglass (PMMA) extrudé **transparant** 2mm](https://plexiglasssurmesure.fr/produit/plaque-plexiglass-transparent-extrude-2mm/)
- 1x [Plaque Plexiglass (PMMA) extrudé **opaque** 2mm](https://plexiglasssurmesure.fr/plaquess-en-plexiglass/opaque/)

Je recommande d'acheter 2 plaques Plexiglass au cas où vous devez refaire les découpes/gravures laser.

## Les différentes parties du projet

Ce projet est décomposables en plusieurs parties, les voici :

- Panneau rétroéclairé, la réalisation du panneau rétroéclairé est disponible dans le sous-dossier **[backlight-panel/ReadME.md](./backlight-panel/ReadME.md)**

- Le code arduino et l'éléctronique associé pour le calcul de la puissance, l'affichage sur un afficheur e-Ink/e-Paper et la gestion de la luminosité du panneau

- Le schéma éléctrique
