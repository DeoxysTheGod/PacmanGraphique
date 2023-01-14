# Porjet Pacman Sae

## Création de carte

Il faut une image au format `.ppm` P3

Sur linux :

Vous pouvez faire une image `.png` et la convertir en utilisant :

`convert <nom_image>.png -compress none <nom_image>.ppm`

Il faut utiliser les couleurs suivantes :

* Noir (0, 0, 0) : mur
* Blanc (255, 255, 255) : beignet
* Jaune (255, 255, 0) : Pacgum
* Magenta (255, 0, 255) : case vide
* Rouge (255, 0, 0) : fantôme
* Vert (0, 255, 0) : Pacman
* Cyan (0, 255, 255) : teleporteur **! Il doit forcement y en avoir un symétrique !**
