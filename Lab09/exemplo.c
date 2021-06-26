#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define PRETA 0
#define BRANCA 0xFFFFFF

typedef struct {
    int w, h;
    int **pix;
} Img;

// função presume que não ocorrem erros e que 
// máximo valor de valor de um canal de cor é 255
Img *ler_img() {
    Img *img;
    char peek;
    int i, j, r, g, b;
    assert(img = malloc(sizeof(*img)));
    scanf("P3 ");
 	while((peek = getchar()) == '#') scanf("%*[^\r\n]%*[\r\n]");
	ungetc(peek,stdin);
	assert(scanf("%d %d %*d", &img->w, &img->h)==2);
    assert(img->pix = malloc(sizeof(*img->pix) * img->h));
    for (i = 0; i < img->h; i++) {
        assert(img->pix[i] = malloc(sizeof(**img->pix) * img->w));
        for (j = 0; j < img->w; j++) {
            assert(scanf("%d%d%d", &r, &g, &b)==3);
            img->pix[i][j] = (r << 16) + (g << 8) + b;//r*2^16 + g*2^8 + b
        }
    }
    return img;
}
void salvar_img(Img * img, char *file) {
    int i, j;
	FILE *fp = fopen(file, "w");
	fprintf(fp, "P3\n%d %d %d\n", img->w, img->h, 255);
    for (i = 0; i < img->h; i++) {
        for (j = 0; j < img->w; j++) {
        	int r, g, b;
        	int pix = img->pix[i][j];
        	r = pix >> 16 & 0xFF;// pix/2^16 and 11111111
        	g = pix >> 8  & 0xFF;// pix/2^8 and 11111111
        	b = pix       & 0xFF;
        	fprintf(fp, "%d %d %d\n",  r, g, b);
    	}
	}
	fclose(fp);
}
void libera_img(Img *img) {
    int i;
    for (i = 0; i < img->h; i++)
        free(img->pix[i]);
    free(img->pix);
    free(img);
}

// exemplo de como usar as funções:
// lê uma imagem e cria um novo
// arquivo com metade da imagem pintada
int main(int argc, char *argv[]) {
    int i, j;
    
    Img *img = ler_img();
    /*for (i = 0; i < img->h; i++)
    	for (j = 0; j < img->w/2; j++)
    		img->pix[i][j] = BRANCA;*/
    salvar_img(img, "pintada.ppm");
    libera_img(img);
    return 0;
}


