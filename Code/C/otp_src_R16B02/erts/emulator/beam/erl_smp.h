/*
 * %CopyrightBegin%
 *
 * Copyright Ericsson AB 2005-2013. All Rights Reserved.
 *
 * The contents of this file are subject to the Erlang Public License,
 * Version 1.1, (the "License"); you may not use this file except in
 * compliance with the License. You should have received a copy of the
 * Erlang Public License along with this software. If not, it can be
 * retrieved online at http://www.erlang.org/.
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * %CopyrightEnd%
 */
/*
 * SMP interface to ethread library.
 * This is essentially "sed s/erts_/erts_smp_/g < erl_threads.h > erl_smp.h",
 * plus changes to NOP operations when ERTS_SMP is disabled.
 * Author: Mikael Pettersson
 */
#ifndef ERL_SMP_H
#define ERL_SMP_H
#include "erl_threads.h"

#ifdef ERTS_ENABLE_LOCK_COUNT
#define erts_smp_mtx_lock(L) erts_smp_mtx_lock_x(L, __FILE__, __LINE__)
#define erts_smp_spin_lock(L) erts_smp_spin_lock_x(L, __FILE__, __LINE__)
#define erts_smp_rwmtx_rlock(L) erts_smp_rwmtx_rlock_x(L, __FILE__, __LINE__)
#define erts_smp_rwmtx_rwlock(L) erts_smp_rwmtx_rwlock_x(L, __FILE__, __LINE__)
#define erts_smp_read_lock(L) erts_smp_read_lock_x(L, __FILE__, __LINE__)
#define erts_smp_write_lock(L) erts_smp_write_lock_x(L, __FILE__, __LINE__)
#endif


#ifdef ERTS_SMP
#define ERTS_SMP_THR_OPTS_DEFAULT_INITER ERTS_THR_OPTS_DEFAULT_INITER
typedef erts_thr_opts_t erts_smp_thr_opts_t;
typedef erts_thr_init_data_t erts_smp_thr_init_data_t;
typedef erts_tid_t erts_smp_tid_t;
typedef erts_mtx_t erts_smp_mtx_t;
typedef erts_cnd_t erts_smp_cnd_t;
#define ERTS_SMP_RWMTX_OPT_DEFAULT_INITER ERTS_RWMTX_OPT_DEFAULT_INITER
#define ERTS_SMP_RWMTX_TYPE_NORMAL ERTS_RWMTX_TYPE_NORMAL
#define ERTS_SMP_RWMTX_TYPE_FREQUENT_READ ERTS_RWMTX_TYPE_FREQUENT_READ
#define ERTS_SMP_RWMTX_TYPE_EXTREMELY_FREQUENT_READ \
  ERTS_RWMTX_TYPE_EXTREMELY_FREQUENT_READ
#define ERTS_SMP_RWMTX_LONG_LIVED ERTS_RWMTX_LONG_LIVED
#define ERTS_SMP_RWMTX_SHORT_LIVED ERTS_RWMTX_SHORT_LIVED
#define ERTS_SMP_RWMTX_UNKNOWN_LIVED ERTS_RWMTX_UNKNOWN_LIVED
typedef erts_rwmtx_opt_t erts_smp_rwmtx_opt_t;
typedef erts_rwmtx_t erts_smp_rwmtx_t;
typedef erts_tsd_key_t erts_smp_tsd_key_t;
#define erts_smp_dw_atomic_t erts_dw_atomic_t
#define erts_smp_atomic_t erts_atomic_t
#define erts_smp_atomic32_t erts_atomic32_t
typedef erts_spinlock_t erts_smp_spinlock_t;
typedef erts_rwlock_t erts_smp_rwlock_t;
void erts_thr_fatal_error(int, char *); /* implemented in erl_init.c */

#define ERTS_SMP_MEMORY_BARRIER ERTS_THR_MEMORY_BARRIER
#define ERTS_SMP_WRITE_MEMORY_BARRIER ERTS_THR_WRITE_MEMORY_BARRIER
#define ERTS_SMP_READ_MEMORY_BARRIER ERTS_THR_READ_MEMORY_BARRIER
#define ERTS_SMP_DATA_DEPENDENCY_READ_MEMORY_BARRIER ERTS_THR_DATA_DEPENDENCY_READ_MEMORY_BARRIER

#else /* #ifdef ERTS_SMP */

#define ERTS_SMP_THR_OPTS_DEFAULT_INITER {0}
typedef int erts_smp_thr_opts_t;
typedef int erts_smp_thr_init_data_t;
typedef int erts_smp_tid_t;
typedef int erts_smp_mtx_t;
typedef int erts_smp_cnd_t;
#define ERTS_SMP_RWMTX_OPT_DEFAULT_INITER {0}
#define ERTS_SMP_RWMTX_TYPE_NORMAL 0
#define ERTS_SMP_RWMTX_TYPE_FREQUENT_READ 0
#define ERTS_SMP_RWMTX_TYPE_EXTREMELY_FREQUENT_READ 0
#define ERTS_SMP_RWMTX_LONG_LIVED 0
#define ERTS_SMP_RWMTX_SHORT_LIVED 0
#define ERTS_SMP_RWMTX_UNKNOWN_LIVED 0
typedef struct {
    char type;
    char lived;
    int main_spincount;
    int aux_spincount;
} erts_smp_rwmtx_opt_t;
typedef int erts_smp_rwmtx_t;
typedef int erts_smp_tsd_key_t;
#define erts_smp_dw_atomic_t erts_no_dw_atomic_t
#define erts_smp_atomic_t erts_no_atomic_t
#define erts_smp_atomic32_t erts_no_atomic32_t
#if __GNUC__ > 2
typedef struct { } erts_smp_spinlock_t;
typedef struct { } erts_smp_rwlock_t;
#else
typedef struct { int gcc_is_buggy; } erts_smp_spinlock_t;
typedef struct { int gcc_is_buggy; } erts_smp_rwlock_t;
#endif

#define ERTS_SMP_MEMORY_BARRIER
#define ERTS_SMP_WRITE_MEMORY_BARRIER
#define ERTS_SMP_READ_MEMORY_BARRIER
#define ERTS_SMP_DATA_DEPENDENCY_READ_MEMORY_BARRIER

#endif /* #ifdef ERTS_SMP */

ERTS_GLB_INLINE void erts_smp_thr_init(erts_smp_thr_init_data_t *id);
ERTS_GLB_INLINE void erts_smp_thr_create(erts_smp_tid_t *tid,
					 void * (*func)(void *),
					 void *arg,
					 erts_smp_thr_opts_t *opts);
ERTS_GLB_INLINE void erts_smp_thr_join(erts_smp_tid_t tid, void **thr_res);
ERTS_GLB_INLINE void erts_smp_thr_detach(erts_smp_tid_t tid);
ERTS_GLB_INLINE void erts_smp_thr_exit(void *res);
ERTS_GLB_INLINE void erts_smp_install_exit_handler(void (*exit_handler)(void));
ERTS_GLB_INLINE erts_smp_tid_t erts_smp_thr_self(void);
ERTS_GLB_INLINE int erts_smp_equal_tids(erts_smp_tid_t x, erts_smp_tid_t y);
#ifdef ERTS_HAVE_REC_MTX_INIT
#define ERTS_SMP_HAVE_REC_MTX_INIT 1
ERTS_GLB_INLINE void erts_smp_rec_mtx_init(erts_smp_mtx_t *mtx);
#endif
ERTS_GLB_INLINE void erts_smp_mtx_init_x(erts_smp_mtx_t *mtx,
					 char *name,
					 Eterm extra);
ERTS_GLB_INLINE void erts_smp_mtx_init_locked_x(erts_smp_mtx_t *mtx,
						char *name,
						Eterm extra);
ERTS_GLB_INLINE void erts_smp_mtx_init(erts_smp_mtx_t *mtx, char *name);
ERTS_GLB_INLINE void erts_smp_mtx_init_locked(erts_smp_mtx_t *mtx, char *name);
ERTS_GLB_INLINE void erts_smp_mtx_destroy(erts_smp_mtx_t *mtx);
ERTS_GLB_INLINE int erts_smp_mtx_trylock(erts_smp_mtx_t *mtx);
#ifdef ERTS_ENABLE_LOCK_COUNT
ERTS_GLB_INLINE void erts_smp_mtx_lock_x(erts_smp_mtx_t *mtx, char *file, int line);
#else
ERTS_GLB_INLINE void erts_smp_mtx_lock(erts_smp_mtx_t *mtx);
#endif
ERTS_GLB_INLINE void erts_smp_mtx_unlock(erts_smp_mtx_t *mtx);
ERTS_GLB_INLINE int erts_smp_lc_mtx_is_locked(erts_smp_mtx_t *mtx);
ERTS_GLB_INLINE void erts_smp_cnd_init(erts_smp_cnd_t *cnd);
ERTS_GLB_INLINE void erts_smp_cnd_destroy(erts_smp_cnd_t *cnd);
ERTS_GLB_INLINE void erts_smp_cnd_wait(erts_smp_cnd_t *cnd,
					   erts_smp_mtx_t *mtx);
