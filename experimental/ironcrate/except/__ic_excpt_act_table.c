#include <ic_stdc.h>

struct _ic_exception_action_t
__ic_excpt_act_table[] =
{
  { (unsigned long) STATUS_ACCESS_VIOLATION, IC_SIGSEGV, IC_SIG_DFL },
  { (unsigned long) STATUS_ILLEGAL_INSTRUCTION, IC_SIGILL,  IC_SIG_DFL },
  { (unsigned long) STATUS_PRIVILEGED_INSTRUCTION, IC_SIGILL,  IC_SIG_DFL },
  { (unsigned long) STATUS_FLOAT_DENORMAL_OPERAND, IC_SIGFPE, IC_SIG_DFL },
  { (unsigned long) STATUS_FLOAT_DIVIDE_BY_ZERO, IC_SIGFPE, IC_SIG_DFL },
  { (unsigned long) STATUS_FLOAT_INEXACT_RESULT, IC_SIGFPE, IC_SIG_DFL },
  { (unsigned long) STATUS_FLOAT_INVALID_OPERATION, IC_SIGFPE, IC_SIG_DFL },
  { (unsigned long) STATUS_FLOAT_OVERFLOW, IC_SIGFPE, IC_SIG_DFL },
  { (unsigned long) STATUS_FLOAT_STACK_CHECK, IC_SIGFPE, IC_SIG_DFL },
  { (unsigned long) STATUS_FLOAT_UNDERFLOW, IC_SIGFPE, IC_SIG_DFL },
};

