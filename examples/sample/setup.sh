#!/bin/bash

script_name="setup.sh"

die() {
    echo >&2 "$script_name: $@"
    exit 1
}


[[ ! -z $ABN_ROOT ]] || die "There is no defined ABN_ROOT env variable. Run 'source ./env.sh' in the root abn directory."
ln -s $ABN_ROOT 3rd_party/abn
