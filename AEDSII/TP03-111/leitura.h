#define MAXURL 100
#define ARQUIVO 30
#define TRUE 1
#define FALSE 0
#define VAZIO -1
#define MINPARTICAO 20

typedef struct entidade{
  char *url;
  int pageviews;
}TipoEntidade;

int AbreLeitura(char *arquivo , FILE **fp);
void FechaLeitura(FILE **fp);
void leentidades(FILE *fp , int entidades , TipoEntidade *e);
void AlocaUrls(int entidades , TipoEntidade *e);
void FreeEntidades(int entidades , TipoEntidade *e);

