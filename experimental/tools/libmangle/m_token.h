#ifndef _M_TOKEN_HXX
#define _M_TOKEN_HXX

typedef enum eMToken {
  eMToken_none = 0,
  eMToken_value = 1,
  eMToken_name = 2,
  eMToken_dim = 3,
  eMToken_unary = 4,
  eMToken_binary = 5,
  eMToken_MAX
} eMToken;

typedef enum eMSToken {
  eMST_unmangled = 0, /* eMToken_name */
  eMST_nttp = 1,
  eMST_name = 2,
  eMST_colon = 3, /* ...: */
  eMST_rtti = 4,
  eMST_cv = 5,
  eMST_vftable = 6, eMST_vbtable = 7, eMST_vcall = 8,
  eMST_opname = 9,
  eMST_templargname,
  eMST_type,
  
  eMST_dim, /* eMToken_dim */
  eMST_val, /* sMToken_val */
  eMST_gcarray, /* __gc[,,,,] */
  eMST_slashed, /* eMToken_unary */
  eMST_array,
  eMST_element,
  eMST_template_argument_list,
  eMST_ltgt, /* <> */
  eMST_frame, /* {} */
  eMST_throw, /* throw ... */
  eMST_rframe, /* () */
  eMST_destructor, /* ~ */
  eMST_oper, /* indicates that this is an operand */
  eMST_colonarray, /* ::[] */
  eMST_lexical_frame,
  eMST_scope,
  eMST_udt_returning,
  eMST_coloncolon, /*  eMToken_binary :: */
  eMST_assign,
  eMST_templateparam,
  eMST_nonetypetemplateparam,
  eMST_exp, /* dim 'e' dim */
  eMST_combine,
  eMST_ecsu,
  eMST_based,
  eMST_initfield
} eMSToken;

typedef struct sMToken_base {
  enum eMToken kind;
  enum eMSToken subkind;
  union uMToken *chain;
  int flags;
} sMToken_base;

#define MTOKEN_KIND(PT)		((PT)->base.kind)
#define MTOKEN_SUBKIND(PT)	((PT)->base.subkind)
#define MTOKEN_CHAIN(PT)	((PT)->base.chain)
#define MTOKEN_FLAGS(PT)	((PT)->base.flags)

#define MTOKEN_FLAGS_UDC	0x1
#define MTOKEN_FLAGS_NOTE	0x2
#define MTOKEN_FLAGS_PTRREF	0x4
#define MTOKEN_FLAGS_ARRAY	0x8

typedef struct sMToken_value {
  sMToken_base base;
  uint64_t value;
  uint64_t size : 5;
  uint64_t is_signed : 1;
} sMToken_value;

#define MTOKEN_VALUE(PT)	((PT)->value.value)
#define MTOKEN_VALUE_SIGNED(PT)	((PT)->value.is_signed)
#define MTOKEN_VALUE_SIZE(PT)	((PT)->value.size)

typedef struct sMToken_name {
  sMToken_base base;
  char name[1];
} sMToken_name;

#define MTOKEN_NAME(PT)		((PT)->name.name)

typedef struct sMToken_dim {
  sMToken_base base;
  union uMToken *value;
  union uMToken *non_tt_param;
  int beNegate;
} sMToken_dim;

#define MTOKEN_DIM_VALUE(PT)	((PT)->dim.value)
#define MTOKEN_DIM_NTTP(PT)	((PT)->dim.non_tt_param)
#define MTOKEN_DIM_NEGATE(PT)	((PT)->dim.beNegate)

typedef struct sMToken_Unary
{
  sMToken_base base;
  union uMToken *unary;
} sMToken_Unary;

#define MTOKEN_UNARY(PT)	((PT)->unary.unary)

typedef struct sMToken_binary {
  sMToken_base base;
  union uMToken *left;
  union uMToken *right;
} sMToken_binary;

#define MTOKEN_BINARY_LEFT(PT)		((PT)->binary.left)
#define MTOKEN_BINARY_RIGHT(PT)		((PT)->binary.right)

typedef union uMToken {
  sMToken_base base;
  sMToken_value value;
  sMToken_name name;
  sMToken_dim dim;
  sMToken_Unary unary;
  sMToken_binary binary;
} uMToken;

uMToken *gen_tok (enum eMToken kind, enum eMSToken subkind, size_t addend);

/**
 * Frees uMToken chains.
 * @param tok uMToken to be freed, will always be set to NULL.
 * @see uMToken
 * @return Returns a NULL pointer.
 */
uMToken *release_tok (uMToken *tok);

/**
 * Chains uMTokens together.
 * @param[in] l uMtoken chain to link up with.
 * @param[in] add uMtoken to add to chain.
 * @see uMToken.
 */
uMToken *chain_tok (uMToken *l, uMToken *add);

/**
 * Dumps uMToken to a file descriptor for debugging.
 * @param[in] fp File descriptor to print the token to.
 * @param[in] p uMToken chain to print.
 * @see uMToken
 */
void dump_tok (FILE *fp, uMToken *p);

/** 
 * Prints C++ name to file descriptor.
 * @param[in] fp Output file descriptor.
 * @param[in] p Token containing information about the C++ name.
 * @see decode_ms_name()
 * @see uMToken
 */
void print_decl (FILE *fp, uMToken *p);

uMToken *gen_value (enum eMSToken skind, uint64_t val, int is_signed, int size);
uMToken *gen_name (enum eMSToken skind, const char *name);
uMToken *gen_dim (enum eMSToken skind, uint64_t val, const char *non_tt_param, int fSigned, int fNegate);
uMToken *gen_unary (enum eMSToken skind, uMToken *un);
uMToken *gen_binary (enum eMSToken skind, uMToken *l, uMToken *r);

#endif
