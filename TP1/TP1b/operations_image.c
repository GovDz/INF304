#include "operations_image.h"

/* Calcule l'image "inverse" (négative) de l'image im1, et place le
   résultat dans l'image im2 */

void inverse_video(Image *im1, Image *im2) {
  Pixel p, p_inverse;
  int l = largeur(im1);
  int h = hauteur(im1);
  int max = maxval(im1);
  /* Indices de parcours de boucles */
  int i, j;

  /* Initialisation de l'image résultat, de mêmes largeur, hauteur
     et valeur max que l'image donnée en paramètre */
  init_image(l, h, max, im2);

  /* Parcours de chaque pixel de chaque ligne */
  for (i = 0; i < l; i++) {
    for (j = 0; j < h; j++) {
      p = lepixel(im1, i, j);

      /* Calcul de son "inverse video" */
      p_inverse = max - p;

      /* Affectation du résultat dans la nouvelle image im2 */
      affecter_pixel(im2, i, j, p_inverse);
    }
  }
}

void rotation(Image *im1, Image *im2) {
  int l = largeur(im1);
  int h = hauteur(im1);
  int max = maxval(im1);
  /* Indices de parcours de boucles */
  int i, j;

  /* Initialisation de l'image résultat, de mêmes largeur, hauteur,
     et valeur max que l'image donnée en paramètre */
  init_image(l, h, max, im2);

  /* Parcours de chaque pixel de chaque ligne*/
  for (i = 0; i < l; i++) {
    for (j = 0; j < h; j++) {
      affecter_pixel(im2, i, j, lepixel(im1, i, h - 1 - j));
    }
  }
}

void rotation_gauche(Image *im1, Image *im2) {
  int l = largeur(im1);
  int h = hauteur(im1);
  int max = maxval(im1);
  /* Indices de parcours de boucles */
  int i, j;

  /* Initialisation de l'image résultat, de mêmes largeur, hauteur,
     et valeur max que l'image donnée en paramètre */
  init_image(l, h, max, im2);

  for (i = 0; i < l; i++) {
    for (j = 0; j < h; j++) {
      affecter_pixel(im2, i, j, lepixel(im1, l - 1 - i, j));
    }
  }
}



void zoom_x2(Image *im1, Image *im2) {
  int l1 = largeur(im1); 
  int h1 = hauteur(im1); 
  int max = maxval(im1); 

  int l2 = 2 * l1; 
  int h2 = 2 * h1; 

  init_image(l2, h2, max, im2);

  for (int i = 0; i < l1; i++) {
    for (int j = 0; j < h1; j++) {
      Pixel p = lepixel(im1, i, j);
      affecter_pixel(im2, 2 * i, 2 * j, p);
      affecter_pixel(im2, 2 * i + 1, 2 * j, p);
      affecter_pixel(im2, 2 * i, 2 * j + 1, p);
      affecter_pixel(im2, 2 * i + 1, 2 * j + 1, p);
    }
  }
}
