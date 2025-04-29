#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int r, g, b;
} RGB;
int main () 
{
    FILE *fp;
    
    char imagem[50];
    printf("Digite o nome da imagen colorida, com .ppm: ");
    scanf("%s", imagem);
    fp = fopen(imagem,"r");
    if(fp==NULL){
        printf("Erro ao abrir o arquivo!");
        return 1;
        }

    char tipoImg[3];

    int i, j, linha, coluna, val, opcao;
    
    fscanf(fp, "%s", tipoImg);
    printf("%s\n", tipoImg);
    
    fscanf(fp, "%d %d", &coluna, &linha); 
    printf("%d %d\n", coluna, linha);

      if (coluna < 400 ||  linha < 400) {
        printf("Imagem menor que 400x400!\n");
        fclose(fp);
        return 1;
    }
    
    fscanf(fp, "%d", &val);  
    printf("%d\n", val);

      RGB **matriz = malloc(linha * sizeof(RGB*));
      for(j = 0; j<linha; j++) {
        matriz[j] = malloc (coluna * sizeof(RGB));
      }

    for(j=0; j<linha; j++)
    {
        for(i=0; i<coluna; i++)
        {   
            fscanf(fp, "%d %d %d", &matriz[j][i].r, &matriz[j][i].g, &matriz[j][i].b);
        }
    }
    fclose(fp);

      printf ("1- Transformar colorida em uma imagem tons de cinza ");

      printf ("2- Transformar colorida em uma imagem negativa ");

      printf ("3- Transformar colorida em uma imagem raio-x ");

      printf ("4- Transformar colorida em uma imagem envelhecida (sépia) ");

      printf ("5- Rotacionar colorida em 90 graus ");

      printf ("6- Rotacionar colorida em 180 graus ");

      printf ("Qual voce deseja fazer? ");

      scanf ("%d", &opcao);

      FILE *fp_novo = fopen("saida.ppm", "w");
      if (fp_novo == NULL) {
          printf("Erro ao criar o arquivo de saída!\n");
          return 1;
      }  

      if (opcao == 1) 
      { 
            fprintf (fp_novo, "P2\n");
            fprintf (fp_novo, "%d %d\n", coluna, linha);
            fprintf (fp_novo, "%d\n", val);
    
            for(j=0; j<linha; j++)
            {
                for(i=0; i<coluna; i++)
                {   
                int cinza = (matriz[j][i].r * 0.299) + (matriz[j][i].g * 0.587) + (matriz[j][i].b * 0.114);
                if (cinza > 255) cinza = 255;
                if (cinza < 0) cinza = 0;
            fprintf(fp_novo, "%d\n", cinza);
                }
            }
      } else if (opcao == 2)
      {
            fprintf (fp_novo, "P3\n");
            fprintf (fp_novo, "%d %d\n", coluna, linha);
            fprintf (fp_novo, "%d\n", val);
    
            for(j=0; j<linha; j++)
            {
                for(i=0; i<coluna; i++)
                {   
                    int R_novo = 255 - matriz[j][i].r;
                    int G_novo = 255 - matriz[j][i].g;
                    int B_novo = 255 - matriz[j][i].b;
                    fprintf(fp_novo, "%d %d %d\n", R_novo, G_novo, B_novo);
                }
            }
      } else if (opcao == 3) {
        
            fprintf (fp_novo, "P2\n");
            fprintf (fp_novo, "%d %d\n", coluna, linha);
            fprintf (fp_novo, "%d\n", val);
            int fator = 1;
    
            for(j=0; j<linha; j++)
            {
                for(i=0; i<coluna; i++)
                {   
                 int cinza = (matriz[j][i].r * 0.299) + (matriz[j][i].g * 0.587) + (matriz[j][i].b * 0.114);
                 matriz[j][i].r = cinza ^ fator;
                 matriz[j][i].g = cinza ^ fator;
                 matriz[j][i].b = cinza ^ fator;
            fprintf(fp_novo, "%d %d %d\n", matriz[j][i].r, matriz[j][i].g, matriz[j][i].b);
                }
            }
      } else if (opcao == 4)
      {
            fprintf (fp_novo, "P3\n");
            fprintf (fp_novo, "%d %d\n", coluna, linha);
            fprintf (fp_novo, "%d\n", val);

            double fator2 = 0.1;
    
            for(j=0; j<linha; j++)
            {
                for(i=0; i<coluna; i++)
                {   
                    matriz[j][i].r = matriz[j][i].r * (1 + fator2);
                    matriz[j][i].g = matriz[j][i].g * (1 + fator2);
                    matriz[j][i].b = matriz[j][i].b * (1 - fator2);

             if (matriz[j][i].r > 255) matriz[j][i].r = 255;
                if (matriz[j][i].g  > 255) matriz[j][i].g  = 255;
                if (matriz[j][i].b > 255) matriz[j][i].b  = 255;
                if (matriz[j][i].r  < 0) matriz[j][i].r  = 0;
                if (matriz[j][i].g < 0) matriz[j][i].g = 0;
                if (matriz[j][i].b  < 0) matriz[j][i].b = 0;
                    fprintf(fp_novo, "%d %d %d\n", matriz[j][i].r , matriz[j][i].g , matriz[j][i].r );
                }
            }
      } else if (opcao == 5) 
      {
            fprintf (fp_novo, "P3\n");
            fprintf (fp_novo, "%d %d\n", linha, coluna);
            fprintf (fp_novo, "%d\n", val);
    
            for(i=0; i<coluna; i++)
            {
                for(j= linha - 1; j>= 0; j--)
                {   
                    fprintf(fp_novo, "%d %d %d\n", matriz[j][i].r, matriz[j][i].g, matriz[j][i].b);
                }
            }
      } else if (opcao == 6) 
      {
        fprintf(fp_novo, "P3\n"); 
        fprintf(fp_novo, "%d %d\n", coluna , linha);
        fprintf(fp_novo, "%d\n", val);
        
        for (int j = linha - 1; j >= 0; j--) {
            for (int i = coluna - 1; i >= 0; i--) {
                fprintf(fp_novo, "%d %d %d\n", matriz[j][i].r, matriz[j][i].g, matriz[j][i].b);
            }
        }
    }
    else {
        printf("Opção inválida!\n");
        fclose(fp_novo);
        return 1;
    }
    
    fclose(fp_novo);
    for(j = 0; j< linha; j++) {
        free(matriz[j]);
    }
    free (matriz);
    printf("Imagem processada e salva em 'saida.ppm'!\n");
    
    return 0;
      }