ERTS_GLB_INLINE void erts_smp_cnd_signal(erts_smp_cnd_t *cnd);
ERTS_GLB_INLINE void erts_smp_cnd_broadcast(erts_smp_cnd_t *cnd);
ERTS_GLB_INLINE void erts_smp_rwmtx_set_reader_group(int no);
ERTS_GLB_INLINE void erts_smp_rwmtx_init_opt_x(erts_smp_rwmtx_t *rwmtx,
					       erts_smp_rwmtx_opt_t *opt,
					       char *name,
					       Eterm extra);
ERTS_GLB_INLINE void erts_smp_rwmtx_init_x(erts_smp_rwmtx_t *rwmtx,
					   char *name,
					   Eterm extra);
ERTS_GLB_INLINE void erts_smp_rwmtx_init_opt(erts_smp_rwmtx_t *rwmtx,
					     erts_smp_rwmtx_opt_t *opt,
					     char *name);
ERTS_GLB_INLINE void erts_smp_rwmtx_init(erts_smp_rwmtx_t *rwmtx,
					 char *name);
ERTS_GLB_INLINE void erts_smp_rwmtx_destroy(erts_smp_rwmtx_t *rwmtx);
ERTS_GLB_INLINE int erts_smp_rwmtx_tryrlock(erts_smp_rwmtx_t *rwmtx);
#ifdef ERTS_ENABLE_LOCK_COUNT
ERTS_GLB_INLINE void erts_smp_rwmtx_rlock_x(erts_smp_rwmtx_t *rwmtx, char *file, unsigned int line);
ERTS_GLB_INLINE void erts_smp_rwmtx_rwlock_x(erts_smp_rwmtx_t *rwmtx, char *file, unsigned int line);
#else
ERTS_GLB_INLINE void erts_smp_rwmtx_rlock(erts_smp_rwmtx_t *rwmtx);
ERTS_GLB_INLINE void erts_smp_rwmtx_rwlock(erts_smp_rwmtx_t *rwmtx);
#endif
ERTS_GLB_INLINE void erts_smp_rwmtx_runlock(erts_smp_rwmtx_t *rwmtx);
ERTS_GLB_INLINE int erts_smp_rwmtx_tryrwlock(erts_smp_rwmtx_t *rwmtx);
ERTS_GLB_INLINE void erts_smp_rwmtx_rwunlock(erts_smp_rwmtx_t *rwmtx);
ERTS_GLB_INLINE int erts_smp_lc_rwmtx_is_rlocked(erts_smp_rwmtx_t *mtx);
ERTS_GLB_INLINE int erts_smp_lc_rwmtx_is_rwlocked(erts_smp_rwmtx_t *mtx);
ERTS_GLB_INLINE void erts_smp_spinlock_init_x(erts_smp_spinlock_t *lock,
					      char *name,
					      Eterm extra);
ERTS_GLB_INLINE void erts_smp_spinlock_init(erts_smp_spinlock_t *lock,
					    char *name);
ERTS_GLB_INLINE void erts_smp_spinlock_destroy(erts_smp_spinlock_t *lock);
ERTS_GLB_INLINE void erts_smp_spin_unlock(erts_smp_spinlock_t *lock);
#ifdef ERTS_ENABLE_LOCK_COUNT
ERTS_GLB_INLINE void erts_smp_spin_lock_x(erts_smp_spinlock_t *lock, char *file, unsigned int line);
#else
ERTS_GLB_INLINE void erts_smp_spin_lock(erts_smp_spinlock_t *lock);
#endif
ERTS_GLB_INLINE int erts_smp_lc_spinlock_is_locked(erts_smp_spinlock_t *lock);
ERTS_GLB_INLINE void erts_smp_rwlock_init_x(erts_smp_rwlock_t *lock,
					    char *name,
					    Eterm extra);
ERTS_GLB_INLINE void erts_smp_rwlock_init(erts_smp_rwlock_t *lock,
					  char *name);
ERTS_GLB_INLINE void erts_smp_rwlock_destroy(erts_smp_rwlock_t *lock);
ERTS_GLB_INLINE void erts_smp_read_unlock(erts_smp_rwlock_t *lock);
#ifdef ERTS_ENABLE_LOCK_COUNT
ERTS_GLB_INLINE void erts_smp_read_lock_x(erts_smp_rwlock_t *lock, char *file, unsigned int line);
ERTS_GLB_INLINE void erts_smp_write_lock_x(erts_smp_rwlock_t *lock, char *file, unsigned int line);
#else
ERTS_GLB_INLINE void erts_smp_read_lock(erts_smp_rwlock_t *lock);
ERTS_GLB_INLINE void erts_smp_write_lock(erts_smp_rwlock_t *lock);
#endif
ERTS_GLB_INLINE void erts_smp_write_unlock(erts_smp_rwlock_t *lock);
ERTS_GLB_INLINE int erts_smp_lc_rwlock_is_rlocked(erts_smp_rwlock_t *lock);
ERTS_GLB_INLINE int erts_smp_lc_rwlock_is_rwlocked(erts_smp_rwlock_t *lock);
ERTS_GLB_INLINE void erts_smp_tsd_key_create(erts_smp_tsd_key_t *keyp);
ERTS_GLB_INLINE void erts_smp_tsd_key_delete(erts_smp_tsd_key_t key);
ERTS_GLB_INLINE void erts_smp_tsd_set(erts_smp_tsd_key_t key, void *value);
ERTS_GLB_INLINE void * erts_smp_tsd_get(erts_smp_tsd_key_t key);

#ifdef ERTS_THR_HAVE_SIG_FUNCS
#define ERTS_SMP_THR_HAVE_SIG_FUNCS 1
ERTS_GLB_INLINE void erts_smp_thr_sigmask(int how,
					  const sigset_t *set,
					  sigset_t *oset);
ERTS_GLB_INLINE void erts_smp_thr_sigwait(const sigset_t *set, int *sig);
#endif /* #ifdef ERTS_THR_HAVE_SIG_FUNCS */

/*
 * See "Documentation of atomics and memory barriers" at the top
 * of erl_threads.h for info on atomics.
 */

#ifdef ERTS_SMP

/* Double word size atomics */

#define erts_smp_dw_atomic_init_nob erts_dw_atomic_init_nob
#define erts_smp_dw_atomic_set_nob erts_dw_atomic_set_nob
#define erts_smp_dw_atomic_read_nob erts_dw_atomic_read_nob
#define erts_smp_dw_atomic_cmpxchg_nob erts_dw_atomic_cmpxchg_nob

#define erts_smp_dw_atomic_init_mb erts_dw_atomic_init_mb
#define erts_smp_dw_atomic_set_mb erts_dw_atomic_set_mb
#define erts_smp_dw_atomic_read_mb erts_dw_atomic_read_mb
#define erts_smp_dw_atomic_cmpxchg_mb erts_dw_atomic_cmpxchg_mb

#define erts_smp_dw_atomic_init_acqb erts_dw_atomic_init_acqb
#define erts_smp_dw_atomic_set_acqb erts_dw_atomic_set_acqb
#define erts_smp_dw_atomic_read_acqb erts_dw_atomic_read_acqb
#define erts_smp_dw_atomic_cmpxchg_acqb erts_dw_atomic_cmpxchg_acqb

#define erts_smp_dw_atomic_init_relb erts_dw_atomic_init_relb
#define erts_smp_dw_atomic_set_relb erts_dw_atomic_set_relb
#define erts_smp_dw_atomic_read_relb erts_dw_atomic_read_relb
#define erts_smp_dw_atomic_cmpxchg_relb erts_dw_atomic_cmpxchg_relb

#define erts_smp_dw_atomic_init_ddrb erts_dw_atomic_init_ddrb
#define erts_smp_dw_atomic_set_ddrb erts_dw_atomic_set_ddrb
#define erts_smp_dw_atomic_read_ddrb erts_dw_atomic_read_ddrb
#define erts_smp_dw_atomic_cmpxchg_ddrb erts_dw_atomic_cmpxchg_ddrb

#define erts_smp_dw_atomic_init_rb erts_dw_atomic_init_rb
#define erts_smp_dw_atomic_set_rb erts_dw_atomic_set_rb
#define erts_smp_dw_atomic_read_rb erts_dw_atomic_read_rb
#define erts_smp_dw_atomic_cmpxchg_rb erts_dw_atomic_cmpxchg_rb

#define erts_smp_dw_atomic_init_wb erts_dw_atomic_init_wb
#define erts_smp_dw_atomic_set_wb erts_dw_atomic_set_wb
#define erts_smp_dw_atomic_read_wb erts_dw_atomic_read_wb
#define erts_smp_dw_atomic_cmpxchg_wb erts_dw_atomic_cmpxchg_wb

#define erts_smp_dw_atomic_set_dirty erts_dw_atomic_set_dirty
#define erts_smp_dw_atomic_read_dirty erts_dw_atomic_read_dirty

/* Word size atomics */

