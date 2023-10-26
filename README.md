# 42-cub3D

edit :  ~~barrés~~ les rules qui sont déjà en place et fonctionnelle  

## Parsing rules
• ~~Votre programme doit prendre en premier argument un fichier de description de
scène avec pour extension .cub~~
• La map doit être composée d’uniquement ces 6 caractères : 0 pour les espaces vides, 1 pour les murs, et N,S,E ou W qui représentent la position de départ du joueur et son orientation.
• ~~Cette simple map doit être valide :~~
```
111111
100101
101001
1100N1
111111
```
• La map doit être fermée/entourée de murs, sinon le programme doit renvoyer une erreur.
• Mis à part la description de la map, chaque type d’élément peut être séparée par une ou plusieurs lignes vides.
• ~~La description de la carte sera toujours en dernier dans le fichier, le reste des éléments peut être dans n’importe quel ordre.~~
• ~~Sauf pour la map elle-même, les informations de chaque élément peuvent être séparées par un ou plusieurs espace(s).~~
• ~~La carte doit être parsée en accord avec ce qui est présenté dans le fichier. Les espaces sont une partie valable de la carte, c’est à vous de les gérer correctement. Vous devez pouvoir parser n’importe quelle sorte de carte, tant qu’elle respecte les règles de carte.~~
• ~~Pour chaque élement, le premier caractère est l’identifiant (un ou deux caractères), suivi de toutes les informations spécifiques à l’élément dans un ordre strict tel que :~~
```
— texture nord :
NO ./path_to_the_north_texture
— identifiant : NO
— chemin vers la texture nord
```
```
— South texture :
SO ./path_to_the_south_texture
— identifiant : SO
— chemin vers la texture sud
```
```
— West texture :
WE ./path_to_the_west_texture
— identifiant : WE
— chemin vers la texture ouest
``` 
```
— East texture :
EA ./path_to_the_east_texture
— identifiant : EA
— chemin vers la texture est
```
```
— Couleur du sol :
F 220,100,0
— identifiant : F
— couleurs R,G,B range [0,255] : 0, 255, 255
```
```
— Couleur du plafond :
C 225,30,0
— identifiant : C
— couleurs R,G,B range [0,255] : 0, 255, 255
```
◦~~Exemple minimaliste de scène de la partie obligatoire .cub :~~
``` 
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
``` 
• ~~Si un problème de configuration de n’importe quel type est rencontré dans le fichier, le programme doit quitter et renvoyer "Error\n" suivi d’un message d’erreur explicite de votre choix.~~

## Exec rules
• Vous devez utiliser la minilibX. 
• La gestion des fenêtres doit être parfaite : gestion de la minimalisation, du passage
d’une autre fenetre, etc.
• Vous devez afficher des textures différentes (vous avez le choix) selon si les murs
sont face nord, sud, est, ouest.
• Votre programme doit être capable d’avoir des couleurs différentes pour le sol et
le plafond.
• Le programme affiche l’image dans une fenêtre et respecte les règles suivantes :
	◦Les touches flèches du gauche et droite du clavier doivent permettre de faire
	une rotation de la caméra (regarder a gauche et a droite)
	◦Les touches W, A, S et D doivent permettre de déplacer la caméra (déplacement
	du personnage)
	◦Appuyer sur la touche ESC doit fermer la fenêtre et quitter le programme
	proprement
	◦Cliquer sur la croix rouge de la fenêtre doit fermer la fenêtre et quitter le
	programme proprement
	◦L’utilisation d’images de la minilibX est fortement recommandée.