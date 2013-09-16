cmake_minimum_required (VERSION 2.6)
project (TCMalloc CXX C)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

include(CheckTypeSize)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckCXXCompilerFlag)

macro(set_config_option VARNAME STRING)
  set(${VARNAME} TRUE)
  list(APPEND CONFIG_OPTIONS ${STRING})
  message(STATUS "Found " ${STRING})
endmacro(set_config_option)

# check if the machine is 64 bits (this is more reliable than using
# CMAKE_SIZEOF_VOID_P, which does not seem to work e.g. on some Suse
# machines) -- from Gmsh's config file
check_type_size("void*" SIZEOF_VOID_P)
if(SIZEOF_VOID_P EQUAL 8)
  set_config_option(HAVE_64BIT_SIZE_T "64Bit")
endif(SIZEOF_VOID_P EQUAL 8)

if (APPLE)
    set(CMAKE_FIND_LIBRARY_SUFFIXES .lib ${CMAKE_FIND_LIBRARY_SUFFIXES})
    set(CMAKE_FIND_LIBRARY_SUFFIXES .dylib ${CMAKE_FIND_LIBRARY_SUFFIXES})
endif (APPLE)

check_cxx_source_compiles("int main () { return __builtin_expect(main != 0, 1) ; return 0; }" HAVE_BUILTIN_EXPECT)
check_cxx_source_compiles("int main () { void *sp = __builtin_stack_pointer() ; return 0; }" HAVE_BUILTIN_STACK_POINTER)
check_cxx_source_compiles("
  #include <conflict-signal.h> 
  int main(int argc, char* argv[]) {return 0;} " HAVE_CONFLICT_SIGNAL_H)
check_cxx_source_compiles("
  #include <cygwin/signal.h> 
  int main(int argc, char* argv[]) {return 0;} " HAVE_CYGWIN_SIGNAL_H)
check_cxx_source_compiles("
  #include <stdlib.h>
  #include <malloc.h>
  int main(int argc, char* argv[]) {cfree(NULL); return 0;} " HAVE_DECL_CFREE)
check_cxx_source_compiles("
  #include <stdlib.h>
  #include <malloc.h>
  int main(int argc, char* argv[]) {void* ptr = memalign(0, 0); return 0;} " HAVE_DECL_MEMALIGN)
check_cxx_source_compiles("
  #include <time.h>
  int main(int argc, char* argv[]) {int t = nanosleep(NULL, NULL); return 0;} " HAVE_DECL_NANOSLEEP)
check_cxx_source_compiles("
  #include <stdlib.h>
  #include <malloc.h>
  int main(int argc, char* argv[]) {void* ptr;int a = posix_memalign(&ptr, 0, 0); return 0;} " HAVE_DECL_POSIX_MEMALIGN)
check_cxx_source_compiles("
  #include <stdlib.h>
  #include <malloc.h>
  int main(int argc, char* argv[]) {void* ptr = pvalloc(0); return 0;} " HAVE_DECL_PVALLOC)
check_cxx_source_compiles("
  #include <unistd.h>
  int main(int argc, char* argv[]) {sleep(0); return 0;} " HAVE_DECL_SLEEP)
check_cxx_source_compiles("
  #include <sys/utsname.h>
  int main(int argc, char* argv[]) {struct utsname buf; int a = uname(&buf); return 0;} " HAVE_DECL_UNAME)
check_cxx_source_compiles("
  #include <stdlib.h>
  #include <malloc.h>
  int main(int argc, char* argv[]) {void* ptr = valloc(0); return 0;} " HAVE_DECL_VALLOC)
check_cxx_source_compiles("
 #include <dlfcn.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_DLFCN_H)
check_cxx_source_compiles("
 #include <elf.h>
 int main(int argc, char* argv[]) {Elf32_Versym a; return 0;} " HAVE_ELF32_VERSYM)
check_cxx_source_compiles("
 #include <execinfo.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_EXECINFO_H)
check_cxx_source_compiles("
 #include <fcntl.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_FCNTL_H)
check_cxx_source_compiles("
 #include <features.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_FEATURES_H)
check_cxx_source_compiles("
 #include <unistd.h>
 int main(int argc, char* argv[]) {pid_t a = fork(); return 0;} " HAVE_FORK)
check_cxx_source_compiles("
 #include <unistd.h>
 #include <sys/types.h>
 int main(int argc, char* argv[]) {uid_t a = geteuid(); return 0;} " HAVE_GETEUID)
check_cxx_source_compiles("
 #include <unistd.h>
 int main(int argc, char* argv[]) {int a = getpagesize(); return 0;} " HAVE_GETPAGESIZE)
check_cxx_source_compiles("
 #include <glob.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_GLOB_H)
check_cxx_source_compiles("
 #include <grp.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_GRP_H)
check_cxx_source_compiles("
 #include <inttypes.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_INTTYPES_H)
check_cxx_source_compiles("
 #include <libunwind.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_LIBUNWIND_H)
check_cxx_source_compiles("
 #include <linux/ptrace.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_LINUX_PTRACE_H)
check_cxx_source_compiles("
 #include <malloc.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_MALLOC_H)
check_cxx_source_compiles("
 #include <malloc/malloc.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_MALLOC_MALLOC_H)
check_cxx_source_compiles("
 #include <memory.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_MEMORY_H)
 include(CheckCXXSourceRuns)

check_cxx_source_runs("
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#if !defined STDC_HEADERS && !defined HAVE_STDLIB_H
char *malloc ();
#endif

/* This mess was copied from the GNU getpagesize.h.  */
#ifndef HAVE_GETPAGESIZE
# ifdef _SC_PAGESIZE
#  define getpagesize() sysconf(_SC_PAGESIZE)
# else /* no _SC_PAGESIZE */
#  ifdef HAVE_SYS_PARAM_H
#   include <sys/param.h>
#   ifdef EXEC_PAGESIZE
#    define getpagesize() EXEC_PAGESIZE
#   else /* no EXEC_PAGESIZE */
#    ifdef NBPG
#     define getpagesize() NBPG * CLSIZE
#     ifndef CLSIZE
#      define CLSIZE 1
#     endif /* no CLSIZE */
#    else /* no NBPG */
#     ifdef NBPC
#      define getpagesize() NBPC
#     else /* no NBPC */
#      ifdef PAGESIZE
#       define getpagesize() PAGESIZE
#      endif /* PAGESIZE */
#     endif /* no NBPC */
#    endif /* no NBPG */
#   endif /* no EXEC_PAGESIZE */
#  else /* no HAVE_SYS_PARAM_H */
#   define getpagesize() 8192	/* punt totally */
#  endif /* no HAVE_SYS_PARAM_H */
# endif /* no _SC_PAGESIZE */

#endif /* no HAVE_GETPAGESIZE */

int
main ()
{
  char *data, *data2, *data3;
  const char *cdata2;
  int i, pagesize;
  int fd, fd2;

  pagesize = getpagesize ();

  /* First, make a file with some known garbage in it. */
  data = (char *) malloc (pagesize);
  if (!data)
    return 1;
  for (i = 0; i < pagesize; ++i)
    *(data + i) = rand ();
  umask (0);
  fd = creat (\"conftest.mmap\", 0600);
  if (fd < 0)
    return 2;
  if (write (fd, data, pagesize) != pagesize)
    return 3;
  close (fd);

  /* Next, check that the tail of a page is zero-filled.  File must have
     non-zero length, otherwise we risk SIGBUS for entire page.  */
  fd2 = open (\"conftest.txt\", O_RDWR | O_CREAT | O_TRUNC, 0600);
  if (fd2 < 0)
    return 4;
  cdata2 = \"\";
  if (write (fd2, cdata2, 1) != 1)
    return 5;
  data2 = (char *) mmap (0, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0L);
  if (data2 == MAP_FAILED)
    return 6;
  for (i = 0; i < pagesize; ++i)
    if (*(data2 + i))
      return 7;
  close (fd2);
  if (munmap (data2, pagesize))
    return 8;

  /* Next, try to mmap the file at a fixed address which already has
     something else allocated at it.  If we can, also make sure that
     we see the same garbage.  */
  fd = open (\"conftest.mmap\", O_RDWR);
  if (fd < 0)
    return 9;
  if (data2 != mmap (data2, pagesize, PROT_READ | PROT_WRITE,
		     MAP_PRIVATE | MAP_FIXED, fd, 0L))
    return 10;
  for (i = 0; i < pagesize; ++i)
    if (*(data + i) != *(data2 + i))
      return 11;

  /* Finally, make sure that changes to the mapped area do not
     percolate back to the file as seen by read().  (This is a bug on
     some variants of i386 svr4.0.)  */
  for (i = 0; i < pagesize; ++i)
    *(data2 + i) = *(data2 + i) + 1;
  data3 = (char *) malloc (pagesize);
  if (!data3)
    return 12;
  if (read (fd, data3, pagesize) != pagesize)
    return 13;
  for (i = 0; i < pagesize; ++i)
    if (*(data + i) != *(data3 + i))
      return 14;
  close (fd);
  return 0;
} " HAVE_MMAP)
#"
check_cxx_source_runs("namespace Outer { namespace Inner { int i = 0; }}
int main () { using namespace Outer::Inner; return i; ; return 0; }" HAVE_NAMESPACES)
check_cxx_source_compiles(" #include <poll.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_POLL_H)
check_cxx_source_runs("extern char* program_invocation_name;
int main () { return !(*program_invocation_name); ; return 1; }" HAVE_PROGRAM_INVOCATION_NAME)
set(OLD_REQUIRED_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES})
set(CMAKE_REQUIRED_LIBRARIES "-pthread")
check_cxx_source_compiles("#include <pthread.h>
int main () { pthread_t th; pthread_join(th, 0); pthread_attr_init(0); pthread_cleanup_push(0, 0);
	       pthread_create(0,0,0,0); pthread_cleanup_pop(0); ; return 0; }" HAVE_PTHREAD)
set(CMAKE_REQUIRED_LIBRARIES ${OLD_REQUIRED_LIBRARIES})
check_cxx_source_compiles(" #include <pwd.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_PWD_H)
check_cxx_source_compiles(" #include <unistd.h>
int main(int argc, char* argv[]) {void* p = sbrk(NULL); return 0;} " HAVE_SBRK)
check_cxx_source_compiles(" #include <sched.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_SCHED_H)
 check_cxx_source_compiles(" #include <stdint.h>
 int main(int argc, char* argv[]) {return 0;} " HHAVE_STDINT_H)
 set(HAVE_STDINT_H "${HHAVE_STDINT_H}")
check_cxx_source_compiles(" #include <stdlib.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_STDLIB_H)
check_cxx_source_compiles(" #include <strings.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_STRINGS_H)
check_cxx_source_compiles(" #include <string.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_STRING_H)
check_cxx_source_compiles(" #include <malloc.h>
 int main(int argc, char* argv[]) {struct mallinfo m; return 0;} " HAVE_STRUCT_MALLINFO)
check_cxx_source_compiles(" #include <sys/cdefs.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_SYS_CDEFS_H)
check_cxx_source_compiles(" #include <sys/malloc.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_SYS_MALLOC_H)
check_cxx_source_compiles(" #include <sys/param.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_SYS_PARAM_H)
check_cxx_source_compiles(" #include <sys/prctl.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_SYS_PRCTL_H)
check_cxx_source_compiles(" #include <sys/resource.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_SYS_RESOURCE_H)
check_cxx_source_compiles(" #include <sys/socket.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_SYS_SOCKET_H)
check_cxx_source_compiles(" #include <sys/stat.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_SYS_STAT_H)
check_cxx_source_compiles(" #include <sys/syscall.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_SYS_SYSCALL_H)
check_cxx_source_compiles(" #include <sys/types.h>
 int main(int argc, char* argv[]) {return 0;} " HHAVE_SYS_TYPES_H)
check_cxx_source_compiles(" #include <sys/ucontext.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_SYS_UCONTEXT_H)
check_cxx_source_compiles(" #include <sys/wait.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_SYS_WAIT_H)
check_cxx_source_runs("#if defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__)) && ((__GNUC__ < 4) || (__GNUC__ == 4 && __GNUC_MINOR__ < 1) || (__GNUC__ == 4 && __GNUC_MINOR__ == 1 && __GNUC_PATCHLEVEL__ < 2))
#error gcc has this bug: http://gcc.gnu.org/ml/gcc-bugs/2006-09/msg02275.html
#endif
#if defined(__MINGW32__)
#error mingw doesn't really support tls
#endif
int main () { static __thread int p = 0 ; return 0; }" HAVE_TLS)
check_cxx_source_compiles(" #include <ucontext.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_UCONTEXT_H)
check_cxx_source_compiles(" #include <unistd.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_UNISTD_H)
check_cxx_source_compiles(" #include <unwind.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_UNWIND_H)
check_cxx_source_compiles(" #include <valgrind.h>
 int main(int argc, char* argv[]) {return 0;} " HAVE_VALGRIND_H)
check_cxx_source_compiles("#include <stdlib.h>
       static void foo(void) __attribute__ ((unused)); void foo(void) { exit(1); }
       int main () { ; return 0; }" HAVE___ATTRIBUTE__)
check_cxx_source_compiles("#include <unistd.h>
       int main () { char **env = __environ ; return 0; }" HAVE___ENVIRON)
check_cxx_source_compiles(" int main(int argc, char* argv[]) {__int64 a = 0; return 0;} " HAVE___INT64)
#undef INSTALL_PREFIX

check_cxx_source_compiles("#include <stdint.h>
       int main () { int32_t v1 = 0; intptr_t v2 = 0; return (&v1 - &v2) ; return 0; }" INT32_EQUALS_INTPTR)

#undef LT_OBJDIR

#undef MALLOC_HOOK_MAYBE_VOLATILE TODO: change name ``volatile''
#define MALLOC_HOOK_MAYBE_VOLATILE volatile
check_cxx_source_compiles("#include <malloc.h>
void* (* volatile __malloc_hook)(size_t, const void*) = 0;
int main () { ; return 0; }" MALLOC_HOOK_MAYBE_VOLATILE)

#undef NO_MINUS_C_MINUS_O

#undef PACKAGE

#undef PACKAGE_BUGREPORT

#undef PACKAGE_NAME

#undef PACKAGE_STRING

#undef PACKAGE_TARNAME

#undef PACKAGE_URL

#undef PACKAGE_VERSION

#undef PC_FROM_UCONTEXT
set(PC_FIELDS "")
list(APPEND PC_FIELDS "uc_mcontext.gregs[REG_PC]") # Solaris x86 (32 + 64 bit)
list(APPEND PC_FIELDS "uc_mcontext.gregs[REG_EIP]") # Linux (i386)
list(APPEND PC_FIELDS "uc_mcontext.gregs[REG_RIP]") # Linux (x86_64)
list(APPEND PC_FIELDS "uc_mcontext.sc_ip"           ) # Linux (ia64)
list(APPEND PC_FIELDS "uc_mcontext.uc_regs->gregs[PT_NIP]") # Linux (ppc)
list(APPEND PC_FIELDS "uc_mcontext.gregs[R15]"    ) # Linux (arm old [untested])
list(APPEND PC_FIELDS "uc_mcontext.arm_pc"          ) # Linux (arm arch 5)
list(APPEND PC_FIELDS "uc_mcontext.gp_regs[PT_NIP]" ) # Suse SLES 11 (ppc64)
list(APPEND PC_FIELDS "uc_mcontext.mc_eip"          ) # FreeBSD (i386)
list(APPEND PC_FIELDS "uc_mcontext.mc_rip"          ) # FreeBSD (x86_64 [untested])
list(APPEND PC_FIELDS "uc_mcontext.__gregs[_REG_EIP]" ) # NetBSD (i386)
list(APPEND PC_FIELDS "uc_mcontext.__gregs[_REG_RIP]" ) # NetBSD (x86_64)
list(APPEND PC_FIELDS "uc_mcontext->ss.eip"         ) # OS X (i386, <=10.4)
list(APPEND PC_FIELDS "uc_mcontext->__ss.__eip"     ) # OS X (i386, >=10.5)
list(APPEND PC_FIELDS "uc_mcontext->ss.rip"         ) # OS X (x86_64)
list(APPEND PC_FIELDS "uc_mcontext->__ss.__rip"     ) # OS X (>=10.5 [untested])
list(APPEND PC_FIELDS "uc_mcontext->ss.srr0"        ) # OS X (ppc, ppc64 [untested])
list(APPEND PC_FIELDS "uc_mcontext->__ss.__srr0"    ) # OS X (>=10.5 [untested])
set(PC_FIELD_FOUND FALSE)
set(PC_FIELD_CNT "0")
foreach(PC_FIELD ${PC_FIELDS})
    math(EXPR PC_FIELD_CNT "${PC_FIELD_CNT} + 1")
    if (NOT PC_FIELD_FOUND)
        check_cxx_source_compiles(" #include <sys/ucontext.h>
        int main () { ucontext_t u; return u.${PC_FIELD} == 0; ; return 0; }" PC_FIELD_${PC_FIELD_CNT}_OK)
        if (PC_FIELD_${PC_FIELD_CNT}_OK)
            set(PC_FROM_UCONTEXT ${PC_FIELD})
            set(PC_FIELD_FOUND TRUE)
        endif (PC_FIELD_${PC_FIELD_CNT}_OK)
    endif (NOT PC_FIELD_FOUND)
endforeach(PC_FIELD ${PC_FIELDS})
message("PC_FROM_UCONTEXT:${PC_FROM_UCONTEXT}")

set(PERFTOOLS_DLL_DECL "/**/")

set(FORMAT_PREFIXES "")
check_cxx_source_compiles("#include <stddef.h>
int main () { unsigned int v1 = 0; size_t v2 = 0; return (&v1 - &v2) ; return 0; }" IS_INT_EQUAL_SIZE_T)
check_cxx_source_compiles("#include <stddef.h>
int main () { unsigned long v1 = 0; size_t v2 = 0; return (&v1 - &v2) ; return 0; }" IS_LONG_EQUAL_SIZE_T)
check_cxx_source_compiles("#include <stddef.h>
int main () { unsigned long long v1 = 0; size_t v2 = 0; return (&v1 - &v2) ; return 0; }" IS_LONG_LONG_EQUAL_SIZE_T)
if (IS_INT_EQUAL_SIZE_T)
    set(PRIdS "d")
    set(PRIuS "u")
    set(PRIxS "x")
endif (IS_INT_EQUAL_SIZE_T)
if (IS_LONG_EQUAL_SIZE_T)
    set(PRIdS "ld")
    set(PRIuS "lu")
    set(PRIxS "lx")
endif (IS_LONG_EQUAL_SIZE_T)
if (IS_LONG_LONG_EQUAL_SIZE_T)
    set(PRIdS "lld")
    set(PRIuS "llu")
    set(PRIxS "llx")
endif (IS_LONG_LONG_EQUAL_SIZE_T)
#undef PRIdS

#undef PRIuS

#undef PRIxS

#ifdef __FreeBSD__
#define PTHREADS_CRASHES_IF_RUN_TOO_EARLY 1
#endif

#undef PTHREAD_CREATE_JOINABLE

check_cxx_source_runs("#include <ctype.h>
#include <stdlib.h>
#if ((' ' & 0x0FF) == 0x020)
# define ISLOWER(c) ('a' <= (c) && (c) <= 'z')
# define TOUPPER(c) (ISLOWER(c) ? 'A' + ((c) - 'a') : (c))
#else
# define ISLOWER(c)  (('a' <= (c) && (c) <= 'i')  || ('j' <= (c) && (c) <= 'r')  || ('s' <= (c) && (c) <= 'z'))
# define TOUPPER(c) (ISLOWER(c) ? ((c) | 0x40) : (c))
#endif
#define XOR(e, f) (((e) && !(f)) || (!(e) && (f)))
int main () { int i; for (i = 0; i < 256; i++) if (XOR (islower (i), ISLOWER (i))
|| toupper (i) != TOUPPER (i)) return 2; return 0; }" STDC_HEADERS)

check_cxx_source_compiles("#include <vector>
int main () { std::vector<int> t; return 0; ; return 0; }" STL_NAMESPACE)

set(VERSION "2.1")

#ifndef __STDC_FORMAT_MACROS
# define __STDC_FORMAT_MACROS 1
#endif