#define erts_smp_atomic_init_nob erts_atomic_init_nob
#define erts_smp_atomic_set_nob erts_atomic_set_nob
#define erts_smp_atomic_read_nob erts_atomic_read_nob
#define erts_smp_atomic_inc_read_nob erts_atomic_inc_read_nob
#define erts_smp_atomic_dec_read_nob erts_atomic_dec_read_nob
#define erts_smp_atomic_inc_nob erts_atomic_inc_nob
#define erts_smp_atomic_dec_nob erts_atomic_dec_nob
#define erts_smp_atomic_add_read_nob erts_atomic_add_read_nob
#define erts_smp_atomic_add_nob erts_atomic_add_nob
#define erts_smp_atomic_read_bor_nob erts_atomic_read_bor_nob
#define erts_smp_atomic_read_band_nob erts_atomic_read_band_nob
#define erts_smp_atomic_xchg_nob erts_atomic_xchg_nob
#define erts_smp_atomic_cmpxchg_nob erts_atomic_cmpxchg_nob
#define erts_smp_atomic_read_bset_nob erts_atomic_read_bset_nob

#define erts_smp_atomic_init_mb erts_atomic_init_mb
#define erts_smp_atomic_set_mb erts_atomic_set_mb
#define erts_smp_atomic_read_mb erts_atomic_read_mb
#define erts_smp_atomic_inc_read_mb erts_atomic_inc_read_mb
#define erts_smp_atomic_dec_read_mb erts_atomic_dec_read_mb
#define erts_smp_atomic_inc_mb erts_atomic_inc_mb
#define erts_smp_atomic_dec_mb erts_atomic_dec_mb
#define erts_smp_atomic_add_read_mb erts_atomic_add_read_mb
#define erts_smp_atomic_add_mb erts_atomic_add_mb
#define erts_smp_atomic_read_bor_mb erts_atomic_read_bor_mb
#define erts_smp_atomic_read_band_mb erts_atomic_read_band_mb
#define erts_smp_atomic_xchg_mb erts_atomic_xchg_mb
#define erts_smp_atomic_cmpxchg_mb erts_atomic_cmpxchg_mb
#define erts_smp_atomic_read_bset_mb erts_atomic_read_bset_mb

#define erts_smp_atomic_init_acqb erts_atomic_init_acqb
#define erts_smp_atomic_set_acqb erts_atomic_set_acqb
#define erts_smp_atomic_read_acqb erts_atomic_read_acqb
#define erts_smp_atomic_inc_read_acqb erts_atomic_inc_read_acqb
#define erts_smp_atomic_dec_read_acqb erts_atomic_dec_read_acqb
#define erts_smp_atomic_inc_acqb erts_atomic_inc_acqb
#define erts_smp_atomic_dec_acqb erts_atomic_dec_acqb
#define erts_smp_atomic_add_read_acqb erts_atomic_add_read_acqb
#define erts_smp_atomic_add_acqb erts_atomic_add_acqb
#define erts_smp_atomic_read_bor_acqb erts_atomic_read_bor_acqb
#define erts_smp_atomic_read_band_acqb erts_atomic_read_band_acqb
#define erts_smp_atomic_xchg_acqb erts_atomic_xchg_acqb
#define erts_smp_atomic_cmpxchg_acqb erts_atomic_cmpxchg_acqb
#define erts_smp_atomic_read_bset_acqb erts_atomic_read_bset_acqb

#define erts_smp_atomic_init_relb erts_atomic_init_relb
#define erts_smp_atomic_set_relb erts_atomic_set_relb
#define erts_smp_atomic_read_relb erts_atomic_read_relb
#define erts_smp_atomic_inc_read_relb erts_atomic_inc_read_relb
#define erts_smp_atomic_dec_read_relb erts_atomic_dec_read_relb
#define erts_smp_atomic_inc_relb erts_atomic_inc_relb
#define erts_smp_atomic_dec_relb erts_atomic_dec_relb
#define erts_smp_atomic_add_read_relb erts_atomic_add_read_relb
#define erts_smp_atomic_add_relb erts_atomic_add_relb
#define erts_smp_atomic_read_bor_relb erts_atomic_read_bor_relb
#define erts_smp_atomic_read_band_relb erts_atomic_read_band_relb
#define erts_smp_atomic_xchg_relb erts_atomic_xchg_relb
#define erts_smp_atomic_cmpxchg_relb erts_atomic_cmpxchg_relb
#define erts_smp_atomic_read_bset_relb erts_atomic_read_bset_relb

#define erts_smp_atomic_init_ddrb erts_atomic_init_ddrb
#define erts_smp_atomic_set_ddrb erts_atomic_set_ddrb
#define erts_smp_atomic_read_ddrb erts_atomic_read_ddrb
#define erts_smp_atomic_inc_read_ddrb erts_atomic_inc_read_ddrb
#define erts_smp_atomic_dec_read_ddrb erts_atomic_dec_read_ddrb
#define erts_smp_atomic_inc_ddrb erts_atomic_inc_ddrb
#define erts_smp_atomic_dec_ddrb erts_atomic_dec_ddrb
#define erts_smp_atomic_add_read_ddrb erts_atomic_add_read_ddrb
#define erts_smp_atomic_add_ddrb erts_atomic_add_ddrb
#define erts_smp_atomic_read_bor_ddrb erts_atomic_read_bor_ddrb
#define erts_smp_atomic_read_band_ddrb erts_atomic_read_band_ddrb
#define erts_smp_atomic_xchg_ddrb erts_atomic_xchg_ddrb
#define erts_smp_atomic_cmpxchg_ddrb erts_atomic_cmpxchg_ddrb
#define erts_smp_atomic_read_bset_ddrb erts_atomic_read_bset_ddrb

#define erts_smp_atomic_init_rb erts_atomic_init_rb
#define erts_smp_atomic_set_rb erts_atomic_set_rb
#define erts_smp_atomic_read_rb erts_atomic_read_rb
#define erts_smp_atomic_inc_read_rb erts_atomic_inc_read_rb
#define erts_smp_atomic_dec_read_rb erts_atomic_dec_read_rb
#define erts_smp_atomic_inc_rb erts_atomic_inc_rb
#define erts_smp_atomic_dec_rb erts_atomic_dec_rb
#define erts_smp_atomic_add_read_rb erts_atomic_add_read_rb
#define erts_smp_atomic_add_rb erts_atomic_add_rb
#define erts_smp_atomic_read_bor_rb erts_atomic_read_bor_rb
#define erts_smp_atomic_read_band_rb erts_atomic_read_band_rb
#define erts_smp_atomic_xchg_rb erts_atomic_xchg_rb
#define erts_smp_atomic_cmpxchg_rb erts_atomic_cmpxchg_rb
#define erts_smp_atomic_read_bset_rb erts_atomic_read_bset_rb

#define erts_smp_atomic_init_wb erts_atomic_init_wb
#define erts_smp_atomic_set_wb erts_atomic_set_wb
#define erts_smp_atomic_read_wb erts_atomic_read_wb
#define erts_smp_atomic_inc_read_wb erts_atomic_inc_read_wb
#define erts_smp_atomic_dec_read_wb erts_atomic_dec_read_wb
#define erts_smp_atomic_inc_wb erts_atomic_inc_wb
#define erts_smp_atomic_dec_wb erts_atomic_dec_wb
#define erts_smp_atomic_add_read_wb erts_atomic_add_read_wb
#define erts_smp_atomic_add_wb erts_atomic_add_wb
#define erts_smp_atomic_read_bor_wb erts_atomic_read_bor_wb
#define erts_smp_atomic_read_band_wb erts_atomic_read_band_wb
#define erts_smp_atomic_xchg_wb erts_atomic_xchg_wb
#define erts_smp_atomic_cmpxchg_wb erts_atomic_cmpxchg_wb
#define erts_smp_atomic_read_bset_wb erts_atomic_read_bset_wb

#define erts_smp_atomic_set_dirty erts_atomic_set_dirty
#define erts_smp_atomic_read_dirty erts_atomic_read_dirty

/* 32-bit atomics */

#define erts_smp_atomic32_init_nob erts_atomic32_init_nob
#define erts_smp_atomic32_set_nob erts_atomic32_set_nob
#define erts_smp_atomic32_read_nob erts_atomic32_read_nob
#define erts_smp_atomic32_inc_read_nob erts_atomic32_inc_read_nob
#define erts_smp_atomic32_dec_read_nob erts_atomic32_dec_read_nob
#define erts_smp_atomic32_inc_nob erts_atomic32_inc_nob
#define erts_smp_atomic32_dec_nob erts_atomic32_dec_nob
#define erts_smp_atomic32_add_read_nob erts_atomic32_add_read_nob
#define erts_smp_atomic32_add_nob erts_atomic32_add_nob
#define erts_smp_atomic32_read_bor_nob erts_atomic32_read_bor_nob
#define erts_smp_atomic32_read_band_nob erts_atomic32_read_band_nob
#define erts_smp_atomic32_xchg_nob erts_atomic32_xchg_nob
#define erts_smp_atomic32_cmpxchg_nob erts_atomic32_cmpxchg_nob
#define erts_smp_atomic32_read_bset_nob erts_atomic32_read_bset_nob

