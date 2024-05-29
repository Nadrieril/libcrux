#!/usr/bin/env bash

set -e
set -o pipefail

cdir=c

# rm -rf $cdir

if [[ -z "$CHARON_HOME" ]]; then
    echo "Please set CHARON_HOME to the Charon directory" 1>&2
    exit 1
fi
if [[ -z "$EURYDICE_HOME" ]]; then
    echo "Please set EURYDICE_HOME to the Eurydice directory" 1>&2
    exit 1
fi

portable_only=0
no_hacl=0
no_charon=0

# Parse command line arguments.
all_args=("$@")
while [ $# -gt 0 ]; do
    case "$1" in
    -p | --portable) portable_only=1 ;;
    --no-hacl) no_hacl=1 ;;
    --no-charon) no_charon=1 ;;
    esac
    shift
done

if [[ "$portable_only" = 1 ]]; then
    export LIBCRUX_DISABLE_SIMD256=1
    export LIBCRUX_DISABLE_SIMD128=1
fi

if [[ "$no_charon" = 0 ]]; then
    echo "Running charon ..."
    RUSTFLAGS="--cfg eurydice" $CHARON_HOME/bin/charon --errors-as-warnings
else
    echo "Skipping charon"
fi

mkdir -p $cdir
cd $cdir

echo "Running eurydice ..."
$EURYDICE_HOME/eurydice --config ../c.yaml ../../libcrux_sha3.llbc
cp $EURYDICE_HOME/include/eurydice_glue.h .

# TODO: copy karamel
