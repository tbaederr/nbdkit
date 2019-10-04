/* nbdkit
 * Copyright (C) 2018 Red Hat Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * * Neither the name of Red Hat nor the names of its contributors may be
 * used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY RED HAT AND CONTRIBUTORS ''AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL RED HAT OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/* This file pretends to be libvixDiskLib.so.6.
 *
 * However it only implements --dump-plugin support so our stubs don't
 * need to do anything.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "vddk-structs.h"

VixError
VixDiskLib_InitEx (uint32_t major, uint32_t minor,
                   VixDiskLibGenericLogFunc *log_function,
                   VixDiskLibGenericLogFunc *warn_function,
                   VixDiskLibGenericLogFunc *panic_function,
                   const char *lib_dir, const char *config_file)
{
  /* Do nothing, only exit with no error. */
  return VIX_OK;
}

void
VixDiskLib_Exit (void)
{
  /* Do nothing. */
}

#define STUB(fn) void fn (void) { abort (); }
STUB (VixDiskLib_GetErrorText)
STUB (VixDiskLib_FreeErrorText)
STUB (VixDiskLib_ConnectEx)
STUB (VixDiskLib_Open)
STUB (VixDiskLib_GetTransportMode)
STUB (VixDiskLib_Close)
STUB (VixDiskLib_Disconnect)
STUB (VixDiskLib_GetInfo)
STUB (VixDiskLib_FreeInfo)
STUB (VixDiskLib_Read)
STUB (VixDiskLib_Write)
STUB (VixDiskLib_FreeConnectParams)