#define erts_smp_atomic32_init_mb erts_atomic32_init_mb
#define erts_smp_atomic32_set_mb erts_atomic32_set_mb
#define erts_smp_atomic32_read_mb erts_atomic32_read_mb
#define erts_smp_atomic32_inc_read_mb erts_atomic32_inc_read_mb
#define erts_smp_atomic32_dec_read_mb erts_atomic32_dec_read_mb
#define erts_smp_atomic32_inc_mb erts_atomic32_inc_mb
#define erts_smp_atomic32_dec_mb erts_atomic32_dec_mb
#define erts_smp_atomic32_add_read_mb erts_atomic32_add_read_mb
#define erts_smp_atomic32_add_mb erts_atomic32_add_mb
#define erts_smp_atomic32_read_bor_mb erts_atomic32_read_bor_mb
#define erts_smp_atomic32_read_band_mb erts_atomic32_read_band_mb
#define erts_smp_atomic32_xchg_mb erts_atomic32_xchg_mb
#define erts_smp_atomic32_cmpxchg_mb erts_atomic32_cmpxchg_mb
#define erts_smp_atomic32_read_bset_mb erts_atomic32_read_bset_mb

#define erts_smp_atomic32_init_acqb erts_atomic32_init_acqb
#define erts_smp_atomic32_set_acqb erts_atomic32_set_acqb
#define erts_smp_atomic32_read_acqb erts_atomic32_read_acqb
#define erts_smp_atomic32_inc_read_acqb erts_atomic32_inc_read_acqb
#define erts_smp_atomic32_dec_read_acqb erts_atomic32_dec_read_acqb
#define erts_smp_atomic32_inc_acqb erts_atomic32_inc_acqb
#define erts_smp_atomic32_dec_acqb erts_atomic32_dec_acqb
#define erts_smp_atomic32_add_read_acqb erts_atomic32_add_read_acqb
#define erts_smp_atomic32_add_acqb erts_atomic32_add_acqb
#define erts_smp_atomic32_read_bor_acqb erts_atomic32_read_bor_acqb
#define erts_smp_atomic32_read_band_acqb erts_atomic32_read_band_acqb
#define erts_smp_atomic32_xchg_acqb erts_atomic32_xchg_acqb
#define erts_smp_atomic32_cmpxchg_acqb erts_atomic32_cmpxchg_acqb
#define erts_smp_atomic32_read_bset_acqb erts_atomic32_read_bset_acqb

#define erts_smp_atomic32_init_relb erts_atomic32_init_relb
#define erts_smp_atomic32_set_relb erts_atomic32_set_relb
#define erts_smp_atomic32_read_relb erts_atomic32_read_relb
#define erts_smp_atomic32_inc_read_relb erts_atomic32_inc_read_relb
#define erts_smp_atomic32_dec_read_relb erts_atomic32_dec_read_relb
#define erts_smp_atomic32_inc_relb erts_atomic32_inc_relb
#define erts_smp_atomic32_dec_relb erts_atomic32_dec_relb
#define erts_smp_atomic32_add_read_relb erts_atomic32_add_read_relb
#define erts_smp_atomic32_add_relb erts_atomic32_add_relb
#define erts_smp_atomic32_read_bor_relb erts_atomic32_read_bor_relb
#define erts_smp_atomic32_read_band_relb erts_atomic32_read_band_relb
#define erts_smp_atomic32_xchg_relb erts_atomic32_xchg_relb
#define erts_smp_atomic32_cmpxchg_relb erts_atomic32_cmpxchg_relb
#define erts_smp_atomic32_read_bset_relb erts_atomic32_read_bset_relb

#define erts_smp_atomic32_init_ddrb erts_atomic32_init_ddrb
#define erts_smp_atomic32_set_ddrb erts_atomic32_set_ddrb
#define erts_smp_atomic32_read_ddrb erts_atomic32_read_ddrb
#define erts_smp_atomic32_inc_read_ddrb erts_atomic32_inc_read_ddrb
#define erts_smp_atomic32_dec_read_ddrb erts_atomic32_dec_read_ddrb
#define erts_smp_atomic32_inc_ddrb erts_atomic32_inc_ddrb
#define erts_smp_atomic32_dec_ddrb erts_atomic32_dec_ddrb
#define erts_smp_atomic32_add_read_ddrb erts_atomic32_add_read_ddrb
#define erts_smp_atomic32_add_ddrb erts_atomic32_add_ddrb
#define erts_smp_atomic32_read_bor_ddrb erts_atomic32_read_bor_ddrb
#define erts_smp_atomic32_read_band_ddrb erts_atomic32_read_band_ddrb
#define erts_smp_atomic32_xchg_ddrb erts_atomic32_xchg_ddrb
#define erts_smp_atomic32_cmpxchg_ddrb erts_atomic32_cmpxchg_ddrb
#define erts_smp_atomic32_read_bset_ddrb erts_atomic32_read_bset_ddrb

#define erts_smp_atomic32_init_rb erts_atomic32_init_rb
#define erts_smp_atomic32_set_rb erts_atomic32_set_rb
#define erts_smp_atomic32_read_rb erts_atomic32_read_rb
#define erts_smp_atomic32_inc_read_rb erts_atomic32_inc_read_rb
#define erts_smp_atomic32_dec_read_rb erts_atomic32_dec_read_rb
#define erts_smp_atomic32_inc_rb erts_atomic32_inc_rb
#define erts_smp_atomic32_dec_rb erts_atomic32_dec_rb
#define erts_smp_atomic32_add_read_rb erts_atomic32_add_read_rb
#define erts_smp_atomic32_add_rb erts_atomic32_add_rb
#define erts_smp_atomic32_read_bor_rb erts_atomic32_read_bor_rb
#define erts_smp_atomic32_read_band_rb erts_atomic32_read_band_rb
#define erts_smp_atomic32_xchg_rb erts_atomic32_xchg_rb
#define erts_smp_atomic32_cmpxchg_rb erts_atomic32_cmpxchg_rb
#define erts_smp_atomic32_read_bset_rb erts_atomic32_read_bset_rb

#define erts_smp_atomic32_init_wb erts_atomic32_init_wb
#define erts_smp_atomic32_set_wb erts_atomic32_set_wb
#define erts_smp_atomic32_read_wb erts_atomic32_read_wb
#define erts_smp_atomic32_inc_read_wb erts_atomic32_inc_read_wb
#define erts_smp_atomic32_dec_read_wb erts_atomic32_dec_read_wb
#define erts_smp_atomic32_inc_wb erts_atomic32_inc_wb
#define erts_smp_atomic32_dec_wb erts_atomic32_dec_wb
#define erts_smp_atomic32_add_read_wb erts_atomic32_add_read_wb
#define erts_smp_atomic32_add_wb erts_atomic32_add_wb
#define erts_smp_atomic32_read_bor_wb erts_atomic32_read_bor_wb
#define erts_smp_atomic32_read_band_wb erts_atomic32_read_band_wb
#define erts_smp_atomic32_xchg_wb erts_atomic32_xchg_wb
#define erts_smp_atomic32_cmpxchg_wb erts_atomic32_cmpxchg_wb
#define erts_smp_atomic32_read_bset_wb erts_atomic32_read_bset_wb

#define erts_smp_atomic32_set_dirty erts_atomic32_set_dirty
#define erts_smp_atomic32_read_dirty erts_atomic32_read_dirty

#else /* !ERTS_SMP */

/* Double word size atomics */

#define erts_smp_dw_atomic_init_nob erts_no_dw_atomic_set
#define erts_smp_dw_atomic_set_nob erts_no_dw_atomic_set
#define erts_smp_dw_atomic_read_nob erts_no_dw_atomic_read
#define erts_smp_dw_atomic_cmpxchg_nob erts_no_dw_atomic_cmpxchg

#define erts_smp_dw_atomic_init_mb erts_no_dw_atomic_init
#define erts_smp_dw_atomic_set_mb erts_no_dw_atomic_set
#define erts_smp_dw_atomic_read_mb erts_no_dw_atomic_read
#define erts_smp_dw_atomic_cmpxchg_mb erts_no_dw_atomic_cmpxchg

#define erts_smp_dw_atomic_init_acqb erts_no_dw_atomic_init
#define erts_smp_dw_atomic_set_acqb erts_no_dw_atomic_set
#define erts_smp_dw_atomic_read_acqb erts_no_dw_atomic_read
#define erts_smp_dw_atomic_cmpxchg_acqb erts_no_dw_atomic_cmpxchg

#define erts_smp_dw_atomic_init_relb erts_no_dw_atomic_init
#define erts_smp_dw_atomic_set_relb erts_no_dw_atomic_set
#define erts_smp_dw_atomic_read_relb erts_no_dw_atomic_read
#define erts_smp_dw_atomic_cmpxchg_relb erts_no_dw_atomic_cmpxchg

