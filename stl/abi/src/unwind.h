#pragma once

#include <cstdint>

extern "C" {

using _Unwind_Word = uintptr_t ;
using _Unwind_Sword = intptr_t ;
using _Unwind_Ptr =  uintptr_t ;
using _Unwind_Internal_Ptr =  uintptr_t ;
using _Unwind_Exception_Class = uint64_t ;

using _sleb128_t =  intptr_t ;
using _uleb128_t =  uintptr_t ;

struct _Unwind_Context;
struct _Unwind_Exception;

typedef enum {
    _URC_NO_REASON = 0,
#if defined(__arm__) && !defined(__USING_SJLJ_EXCEPTIONS__) && \
    !defined(__ARM_DWARF_EH__)
    _URC_OK = 0, /* used by ARM EHABI */
#endif
    _URC_FOREIGN_EXCEPTION_CAUGHT = 1,

    _URC_FATAL_PHASE2_ERROR = 2,
    _URC_FATAL_PHASE1_ERROR = 3,
    _URC_NORMAL_STOP = 4,

    _URC_END_OF_STACK = 5,
    _URC_HANDLER_FOUND = 6,
    _URC_INSTALL_CONTEXT = 7,
    _URC_CONTINUE_UNWIND = 8,
#if defined(__arm__) && !defined(__USING_SJLJ_EXCEPTIONS__) && \
    !defined(__ARM_DWARF_EH__)
    _URC_FAILURE = 9 /* used by ARM EHABI */
#endif
} _Unwind_Reason_Code;

typedef enum {
    _UA_SEARCH_PHASE = 1,
    _UA_CLEANUP_PHASE = 2,

    _UA_HANDLER_FRAME = 4,
    _UA_FORCE_UNWIND = 8,
    _UA_END_OF_STACK = 16 /* gcc extension to C++ ABI */
} _Unwind_Action;

typedef void (*_Unwind_Exception_Cleanup_Fn)(_Unwind_Reason_Code,
                                             struct _Unwind_Exception *);

struct _Unwind_Exception {
    _Unwind_Exception_Class exception_class;
    _Unwind_Exception_Cleanup_Fn exception_cleanup;
    _Unwind_Word private_1;
    _Unwind_Word private_2;
    /* The Itanium ABI requires that _Unwind_Exception objects are "double-word
     * aligned".  GCC has interpreted this to mean "use the maximum useful
     * alignment for the target"; so do we. */
} __attribute__((__aligned__));

typedef _Unwind_Reason_Code (*_Unwind_Stop_Fn)(int, _Unwind_Action,
                                               _Unwind_Exception_Class,
                                               struct _Unwind_Exception *,
                                               struct _Unwind_Context *,
                                               void *);

typedef _Unwind_Reason_Code (*_Unwind_Personality_Fn)(
        int, _Unwind_Action, _Unwind_Exception_Class, struct _Unwind_Exception *,
        struct _Unwind_Context *);

typedef _Unwind_Personality_Fn __personality_routine;

typedef _Unwind_Reason_Code (*_Unwind_Trace_Fn)(struct _Unwind_Context *,
                                                void *);

#if defined(__arm__) && !defined(__APPLE__)

typedef enum {
  _UVRSC_CORE = 0,        /* integer register */
  _UVRSC_VFP = 1,         /* vfp */
  _UVRSC_WMMXD = 3,       /* Intel WMMX data register */
  _UVRSC_WMMXC = 4        /* Intel WMMX control register */
} _Unwind_VRS_RegClass;

typedef enum {
  _UVRSD_UINT32 = 0,
  _UVRSD_VFPX = 1,
  _UVRSD_UINT64 = 3,
  _UVRSD_FLOAT = 4,
  _UVRSD_DOUBLE = 5
} _Unwind_VRS_DataRepresentation;

typedef enum {
  _UVRSR_OK = 0,
  _UVRSR_NOT_IMPLEMENTED = 1,
  _UVRSR_FAILED = 2
} _Unwind_VRS_Result;

#if !defined(__USING_SJLJ_EXCEPTIONS__) && !defined(__ARM_DWARF_EH__)
typedef uint32_t _Unwind_State;
#define _US_VIRTUAL_UNWIND_FRAME  ((_Unwind_State)0)
#define _US_UNWIND_FRAME_STARTING ((_Unwind_State)1)
#define _US_UNWIND_FRAME_RESUME   ((_Unwind_State)2)
#define _US_ACTION_MASK           ((_Unwind_State)3)
#define _US_FORCE_UNWIND          ((_Unwind_State)8)
#endif

_Unwind_VRS_Result _Unwind_VRS_Get(struct _Unwind_Context *__context,
  _Unwind_VRS_RegClass __regclass,
  uint32_t __regno,
  _Unwind_VRS_DataRepresentation __representation,
  void *__valuep);

_Unwind_VRS_Result _Unwind_VRS_Set(struct _Unwind_Context *__context,
  _Unwind_VRS_RegClass __regclass,
  uint32_t __regno,
  _Unwind_VRS_DataRepresentation __representation,
  void *__valuep);

static __inline__
_Unwind_Word _Unwind_GetGR(struct _Unwind_Context *__context, int __index) {
  _Unwind_Word __value;
  _Unwind_VRS_Get(__context, _UVRSC_CORE, __index, _UVRSD_UINT32, &__value);
  return __value;
}

static __inline__
void _Unwind_SetGR(struct _Unwind_Context *__context, int __index,
                   _Unwind_Word __value) {
  _Unwind_VRS_Set(__context, _UVRSC_CORE, __index, _UVRSD_UINT32, &__value);
}

static __inline__
_Unwind_Word _Unwind_GetIP(struct _Unwind_Context *__context) {
  _Unwind_Word __ip = _Unwind_GetGR(__context, 15);
  return __ip & ~(_Unwind_Word)(0x1); /* Remove thumb mode bit. */
}

static __inline__
void _Unwind_SetIP(struct _Unwind_Context *__context, _Unwind_Word __value) {
  _Unwind_Word __thumb_mode_bit = _Unwind_GetGR(__context, 15) & 0x1;
  _Unwind_SetGR(__context, 15, __value | __thumb_mode_bit);
}
#else

_Unwind_Word _Unwind_GetGR(struct _Unwind_Context *, int);

void _Unwind_SetGR(struct _Unwind_Context *, int, _Unwind_Word);

_Unwind_Word _Unwind_GetIP(struct _Unwind_Context *);

void _Unwind_SetIP(struct _Unwind_Context *, _Unwind_Word);

#endif


_Unwind_Word _Unwind_GetIPInfo(struct _Unwind_Context *, int *);

_Unwind_Word _Unwind_GetCFA(struct _Unwind_Context *);

_Unwind_Word _Unwind_GetBSP(struct _Unwind_Context *);

void *_Unwind_GetLanguageSpecificData(struct _Unwind_Context *);

_Unwind_Ptr _Unwind_GetRegionStart(struct _Unwind_Context *);

/* DWARF EH functions; currently not available on Darwin/ARM */
#if !defined(__APPLE__) || !defined(__arm__)

_Unwind_Reason_Code _Unwind_RaiseException(struct _Unwind_Exception *);

_Unwind_Reason_Code _Unwind_ForcedUnwind(struct _Unwind_Exception *,
                                         _Unwind_Stop_Fn, void *);

void _Unwind_DeleteException(struct _Unwind_Exception *);

void _Unwind_Resume(struct _Unwind_Exception *);

_Unwind_Reason_Code _Unwind_Resume_or_Rethrow(struct _Unwind_Exception *);

#endif

_Unwind_Reason_Code _Unwind_Backtrace(_Unwind_Trace_Fn, void *);

/* setjmp(3)/longjmp(3) stuff */
typedef struct SjLj_Function_Context *_Unwind_FunctionContext_t;

void _Unwind_SjLj_Register(_Unwind_FunctionContext_t);

void _Unwind_SjLj_Unregister(_Unwind_FunctionContext_t);

_Unwind_Reason_Code _Unwind_SjLj_RaiseException(struct _Unwind_Exception *);

_Unwind_Reason_Code _Unwind_SjLj_ForcedUnwind(struct _Unwind_Exception *,
                                              _Unwind_Stop_Fn, void *);

void _Unwind_SjLj_Resume(struct _Unwind_Exception *);

_Unwind_Reason_Code _Unwind_SjLj_Resume_or_Rethrow(struct _Unwind_Exception *);

void *_Unwind_FindEnclosingFunction(void *);

_Unwind_Ptr _Unwind_GetDataRelBase(struct _Unwind_Context *);

_Unwind_Ptr _Unwind_GetTextRelBase(struct _Unwind_Context *);

}
#endif

#endif

