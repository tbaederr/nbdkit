#!/usr/bin/env bash
# nbdkit
# Copyright (C) 2018-2019 Red Hat Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
# * Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution.
#
# * Neither the name of Red Hat nor the names of its contributors may be
# used to endorse or promote products derived from this software without
# specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY RED HAT AND CONTRIBUTORS ''AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
# PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL RED HAT OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
# USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
# OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.

source ./functions.sh
set -e
set -x

requires qemu-img --version

files="rate.img rate.time rate.err"
rm -f $files
cleanup_fn rm -f $files

# This should take no less than 20 seconds to run:
#   (8 * 25 * 1024 * 1024) / (10 * 1024 * 1024) = 20

# We are using the bash time builtin, so setting TIMEFORMAT will
# control the output format of the time builtin.  For strange use of
# { ; } here, see: https://stackoverflow.com/a/13356654
set +x
{ TIMEFORMAT="%0R" ; time nbdkit --filter=rate memory size=25M rate=10M --run 'qemu-img convert -p $nbd rate.img' 2>rate.err ; } 2>rate.time
set -x

cat rate.err ||:

seconds="$( cat rate.time )"
if [ "$seconds" -lt 20 ]; then
    echo "$0: rate filter failed: command took $seconds seconds, expected > 20"
    exit 1
fi