#define erts_smp_dw_atomic_init_ddrb erts_no_dw_atomic_init
#define erts_smp_dw_atomic_set_ddrb erts_no_dw_atomic_set
#define erts_smp_dw_atomic_read_ddrb erts_no_dw_atomic_read
#define erts_smp_dw_atomic_cmpxchg_ddrb erts_no_dw_atomic_cmpxchg

#define erts_smp_dw_atomic_init_rb erts_no_dw_atomic_init
#define erts_smp_dw_atomic_set_rb erts_no_dw_atomic_set
#define erts_smp_dw_atomic_read_rb erts_no_dw_atomic_read
#define erts_smp_dw_atomic_cmpxchg_rb erts_no_dw_atomic_cmpxchg

#define erts_smp_dw_atomic_init_wb erts_no_dw_atomic_init
#define erts_smp_dw_atomic_set_wb erts_no_dw_atomic_set
#define erts_smp_dw_atomic_read_wb erts_no_dw_atomic_read
#define erts_smp_dw_atomic_cmpxchg_wb erts_no_dw_atomic_cmpxchg

#define erts_smp_dw_atomic_set_dirty erts_no_dw_atomic_set
#define erts_smp_dw_atomic_read_dirty erts_no_dw_atomic_read

/* Word size atomics */

#define erts_smp_atomic_init_nob erts_no_atomic_set
#define erts_smp_atomic_set_nob erts_no_atomic_set
#define erts_smp_atomic_read_nob erts_no_atomic_read
#define erts_smp_atomic_inc_read_nob erts_no_atomic_inc_read
#define erts_smp_atomic_dec_read_nob erts_no_atomic_dec_read
#define erts_smp_atomic_inc_nob erts_no_atomic_inc
#define erts_smp_atomic_dec_nob erts_no_atomic_dec
#define erts_smp_atomic_add_read_nob erts_no_atomic_add_read
#define erts_smp_atomic_add_nob erts_no_atomic_add
#define erts_smp_atomic_read_bor_nob erts_no_atomic_read_bor
#define erts_smp_atomic_read_band_nob erts_no_atomic_read_band
#define erts_smp_atomic_xchg_nob erts_no_atomic_xchg
#define erts_smp_atomic_cmpxchg_nob erts_no_atomic_cmpxchg
#define erts_smp_atomic_read_bset_nob erts_no_atomic_read_bset

#define erts_smp_atomic_init_mb erts_no_atomic_set
#define erts_smp_atomic_set_mb erts_no_atomic_set
#define erts_smp_atomic_read_mb erts_no_atomic_read
#define erts_smp_atomic_inc_read_mb erts_no_atomic_inc_read
#define erts_smp_atomic_dec_read_mb erts_no_atomic_dec_read
#define erts_smp_atomic_inc_mb erts_no_atomic_inc
#define erts_smp_atomic_dec_mb erts_no_atomic_dec
#define erts_smp_atomic_add_read_mb erts_no_atomic_add_read
#define erts_smp_atomic_add_mb erts_no_atomic_add
#define erts_smp_atomic_read_bor_mb erts_no_atomic_read_bor
#define erts_smp_atomic_read_band_mb erts_no_atomic_read_band
#define erts_smp_atomic_xchg_mb erts_no_atomic_xchg
#define erts_smp_atomic_cmpxchg_mb erts_no_atomic_cmpxchg
#define erts_smp_atomic_read_bset_mb erts_no_atomic_read_bset

#define erts_smp_atomic_init_acqb erts_no_atomic_set
#define erts_smp_atomic_set_acqb erts_no_atomic_set
#define erts_smp_atomic_read_acqb erts_no_atomic_read
#define erts_smp_atomic_inc_read_acqb erts_no_atomic_inc_read
#define erts_smp_atomic_dec_read_acqb erts_no_atomic_dec_read
#define erts_smp_atomic_inc_acqb erts_no_atomic_inc
#define erts_smp_atomic_dec_acqb erts_no_atomic_dec
#define erts_smp_atomic_add_read_acqb erts_no_atomic_add_read
#define erts_smp_atomic_add_acqb erts_no_atomic_add
#define erts_smp_atomic_read_bor_acqb erts_no_atomic_read_bor
#define erts_smp_atomic_read_band_acqb erts_no_atomic_read_band
#define erts_smp_atomic_xchg_acqb erts_no_atomic_xchg
#define erts_smp_atomic_cmpxchg_acqb erts_no_atomic_cmpxchg
#define erts_smp_atomic_read_bset_acqb erts_no_atomic_read_bset

#define erts_smp_atomic_init_relb erts_no_atomic_set
#define erts_smp_atomic_set_relb erts_no_atomic_set
#define erts_smp_atomic_read_relb erts_no_atomic_read
#define erts_smp_atomic_inc_read_relb erts_no_atomic_inc_read
#define erts_smp_atomic_dec_read_relb erts_no_atomic_dec_read
#define erts_smp_atomic_inc_relb erts_no_atomic_inc
#define erts_smp_atomic_dec_relb erts_no_atomic_dec
#define erts_smp_atomic_add_read_relb erts_no_atomic_add_read
#define erts_smp_atomic_add_relb erts_no_atomic_add
#define erts_smp_atomic_read_bor_relb erts_no_atomic_read_bor
#define erts_smp_atomic_read_band_relb erts_no_atomic_read_band
#define erts_smp_atomic_xchg_relb erts_no_atomic_xchg
#define erts_smp_atomic_cmpxchg_relb erts_no_atomic_cmpxchg
#define erts_smp_atomic_read_bset_relb erts_no_atomic_read_bset

#define erts_smp_atomic_init_ddrb erts_no_atomic_set
#define erts_smp_atomic_set_ddrb erts_no_atomic_set
#define erts_smp_atomic_read_ddrb erts_no_atomic_read
#define erts_smp_atomic_inc_read_ddrb erts_no_atomic_inc_read
#define erts_smp_atomic_dec_read_ddrb erts_no_atomic_dec_read
#define erts_smp_atomic_inc_ddrb erts_no_atomic_inc
#define erts_smp_atomic_dec_ddrb erts_no_atomic_dec
#define erts_smp_atomic_add_read_ddrb erts_no_atomic_add_read
#define erts_smp_atomic_add_ddrb erts_no_atomic_add
#define erts_smp_atomic_read_bor_ddrb erts_no_atomic_read_bor
#define erts_smp_atomic_read_band_ddrb erts_no_atomic_read_band
#define erts_smp_atomic_xchg_ddrb erts_no_atomic_xchg
#define erts_smp_atomic_cmpxchg_ddrb erts_no_atomic_cmpxchg
#define erts_smp_atomic_read_bset_ddrb erts_no_atomic_read_bset

#define erts_smp_atomic_init_rb erts_no_atomic_set
#define erts_smp_atomic_set_rb erts_no_atomic_set
#define erts_smp_atomic_read_rb erts_no_atomic_read
#define erts_smp_atomic_inc_read_rb erts_no_atomic_inc_read
#define erts_smp_atomic_dec_read_rb erts_no_atomic_dec_read
#define erts_smp_atomic_inc_rb erts_no_atomic_inc
#define erts_smp_atomic_dec_rb erts_no_atomic_dec
#define erts_smp_atomic_add_read_rb erts_no_atomic_add_read
#define erts_smp_atomic_add_rb erts_no_atomic_add
#define erts_smp_atomic_read_bor_rb erts_no_atomic_read_bor
#define erts_smp_atomic_read_band_rb erts_no_atomic_read_band
#define erts_smp_atomic_xchg_rb erts_no_atomic_xchg
#define erts_smp_atomic_cmpxchg_rb erts_no_atomic_cmpxchg
#define erts_smp_atomic_read_bset_rb erts_no_atomic_read_bset

#define erts_smp_atomic_init_wb erts_no_atomic_set
#define erts_smp_atomic_set_wb erts_no_atomic_set
#define erts_smp_atomic_read_wb erts_no_atomic_read
#define erts_smp_atomic_inc_read_wb erts_no_atomic_inc_read
#define erts_smp_atomic_dec_read_wb erts_no_atomic_dec_read
#define erts_smp_atomic_inc_wb erts_no_atomic_inc
#define erts_smp_atomic_dec_wb erts_no_atomic_dec
#define erts_smp_atomic_add_read_wb erts_no_atomic_add_read
#define erts_smp_atomic_add_wb erts_no_atomic_add
#define erts_smp_atomic_read_bor_wb erts_no_atomic_read_bor
#define erts_smp_atomic_read_band_wb erts_no_atomic_read_band
#define erts_smp_atomic_xchg_wb erts_no_atomic_xchg
#define erts_smp_atomic_cmpxchg_wb erts_no_atomic_cmpxchg
#define erts_smp_atomic_read_bset_wb erts_no_atomic_read_bset

#define erts_smp_atomic_set_dirty erts_no_atomic_set
#define erts_smp_atomic_read_dirty erts_no_atomic_read

/* 32-bit atomics */

