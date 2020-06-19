/* ------------------------------------------------- */
#define X 0
#define Y 1
typedef enum {FALSE, TRUE } bool;

#define DIM 2              /* Di<mension of points */
typedef int tPointi[DIM];  /* Type integer point */
/* Code 1.1 Point type. */


/* ------------------------------------------------- */
typedef struct tVertexStructure tsVertex; /* Used only in NEW(). */
typedef tsVertex *tVertex;
struct tVertexStructure {
  int vnum;               /* Index */
  tPointi v;              /* Coordinates */
  bool ear;               /* TRUE iff an ear */
  tVertex next, prev;
};
tVertex vertices = NULL;  /* "Head" of circular list. */
/* Code 1.2 Vertex structure. */


/* ------------------------------------------------- */
tVertex v;
v = vertices;
do {
  /* Process vertex v */
  v = v->next;
} while ( v != vertices)
/* Code 1.3 Loop to process all vertices. */


/* ------------------------------------------------- */
#define EXIT FAILURE 1
char *malloc();

#define NEW (p, type) \
  if ((p = (type *) malloc (sizeof(type))) == NULL) { \
    print ("NEW: Out of Memory!\n"); \
    exit(EXIT FAILURE); \
  }

#define ADD (head, p) if (head) { \
    p->next = head; \
    p->prev = head->prev; \
    head->prev = p; \
    p->prev->next = p;\
  }\
  else { \
    head = p; \
    head->next = head->prev = p; \
  }

#define FREE(p) if (p) {free ((char*) p); p = NULL;}
/* Code 1.4 NEW and ADD macros. (The backslashes continue the lines
   so that the preprocessor does not treat those as command lines.) 
   FREE is used in Chapter3 and 4. */


/* ------------------------------------------------- */
int Area2( tPointi a, tPinti b, tPointi c) {
  return (b[X] - a[X]) * (c[Y] - a[Y]) - 
         (c[X] - a[x]) * (b[Y] - a[Y]);
}

int AreaPoly2(void){
  int sum = 0;
  tVertex p, a;

  p = vertices;  /* Fixed. */
  a = p->next;   /* Moving. */

  do {
    sum += Area2( p->v, a->v, a->next->v );
    a = a->next;
  } while ( a->next != vertices );
  return sum;
}
/* Code 1.5 Area2 and AreaPoly2. */


/* ------------------------------------------------- */
bool Left( tPointi a, tPointi b, tPointi c) {
  return Area2( a, b, c) > 0;
}

bool LeftOn( tPointi a, tPointi b, tPointi c) {
  return Area2( a, b, c) >= 0;
}

bool Collinear( tPointi a, tPointi b, tPointi c) {
  return Area2( a, b, c) == 0;
}
/* Code 1.6 Left. */


/* ------------------------------------------------- */
bool IntersectProp( tPointi a, tPointi b, tPointi c, tPointi d) {
  /*Eliminate improper cases. */
  if(
    Collinear(a, b, c) ||
    Collinear(a, b, d) ||
    Collinear(c, d, b)
    )
    return FALSE;

  return Xor( Left(a, b, c), Left(a, b, d))
      && Xor( Left(c, d, a), Left(c, d, b));
}
/*Exclusive or: T iff exactly one argument is true. */
bool Xor(bool x, bool y) {
  /*The arguments are negated to ensure that they are 0/1 values. */
  return !x ^ !y;
}
/* Code 1.7 IntersectProp. */


/* ------------------------------------------------- */
bool Between(tPointi a, tPointi b, tPointi c) {
  tPointi ba, ca;

  if ( !Collinear(a, b, c) )
    return FALSE;

  /* If ab not vertical, check betweenness on x; else on y. */
  if ( a[X] != b[X] )
    return ( ( a[X] <= c[X] ) && ( c[X] <= b[X] ) ) || 
           ( ( a[X] >= c[X] ) && ( c[X] >= b[X] ) );
  else
    return ( ( a[Y] <= c[Y] ) && ( c[Y] <= b[Y] ) ) || 
           ( ( a[Y] >= c[Y] ) && ( c[Y] >= b[Y] ) );
}
/* Code 1.8 Between. */


/* ------------------------------------------------- */
/* Code 1.9 . */









