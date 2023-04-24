# LZW Image Compression

Implémentation de l'algorithme [LZW](https://fr.wikipedia.org/wiki/Lempel-Ziv-Welch)   pour compresser des images au format ppm (sur 1, 2 et 3 octets).

# Comment l'utiliser?
## Compression

 *  Compiler le code en utilisant la commande "make".
*   Choisir une image ppm.
*   Lancer l'exécutable "palette" suivi du nom de votre image. Par exemple : "./palette image.ppm".
 *  Faire un clic droit sur l'image pour obtenir les options de modifications que vous pouvez appliquer à l'image.
 *  Choisir "LZW" et le nombre d'octets par couleur pour la compression. Il est recommandé de choisir le minimum nécessaire pour obtenir une compression optimale.
 *  Ensuite, vous pourrez choisir un nom pour votre image compressée dans le terminal.
 *  L'image compressée sera créée dans le dossier courant.

## Décompression

*   Compiler le code en utilisant la commande "make".
*   Lancer l'exécutable "palette" suivi du nom de votre image compressée. Par exemple : "./palette image.comp".
*   Faire un clic droit sur l'image pour obtenir les options de modifications que vous pouvez appliquer à l'image.
*   Choisir "Décompression LZW" pour le nombre d'octets que vous avez choisi lors de la compression.
 *  Ensuite, vous pourrez choisir un nom pour votre image décompressée dans le terminal.
 *  L'image décompressée sera créée dans le dossier courant.