#define erts_smp_atomic32_init_nob erts_no_atomic32_set
#define erts_smp_atomic32_set_nob erts_no_atomic32_set
#define erts_smp_atomic32_read_nob erts_no_atomic32_read
#define erts_smp_atomic32_inc_read_nob erts_no_atomic32_inc_read
#define erts_smp_atomic32_dec_read_nob erts_no_atomic32_dec_read
#define erts_smp_atomic32_inc_nob erts_no_atomic32_inc
#define erts_smp_atomic32_dec_nob erts_no_atomic32_dec
#define erts_smp_atomic32_add_read_nob erts_no_atomic32_add_read
#define erts_smp_atomic32_add_nob erts_no_atomic32_add
#define erts_smp_atomic32_read_bor_nob erts_no_atomic32_read_bor
#define erts_smp_atomic32_read_band_nob erts_no_atomic32_read_band
#define erts_smp_atomic32_xchg_nob erts_no_atomic32_xchg
#define erts_smp_atomic32_cmpxchg_nob erts_no_atomic32_cmpxchg
#define erts_smp_atomic32_read_bset_nob erts_no_atomic32_read_bset

#define erts_smp_atomic32_init_mb erts_no_atomic32_set
#define erts_smp_atomic32_set_mb erts_no_atomic32_set
#define erts_smp_atomic32_read_mb erts_no_atomic32_read
#define erts_smp_atomic32_inc_read_mb erts_no_atomic32_inc_read
#define erts_smp_atomic32_dec_read_mb erts_no_atomic32_dec_read
#define erts_smp_atomic32_inc_mb erts_no_atomic32_inc
#define erts_smp_atomic32_dec_mb erts_no_atomic32_dec
#define erts_smp_atomic32_add_read_mb erts_no_atomic32_add_read
#define erts_smp_atomic32_add_mb erts_no_atomic32_add
#define erts_smp_atomic32_read_bor_mb erts_no_atomic32_read_bor
#define erts_smp_atomic32_read_band_mb erts_no_atomic32_read_band
#define erts_smp_atomic32_xchg_mb erts_no_atomic32_xchg
#define erts_smp_atomic32_cmpxchg_mb erts_no_atomic32_cmpxchg
#define erts_smp_atomic32_read_bset_mb erts_no_atomic32_read_bset

#define erts_smp_atomic32_init_acqb erts_no_atomic32_set
#define erts_smp_atomic32_set_acqb erts_no_atomic32_set
#define erts_smp_atomic32_read_acqb erts_no_atomic32_read
#define erts_smp_atomic32_inc_read_acqb erts_no_atomic32_inc_read
#define erts_smp_atomic32_dec_read_acqb erts_no_atomic32_dec_read
#define erts_smp_atomic32_inc_acqb erts_no_atomic32_inc
#define erts_smp_atomic32_dec_acqb erts_no_atomic32_dec
#define erts_smp_atomic32_add_read_acqb erts_no_atomic32_add_read
#define erts_smp_atomic32_add_acqb erts_no_atomic32_add
#define erts_smp_atomic32_read_bor_acqb erts_no_atomic32_read_bor
#define erts_smp_atomic32_read_band_acqb erts_no_atomic32_read_band
#define erts_smp_atomic32_xchg_acqb erts_no_atomic32_xchg
#define erts_smp_atomic32_cmpxchg_acqb erts_no_atomic32_cmpxchg
#define erts_smp_atomic32_read_bset_acqb erts_no_atomic32_read_bset

#define erts_smp_atomic32_init_relb erts_no_atomic32_set
#define erts_smp_atomic32_set_relb erts_no_atomic32_set
#define erts_smp_atomic32_read_relb erts_no_atomic32_read
#define erts_smp_atomic32_inc_read_relb erts_no_atomic32_inc_read
#define erts_smp_atomic32_dec_read_relb erts_no_atomic32_dec_read
#define erts_smp_atomic32_inc_relb erts_no_atomic32_inc
#define erts_smp_atomic32_dec_relb erts_no_atomic32_dec
#define erts_smp_atomic32_add_read_relb erts_no_atomic32_add_read
#define erts_smp_atomic32_add_relb erts_no_atomic32_add
#define erts_smp_atomic32_read_bor_relb erts_no_atomic32_read_bor
#define erts_smp_atomic32_read_band_relb erts_no_atomic32_read_band
#define erts_smp_atomic32_xchg_relb erts_no_atomic32_xchg
#define erts_smp_atomic32_cmpxchg_relb erts_no_atomic32_cmpxchg
#define erts_smp_atomic32_read_bset_relb erts_no_atomic32_read_bset

#define erts_smp_atomic32_init_ddrb erts_no_atomic32_set
#define erts_smp_atomic32_set_ddrb erts_no_atomic32_set
#define erts_smp_atomic32_read_ddrb erts_no_atomic32_read
#define erts_smp_atomic32_inc_read_ddrb erts_no_atomic32_inc_read
#define erts_smp_atomic32_dec_read_ddrb erts_no_atomic32_dec_read
#define erts_smp_atomic32_inc_ddrb erts_no_atomic32_inc
#define erts_smp_atomic32_dec_ddrb erts_no_atomic32_dec
#define erts_smp_atomic32_add_read_ddrb erts_no_atomic32_add_read
#define erts_smp_atomic32_add_ddrb erts_no_atomic32_add
#define erts_smp_atomic32_read_bor_ddrb erts_no_atomic32_read_bor
#define erts_smp_atomic32_read_band_ddrb erts_no_atomic32_read_band
#define erts_smp_atomic32_xchg_ddrb erts_no_atomic32_xchg
#define erts_smp_atomic32_cmpxchg_ddrb erts_no_atomic32_cmpxchg
#define erts_smp_atomic32_read_bset_ddrb erts_no_atomic32_read_bset

#define erts_smp_atomic32_init_rb erts_no_atomic32_set
#define erts_smp_atomic32_set_rb erts_no_atomic32_set
#define erts_smp_atomic32_read_rb erts_no_atomic32_read
#define erts_smp_atomic32_inc_read_rb erts_no_atomic32_inc_read
#define erts_smp_atomic32_dec_read_rb erts_no_atomic32_dec_read
#define erts_smp_atomic32_inc_rb erts_no_atomic32_inc
#define erts_smp_atomic32_dec_rb erts_no_atomic32_dec
#define erts_smp_atomic32_add_read_rb erts_no_atomic32_add_read
#define erts_smp_atomic32_add_rb erts_no_atomic32_add
#define erts_smp_atomic32_read_bor_rb erts_no_atomic32_read_bor
#define erts_smp_atomic32_read_band_rb erts_no_atomic32_read_band
#define erts_smp_atomic32_xchg_rb erts_no_atomic32_xchg
#define erts_smp_atomic32_cmpxchg_rb erts_no_atomic32_cmpxchg
#define erts_smp_atomic32_read_bset_rb erts_no_atomic32_read_bset

#define erts_smp_atomic32_init_wb erts_no_atomic32_set
#define erts_smp_atomic32_set_wb erts_no_atomic32_set
#define erts_smp_atomic32_read_wb erts_no_atomic32_read
#define erts_smp_atomic32_inc_read_wb erts_no_atomic32_inc_read
#define erts_smp_atomic32_dec_read_wb erts_no_atomic32_dec_read
#define erts_smp_atomic32_inc_wb erts_no_atomic32_inc
#define erts_smp_atomic32_dec_wb erts_no_atomic32_dec
#define erts_smp_atomic32_add_read_wb erts_no_atomic32_add_read
#define erts_smp_atomic32_add_wb erts_no_atomic32_add
#define erts_smp_atomic32_read_bor_wb erts_no_atomic32_read_bor
#define erts_smp_atomic32_read_band_wb erts_no_atomic32_read_band
#define erts_smp_atomic32_xchg_wb erts_no_atomic32_xchg
#define erts_smp_atomic32_cmpxchg_wb erts_no_atomic32_cmpxchg
#define erts_smp_atomic32_read_bset_wb erts_no_atomic32_read_bset

#define erts_smp_atomic32_set_dirty erts_no_atomic32_set
#define erts_smp_atomic32_read_dirty erts_no_atomic32_read

#endif /* !ERTS_SMP */

#if ERTS_GLB_INLINE_INCL_FUNC_DEF

ERTS_GLB_INLINE void
erts_smp_thr_init(erts_smp_thr_init_data_t *id)
{
#ifdef ERTS_SMP
    erts_thr_init(id);
#endif
}

ERTS_GLB_INLINE void
erts_smp_thr_create(erts_smp_tid_t *tid, void * (*func)(void *), void *arg,
		    erts_smp_thr_opts_t *opts)
{
#ifdef ERTS_SMP
    erts_thr_create(tid, func, arg, opts);
#endif
}

ERTS_GLB_INLINE void
erts_smp_thr_join(erts_smp_tid_t tid, void **thr_res)
{
#ifdef ERTS_SMP
    erts_thr_join(tid, thr_res);
#endif
}


ERTS_GLB_INLINE void
erts_smp_thr_detach(erts_smp_tid_t tid)
{
#ifdef ERTS_SMP
    erts_thr_detach(tid);
#endif
}


ERTS_GLB_INLINE void
erts_smp_thr_exit(void *res)
{
#ifdef ERTS_SMP
    erts_thr_exit(res);
#endif
}

