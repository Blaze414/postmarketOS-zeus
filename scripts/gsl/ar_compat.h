/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Force-included ahead of everything (see the Makefile's -include).
 *
 * graphservices decorates unused parameters with bionic's __unused, which
 * neither glibc nor musl define. Defining it on the command line works on
 * glibc but breaks musl, whose bits/stat.h and the SysV IPC headers use
 * __unused as an ordinary struct member name - the macro would expand inside
 * the struct and the header would not parse.
 *
 * Pulling those headers in first, while __unused is still just an identifier,
 * and only then defining the macro, satisfies both: the include guards make
 * the tree's own later #includes of them no-ops.
 */
#ifndef AR_COMPAT_H
#define AR_COMPAT_H

#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>

#ifndef __unused
#define __unused __attribute__((__unused__))
#endif

#endif /* AR_COMPAT_H */
