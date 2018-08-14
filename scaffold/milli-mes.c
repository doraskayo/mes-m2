#if __M2_PLANET__
CONSTANT TCHAR          0
CONSTANT TCLOSURE       1
CONSTANT TCONTINUATION  2
CONSTANT TFUNCTION      3
CONSTANT TKEYWORD       4
CONSTANT TMACRO         5
CONSTANT TNUMBER        6
CONSTANT TPAIR          7
CONSTANT TPORT          8
CONSTANT TREF           9
CONSTANT TSPECIAL      10
CONSTANT TSTRING       11
CONSTANT TSYMBOL       12
CONSTANT TVALUES       13
CONSTANT TVARIABLE     14
CONSTANT TVECTOR       15
CONSTANT TBROKEN_HEART 16
#else // !__M2_PLANET__
enum type_t {TCHAR, TCLOSURE, TCONTINUATION, TFUNCTION, TKEYWORD, TMACRO, TNUMBER, TPAIR, TPORT, TREF, TSPECIAL, TSTRING, TSYMBOL, TVALUES, TVARIABLE, TVECTOR, TBROKEN_HEART};
#endif // !__M2_PLANET__

typedef long SCM;

struct scm {
  enum type_t type;
  SCM car;
  SCM cdr;
};

struct scm *g_cells;

int oputs (char const *);
char const *itoa (int);
void *malloc (int);

#if __M2_PLANET__
#define struct_size 12
#define TYPE(x) ((x*struct_size)+g_cells)->type
#define CAR(x) ((x*struct_size)+g_cells)->car
#define CDR(x) ((x*struct_size)+g_cells)->cdr
#define VALUE(x) ((x*struct_size)+g_cells)->cdr
#else // !__M2_PLANET__
#define TYPE(x) (g_cells+x)->type
#define CAR(x) (g_cells+x)->car
#define CDR(x) (g_cells+x)->cdr
#define VALUE(x) (g_cells+x)->cdr
#endif // !__M2_PLANET__

int
main (int argc, char **argv)
{
  char *arena = malloc (3*sizeof (struct scm));
  g_cells = arena;

  TYPE (0) = TPAIR;
  CAR (0) = 11;
  CDR (0) = 12;

  int i = 1;
  TYPE (i) = 0;
  CAR (i) = 0;
  CDR (i) = 0;

  oputs ("type 0:");
  oputs (itoa (TYPE (0)));
  oputs ("\n");

  oputs ("setting type 2\n");
  if (argc > 1)
    TYPE (2) = TPAIR;

  oputs ("type 0:");
  oputs (itoa (TYPE (0)));
  oputs ("\n");
  return TYPE (0);
}