ERTS_GLB_INLINE void
erts_smp_install_exit_handler(void (*exit_handler)(void))
{
#ifdef ERTS_SMP
    erts_thr_install_exit_handler(exit_handler);
#endif
}

ERTS_GLB_INLINE erts_smp_tid_t
erts_smp_thr_self(void)
{
#ifdef ERTS_SMP
    return erts_thr_self();
#else
    return 0;
#endif
}


ERTS_GLB_INLINE int
erts_smp_equal_tids(erts_smp_tid_t x, erts_smp_tid_t y)
{
#ifdef ERTS_SMP
    return erts_equal_tids(x, y);
#else
    return 1;
#endif
}


#ifdef ERTS_HAVE_REC_MTX_INIT
ERTS_GLB_INLINE void
erts_smp_rec_mtx_init(erts_smp_mtx_t *mtx)
{
#ifdef ERTS_SMP
    erts_rec_mtx_init(mtx);
#endif
}
#endif

ERTS_GLB_INLINE void
erts_smp_mtx_init_x(erts_smp_mtx_t *mtx, char *name, Eterm extra)
{
#ifdef ERTS_SMP
    erts_mtx_init_x(mtx, name, extra);
#endif
}

ERTS_GLB_INLINE void
erts_smp_mtx_init_locked_x(erts_smp_mtx_t *mtx, char *name, Eterm extra)
{
#ifdef ERTS_SMP
    erts_mtx_init_locked_x(mtx, name, extra);
#endif
}

ERTS_GLB_INLINE void
erts_smp_mtx_init(erts_smp_mtx_t *mtx, char *name)
{
#ifdef ERTS_SMP
    erts_mtx_init(mtx, name);
#endif
}

ERTS_GLB_INLINE void
erts_smp_mtx_init_locked(erts_smp_mtx_t *mtx, char *name)
{
#ifdef ERTS_SMP
    erts_mtx_init_locked(mtx, name);
#endif
}

ERTS_GLB_INLINE void
erts_smp_mtx_destroy(erts_smp_mtx_t *mtx)
{
#ifdef ERTS_SMP
    erts_mtx_destroy(mtx);
#endif
}

ERTS_GLB_INLINE int
erts_smp_mtx_trylock(erts_smp_mtx_t *mtx)
{
#ifdef ERTS_SMP
    return erts_mtx_trylock(mtx);
#else
    return 0;
#endif

}


ERTS_GLB_INLINE void
#ifdef ERTS_ENABLE_LOCK_COUNT
erts_smp_mtx_lock_x(erts_smp_mtx_t *mtx, char *file, int line)
#else
erts_smp_mtx_lock(erts_smp_mtx_t *mtx)
#endif
{
#if defined(ERTS_SMP) && defined(ERTS_ENABLE_LOCK_COUNT)
    erts_mtx_lock_x(mtx, file, line);
#elif defined(ERTS_SMP)
    erts_mtx_lock(mtx);
#endif
}

ERTS_GLB_INLINE void
erts_smp_mtx_unlock(erts_smp_mtx_t *mtx)
{
#ifdef ERTS_SMP
    erts_mtx_unlock(mtx);
#endif
}

ERTS_GLB_INLINE int
erts_smp_lc_mtx_is_locked(erts_smp_mtx_t *mtx)
{
#if defined(ERTS_SMP) && defined(ERTS_ENABLE_LOCK_CHECK)
    return erts_lc_mtx_is_locked(mtx);
#else
    return 0;
#endif
}

ERTS_GLB_INLINE void
erts_smp_cnd_init(erts_smp_cnd_t *cnd)
{
#ifdef ERTS_SMP
    erts_cnd_init(cnd);
#endif
}

ERTS_GLB_INLINE void
erts_smp_cnd_destroy(erts_smp_cnd_t *cnd)
{
#ifdef ERTS_SMP
    erts_cnd_destroy(cnd);
#endif
}

ERTS_GLB_INLINE void
erts_smp_cnd_wait(erts_smp_cnd_t *cnd, erts_smp_mtx_t *mtx)
{
#ifdef ERTS_SMP
    erts_cnd_wait(cnd, mtx);
#endif
}

/*
 * IMPORTANT note about erts_smp_cnd_signal() and erts_smp_cnd_broadcast()
 *
 * POSIX allow a call to `pthread_cond_signal' or `pthread_cond_broadcast'
 * even though the associated mutex/mutexes isn't/aren't locked by the
 * caller. Our implementation do not allow that in order to avoid a
 * performance penalty. That is, all associated mutexes *need* to be
 * locked by the caller of erts_smp_cnd_signal()/erts_smp_cnd_broadcast()!
 */

ERTS_GLB_INLINE void
erts_smp_cnd_signal(erts_smp_cnd_t *cnd)
{
#ifdef ERTS_SMP
    erts_cnd_signal(cnd);
#endif
}


ERTS_GLB_INLINE void
erts_smp_cnd_broadcast(erts_smp_cnd_t *cnd)
{
#ifdef ERTS_SMP
    erts_cnd_broadcast(cnd);
#endif
}

ERTS_GLB_INLINE void
erts_smp_rwmtx_set_reader_group(int no)
{
#ifdef ERTS_SMP
    erts_rwmtx_set_reader_group(no);
#endif
}

ERTS_GLB_INLINE void
erts_smp_rwmtx_init_opt_x(erts_smp_rwmtx_t *rwmtx,
			  erts_smp_rwmtx_opt_t *opt,
			  char *name,
			  Eterm extra)
{
#ifdef ERTS_SMP
    erts_rwmtx_init_opt_x(rwmtx, opt, name, extra);
#endif
}

ERTS_GLB_INLINE void
erts_smp_rwmtx_init_x(erts_smp_rwmtx_t *rwmtx, char *name, Eterm extra)
{
#ifdef ERTS_SMP
    erts_rwmtx_init_x(rwmtx, name, extra);
#endif
}

ERTS_GLB_INLINE void
erts_smp_rwmtx_init_opt(erts_smp_rwmtx_t *rwmtx,
			erts_smp_rwmtx_opt_t *opt,
			char *name)
{
#ifdef ERTS_SMP
    erts_rwmtx_init_opt(rwmtx, opt, name);
#endif
}

ERTS_GLB_INLINE void
erts_smp_rwmtx_init(erts_smp_rwmtx_t *rwmtx, char *name)
{
#ifdef ERTS_SMP
    erts_rwmtx_init(rwmtx, name);
#endif
}

ERTS_GLB_INLINE void
erts_smp_rwmtx_destroy(erts_smp_rwmtx_t *rwmtx)
{
#ifdef ERTS_SMP
    erts_rwmtx_destroy(rwmtx);
#endif
}

ERTS_GLB_INLINE int
erts_smp_rwmtx_tryrlock(erts_smp_rwmtx_t *rwmtx)
{
#ifdef ERTS_SMP
    return erts_rwmtx_tryrlock(rwmtx);
#else
    return 0;
#endif
}

ERTS_GLB_INLINE void
#ifdef ERTS_ENABLE_LOCK_COUNT
erts_smp_rwmtx_rlock_x(erts_smp_rwmtx_t *rwmtx, char *file, unsigned int line)
#else
erts_smp_rwmtx_rlock(erts_smp_rwmtx_t *rwmtx)
#endif
{
#if defined(ERTS_SMP) && defined(ERTS_ENABLE_LOCK_COUNT)
    erts_rwmtx_rlock_x(rwmtx, file, line);
#elif defined(ERTS_SMP)
    erts_rwmtx_rlock(rwmtx);
#endif
}

ERTS_GLB_INLINE void
erts_smp_rwmtx_runlock(erts_smp_rwmtx_t *rwmtx)
{
#ifdef ERTS_SMP
    erts_rwmtx_runlock(rwmtx);
#endif
}


ERTS_GLB_INLINE int
erts_smp_rwmtx_tryrwlock(erts_smp_rwmtx_t *rwmtx)
{
#ifdef ERTS_SMP
    return erts_rwmtx_tryrwlock(rwmtx);
#else
    return 0;
#endif
}

ERTS_GLB_INLINE void
#ifdef ERTS_ENABLE_LOCK_COUNT
erts_smp_rwmtx_rwlock_x(erts_smp_rwmtx_t *rwmtx, char *file, unsigned int line)
#else
erts_smp_rwmtx_rwlock(erts_smp_rwmtx_t *rwmtx)
#endif
{
#if defined(ERTS_SMP) && defined(ERTS_ENABLE_LOCK_COUNT)
    erts_rwmtx_rwlock_x(rwmtx, file, line);
#elif defined(ERTS_SMP)
    erts_rwmtx_rwlock(rwmtx);
#endif
}

ERTS_GLB_INLINE void
erts_smp_rwmtx_rwunlock(erts_smp_rwmtx_t *rwmtx)
{
#ifdef ERTS_SMP
    erts_rwmtx_rwunlock(rwmtx);
#endif
}

#if 0 /* The following rwmtx function names are
	 reserved for potential future use. */ 

