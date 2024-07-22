#!/bin/bash
# This script removes specific revision number lines from files that
# have them. Its purpose is to allow diffing of extraction results
# independent of concrete tool revs used for extraction.
#
# Run this from the repository root.

grep -rl -e "This code was generated with the following revisions:" "$1" | xargs -d '\n' sed -i -f libcrux-ml-kem/header_kill_revs.sed
