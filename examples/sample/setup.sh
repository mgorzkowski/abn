#!/bin/bash

die() {
    echo $1
    exit -1
}

[[ ! -z $ABN_ROOT ]] || die "There is no defined ABN_ROOT env variable. Run 'source ./env.sh' in the root abn directory."
ln -s $ABN_ROOT 3rd_party/abn