/* Try upgrade from r-locked state to rw-locked state */
ERTS_GLB_INLINE int
erts_smp_rwmtx_trywlock(erts_smp_rwmtx_t *rwmtx)
{
    return 0;
}

/* Upgrade from r-locked state to rw-locked state */
ERTS_GLB_INLINE void
erts_smp_rwmtx_wlock(erts_smp_rwmtx_t *rwmtx)
{

}

/* Downgrade from rw-locked state to r-locked state */
ERTS_GLB_INLINE void
erts_smp_rwmtx_wunlock(erts_smp_rwmtx_t *rwmtx)
{

}

#endif

ERTS_GLB_INLINE int
erts_smp_lc_rwmtx_is_rlocked(erts_smp_rwmtx_t *mtx)
{
#if defined(ERTS_SMP) && defined(ERTS_ENABLE_LOCK_CHECK)
    return erts_lc_rwmtx_is_rlocked(mtx);
#else
    return 0;
#endif
}

ERTS_GLB_INLINE int
erts_smp_lc_rwmtx_is_rwlocked(erts_smp_rwmtx_t *mtx)
{
#if defined(ERTS_SMP) && defined(ERTS_ENABLE_LOCK_CHECK)
    return erts_lc_rwmtx_is_rwlocked(mtx);
#else
    return 0;
#endif
}

ERTS_GLB_INLINE void
erts_smp_spinlock_init_x(erts_smp_spinlock_t *lock, char *name, Eterm extra)
{
#ifdef ERTS_SMP
    erts_spinlock_init_x(lock, name, extra);
#else
    (void)lock;
#endif
}

ERTS_GLB_INLINE void
erts_smp_spinlock_init(erts_smp_spinlock_t *lock, char *name)
{
#ifdef ERTS_SMP
    erts_spinlock_init(lock, name);
#else
    (void)lock;
#endif
}

ERTS_GLB_INLINE void
erts_smp_spinlock_destroy(erts_smp_spinlock_t *lock)
{
#ifdef ERTS_SMP
    erts_spinlock_destroy(lock);
#else
    (void)lock;
#endif
}

ERTS_GLB_INLINE void
erts_smp_spin_unlock(erts_smp_spinlock_t *lock)
{
#ifdef ERTS_SMP
    erts_spin_unlock(lock);
#else
    (void)lock;
#endif
}

ERTS_GLB_INLINE void
#ifdef ERTS_ENABLE_LOCK_COUNT
erts_smp_spin_lock_x(erts_smp_spinlock_t *lock, char *file, unsigned int line)
#else
erts_smp_spin_lock(erts_smp_spinlock_t *lock)
#endif
{
#if defined(ERTS_SMP) && defined(ERTS_ENABLE_LOCK_COUNT)
    erts_spin_lock_x(lock, file, line);
#elif defined(ERTS_SMP)
    erts_spin_lock(lock);
#else
    (void)lock;
#endif
}

ERTS_GLB_INLINE int
erts_smp_lc_spinlock_is_locked(erts_smp_spinlock_t *lock)
{
#if defined(ERTS_SMP) && defined(ERTS_ENABLE_LOCK_CHECK)
    return erts_lc_spinlock_is_locked(lock);
#else
    return 0;
#endif
}

ERTS_GLB_INLINE void
erts_smp_rwlock_init_x(erts_smp_rwlock_t *lock, char *name, Eterm extra)
{
#ifdef ERTS_SMP
    erts_rwlock_init_x(lock, name, extra);
#else
    (void)lock;
#endif
}

ERTS_GLB_INLINE void
erts_smp_rwlock_init(erts_smp_rwlock_t *lock, char *name)
{
#ifdef ERTS_SMP
    erts_rwlock_init(lock, name);
#else
    (void)lock;
#endif
}

ERTS_GLB_INLINE void
erts_smp_rwlock_destroy(erts_smp_rwlock_t *lock)
{
#ifdef ERTS_SMP
    erts_rwlock_destroy(lock);
#else
    (void)lock;
#endif
}

ERTS_GLB_INLINE void
erts_smp_read_unlock(erts_smp_rwlock_t *lock)
{
#ifdef ERTS_SMP
    erts_read_unlock(lock);
#else
    (void)lock;
#endif
}

ERTS_GLB_INLINE void
#ifdef ERTS_ENABLE_LOCK_COUNT
erts_smp_read_lock_x(erts_smp_rwlock_t *lock, char *file, unsigned int line)
#else
erts_smp_read_lock(erts_smp_rwlock_t *lock)
#endif 
{
#if defined(ERTS_ENABLE_LOCK_COUNT) && defined(ERTS_SMP)
    erts_read_lock_x(lock, file, line);
#elif defined(ERTS_SMP)
    erts_read_lock(lock);
#else
    (void)lock;
#endif
}

ERTS_GLB_INLINE void
erts_smp_write_unlock(erts_smp_rwlock_t *lock)
{
#ifdef ERTS_SMP
    erts_write_unlock(lock);
#else
    (void)lock;
#endif
}

ERTS_GLB_INLINE void
#ifdef ERTS_ENABLE_LOCK_COUNT
erts_smp_write_lock_x(erts_smp_rwlock_t *lock, char *file, unsigned int line)
#else
erts_smp_write_lock(erts_smp_rwlock_t *lock)
#endif 
{
#if defined(ERTS_SMP) && defined(ERTS_ENABLE_LOCK_COUNT)
    erts_write_lock_x(lock, file, line);
#elif defined(ERTS_SMP)
    erts_write_lock(lock);
#else
    (void)lock;
#endif
}

ERTS_GLB_INLINE int
erts_smp_lc_rwlock_is_rlocked(erts_smp_rwlock_t *lock)
{
#if defined(ERTS_SMP) && defined(ERTS_ENABLE_LOCK_CHECK)
    return erts_lc_rwlock_is_rlocked(lock);
#else
    return 0;
#endif
}

ERTS_GLB_INLINE int
erts_smp_lc_rwlock_is_rwlocked(erts_smp_rwlock_t *lock)
{
#if defined(ERTS_SMP) && defined(ERTS_ENABLE_LOCK_CHECK)
    return erts_lc_rwlock_is_rwlocked(lock);
#else
    return 0;
#endif
}

ERTS_GLB_INLINE void
erts_smp_tsd_key_create(erts_smp_tsd_key_t *keyp)
{
#ifdef ERTS_SMP
    erts_tsd_key_create(keyp);
#endif
}

ERTS_GLB_INLINE void
erts_smp_tsd_key_delete(erts_smp_tsd_key_t key)
{
#ifdef ERTS_SMP
    erts_tsd_key_delete(key);
#endif
}

ERTS_GLB_INLINE void
erts_smp_tsd_set(erts_smp_tsd_key_t key, void *value)
{
#ifdef ERTS_SMP
    erts_tsd_set(key, value);
#endif
}

ERTS_GLB_INLINE void *
erts_smp_tsd_get(erts_smp_tsd_key_t key)
{
#ifdef ERTS_SMP
    return erts_tsd_get(key);
#else
    return NULL;
#endif
}

#ifdef ERTS_THR_HAVE_SIG_FUNCS
#define ERTS_SMP_THR_HAVE_SIG_FUNCS 1

ERTS_GLB_INLINE void
erts_smp_thr_sigmask(int how, const sigset_t *set, sigset_t *oset)
{
#ifdef ERTS_SMP
    erts_thr_sigmask(how, set, oset);
#endif
}

ERTS_GLB_INLINE void
erts_smp_thr_sigwait(const sigset_t *set, int *sig)
{
#ifdef ERTS_SMP
    erts_thr_sigwait(set, sig);
#endif
}

#endif /* #ifdef ERTS_THR_HAVE_SIG_FUNCS */

#endif /* #if ERTS_GLB_INLINE_INCL_FUNC_DEF */

#endif /* ERL_SMP_H */

#ifdef ERTS_UNDEF_DEPRECATED_ATOMICS

/* Deprecated functions to replace */

#undef erts_smp_atomic_init
#undef erts_smp_atomic_set
#undef erts_smp_atomic_read
#undef erts_smp_atomic_inctest
#undef erts_smp_atomic_dectest
#undef erts_smp_atomic_inc
#undef erts_smp_atomic_dec
#undef erts_smp_atomic_addtest
#undef erts_smp_atomic_add
#undef erts_smp_atomic_xchg
#undef erts_smp_atomic_cmpxchg
#undef erts_smp_atomic_bor
#undef erts_smp_atomic_band

#undef erts_smp_atomic32_init
#undef erts_smp_atomic32_set
#undef erts_smp_atomic32_read
#undef erts_smp_atomic32_inctest
#undef erts_smp_atomic32_dectest
#undef erts_smp_atomic32_inc
#undef erts_smp_atomic32_dec
#undef erts_smp_atomic32_addtest
#undef erts_smp_atomic32_add
#undef erts_smp_atomic32_xchg
#undef erts_smp_atomic32_cmpxchg
#undef erts_smp_atomic32_bor
#undef erts_smp_atomic32_band

#endif
