#ifndef _M_TOKEN_HXX
#define _M_TOKEN_HXX

/**
 * eMToken is used to inform gen_tok()
 * the type of Token to generate.
 * @see gen_tok()
 * @see eMSToken
 * @see uMToken
 */
typedef enum eMToken {
  eMToken_none = 0,                /**< Token type: None.  */
  eMToken_value = 1,               /**< Token type: Value. */
  eMToken_name = 2,                /**< Token type: Name.  */
  eMToken_dim = 3,                 /**< Token type: Dim.   */
  eMToken_unary = 4,               /**< Token type: Unary  */
  eMToken_binary = 5,              /**< Token type: Binary */
  eMToken_MAX                      /**< Unused sentinel.   */
} eMToken;

/**
 * eMToken "Subkind" enumeration list.
 * @see eMToken
 */
typedef enum eMSToken {
  eMST_unmangled = 0,              /**< Name is unmagled. */
  eMST_nttp = 1,
  eMST_name = 2,                   /**< Decoded function name. */
  eMST_colon = 3, /* ...: */       /**< Class member accessibility. */
  eMST_rtti = 4,
  eMST_cv = 5,                     /**< Function call convention / data qualifiers / pointer. */
  eMST_vftable = 6,                /**< Virtual Function Table. */
  eMST_vbtable = 7,                /**< Virtual Base Table. */
  eMST_vcall = 8,                  /**< Virtual Function Call. */
  eMST_opname = 9,                 /**< Overloaded operator. */
  eMST_templargname = 10,          /**< Explicit template arg name. */
  eMST_type = 11,                  /**< Function return type. */
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
  eMST_combine,                    /** Unary grouping. */
  eMST_ecsu,
  eMST_based,
  eMST_initfield
} eMSToken;

/**
 * Token base descriptor about decoded fragments
 * @see eMToken
 * @see eMSToken
 * @see uMToken
 */
typedef struct sMToken_base {
  enum eMToken kind;            /**< Token kind. */
  enum eMSToken subkind;        /**< Token Subkind. */
  union uMToken *chain;         /**< Pointer to next token. NULL terminated. */
  int flags;
} sMToken_base;

/**Sets the token kind, @a PT pointer to a base uMToken. */
#define MTOKEN_KIND(PT)		((PT)->base.kind)

/**Sets the token subkind, @a PT pointer to a base uMToken. */
#define MTOKEN_SUBKIND(PT)	((PT)->base.subkind)

/**Sets the pointer to the next token in the chain. */
#define MTOKEN_CHAIN(PT)	((PT)->base.chain)
#define MTOKEN_FLAGS(PT)	((PT)->base.flags)

#define MTOKEN_FLAGS_UDC	0x1
#define MTOKEN_FLAGS_NOTE	0x2
#define MTOKEN_FLAGS_PTRREF	0x4
#define MTOKEN_FLAGS_ARRAY	0x8

typedef struct sMToken_value {
  sMToken_base base;            /**< Base descriptor header. */
  uint64_t value;
  uint64_t size : 5;            /**< Byte width of value. */
  uint64_t is_signed : 1;       /**< Value signed bit */
} sMToken_value;

/**Sets the token value. */
#define MTOKEN_VALUE(PT)	((PT)->value.value)

/**Sets the signed bit on value token. */
#define MTOKEN_VALUE_SIGNED(PT)	((PT)->value.is_signed)

/**Sets the byte width of value in value token. */
#define MTOKEN_VALUE_SIZE(PT)	((PT)->value.size)

/**
 * Name Token contains the text string
 * of the decoded fragment.
 */
typedef struct sMToken_name {
  sMToken_base base;            /**< Base descriptor header. */
  char name[1];                 /**< Pointer to text string.*/
} sMToken_name;

/** Retrieve or set the name string, @a PT pointer to a name uMToken */
#define MTOKEN_NAME(PT)		((PT)->name.name)

typedef struct sMToken_dim {
  sMToken_base base;            /**< Base descriptor header. */
  union uMToken *value;
  union uMToken *non_tt_param;
  int beNegate;
} sMToken_dim;

#define MTOKEN_DIM_VALUE(PT)	((PT)->dim.value)
#define MTOKEN_DIM_NTTP(PT)	((PT)->dim.non_tt_param)
#define MTOKEN_DIM_NEGATE(PT)	((PT)->dim.beNegate)

typedef struct sMToken_Unary
{
  sMToken_base base;            /**< Base descriptor header. */
  union uMToken *unary;
} sMToken_Unary;

/**Sets the token unary, @a PT pointer to a unary uMToken. */
#define MTOKEN_UNARY(PT)	((PT)->unary.unary)

typedef struct sMToken_binary {
  sMToken_base base;            /**< Base descriptor header. */
  union uMToken *left;
  union uMToken *right;
} sMToken_binary;

#define MTOKEN_BINARY_LEFT(PT)		((PT)->binary.left)
#define MTOKEN_BINARY_RIGHT(PT)		((PT)->binary.right)

/**
 * Generic tokens instances.
 * Type of token determined by base descriptor in members.
 * @see sMToken_base
 * @see sMToken_value
 * @see sMToken_name
 * @see sMToken_dim
 * @see sMToken_Unary
 * @see sMToken_binary
 */
typedef union uMToken {
  sMToken_base base;
  sMToken_value value;
  sMToken_name name;
  sMToken_dim dim;
  sMToken_Unary unary;
  sMToken_binary binary;
} uMToken;

/**
 * gen_tok constructs uMToken instances
 * Instances are destroyed with release_tok().
 * @param[in] kind Kind of token to construct
 * @param[in] subkind Subkind of token to construct
 * @param[in] addend Additional byte padding at the end.
 * @see uMToken
 * @see eMToken
 * @see eMSToken
 * @see release_tok()
 */
uMToken *gen_tok (enum eMToken kind, enum eMSToken subkind, size_t addend);

/**
 * Frees uMToken chains recursively.
 * @param[in] tok uMToken to be freed, will always be set to NULL.
 * @see uMToken
 * @return a NULL pointer.
 */
uMToken *release_tok (uMToken *tok);

/**
 * Chains uMTokens together.
 * @param[in] l uMtoken chain to link up with.
 * @param[in] add uMtoken to add to chain.
 * @return @a unchanged l
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

/**
 * Constructs a "value" kind token.
 * @param[in] skind Token subkind.
 * @param[in] val Sets the value on token,
 * @param[in] is_signed Signed bit of \a val.
 * @param[in] size Width of \a val.
 * @return Pointer to token.
 * @see uMToken
 * @see eMSToken
 */
uMToken *gen_value (enum eMSToken skind, uint64_t val, int is_signed, int size);

/**
 * Constructs a "name" kind value.
 * @param[in] skind Token subkind.
 * @param[in] name Pointer to name string.
 * @return Pointer to token.
 * @see uMToken
 * @see eMSToken
 */
uMToken *gen_name (enum eMSToken skind, const char *name);
uMToken *gen_dim (enum eMSToken skind, uint64_t val, const char *non_tt_param, int fSigned, int fNegate);
uMToken *gen_unary (enum eMSToken skind, uMToken *un);
uMToken *gen_binary (enum eMSToken skind, uMToken *l, uMToken *r);

#endif
