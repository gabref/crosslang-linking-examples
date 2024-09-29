/* workaround.c */
/* Workaround for undefined reference to `__imp___acrt_iob_func' on Windows x64 */
/*
	  dependencies/windows/x64/libetx-embed.a(000005.o): In function `_cgo_preinit_init':
	  \\_\_/GOROOT/src/runtime/cgo/gcc_libinit_windows.c:41: undefined reference to `__imp___acrt_iob_func'
	  dependencies/windows/x64/libetx-embed.a(000005.o): In function `x_cgo_bindm':
	  \\_\_/GOROOT/src/runtime/cgo/gcc_libinit_windows.c:99: undefined reference to `__imp___acrt_iob_func'
	  dependencies/windows/x64/libetx-embed.a(000005.o): In function `x_cgo_notify_runtime_init_done':
	  \\_\_/GOROOT/src/runtime/cgo/gcc_libinit_windows.c:112: undefined reference to `__imp___acrt_iob_func'
	  dependencies/windows/x64/libetx-embed.a(000005.o): In function `_cgo_beginthread':
	  \\_\_/GOROOT/src/runtime/cgo/gcc_libinit_windows.c:156: undefined reference to `__imp___acrt_iob_func'
	  dependencies/windows/x64/libetx-embed.a(000007.o): In function `x_cgo_thread_start':
	  \\_\_/GOROOT/src/runtime/cgo/gcc_util.c:18: undefined reference to `__imp___acrt_iob_func'
	  collect2: error: ld returned 1 exit status
*/
// https://github.com/rust-lang/rust/issues/47048#issuecomment-530376978

#define _CRTBLD
#include <stdio.h>

FILE *__cdecl __acrt_iob_func(unsigned index)
{
    return &(__iob_func()[index]);
}

typedef FILE *__cdecl (*_f__acrt_iob_func)(unsigned index);
_f__acrt_iob_func __MINGW_IMP_SYMBOL(__acrt_iob_func) = __acrt_iob_func;
