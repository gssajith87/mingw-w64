#ifndef _LIBMANGLE_HXX
#define _LIBMANGLE_HXX

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Garbage collector elements.
 * Tracks allocated memory and points to the next element from the same context.
 * @see sGcCtx
 */
typedef void *pGcElem;

/**
 * Garbage collector context.
 * Tracks first and last of elements in gc context.
 * @see generate_gc()
 * @see release_gc()
 */
typedef struct sGcCtx {
  pGcElem head;                /**< Pointer to first gc element in context.*/
  pGcElem tail;                /**< Pointer to last gc element in context. */
} sGcCtx;

/**
 * Generic token instances.
 * Type of token determined by base descriptor in members.
 * Base descriptor header available in all members through type punning.
 * @see gen_tok()
 */
typedef void *pMToken;

/**
 * Releases memory tracked by context.
 * @param[in] gc Garbage collection context to work on.
 * @see generate_gc()
 */
void release_gc (sGcCtx *gc);

/**
 * Constructs a garbage collection context token.
 * @return Pointer to context.
 * @see release_gc()
 */
sGcCtx *generate_gc (void);

/**
 * Dumps pMToken to a file descriptor for debugging.
 * @param[in] fp File descriptor to print the token to.
 * @param[in] p pMToken chain to print.
 */
void dump_tok (FILE *fp, pMToken p);

/** 
 * Prints C++ name to file descriptor.
 * @param[in] fp Output file descriptor.
 * @param[in] p Token containing information about the C++ name.
 * @see decode_ms_name()
 */
void print_decl (FILE *fp, pMToken p);

/** 
 * Get pointer to decoded C++ name string.
 * Use free() to release returned string.
 * @param[in] r C++ name token.
 * @return pointer to decoded C++ name string.
 * @see decode_ms_name()
 */
char *sprint_decl (pMToken r);

/**
 * Decodes an MSVC export name.
 * @param[in] gc sGcCtx pointer for collecting memory allocations.
 * @param[in] name MSVC C++ mangled export string.
 * @see sprint_decl()
 * @see release_gc()
 * @see pMToken
 * @return Token containing information about the mangled string,
 * use release_gc() to free after use.
 */
pMToken decode_ms_name (sGcCtx *gc, const char *name);
char *encode_ms_name (sGcCtx *gc, pMToken tok);

#ifdef __cplusplus
}
#endif

#endif
