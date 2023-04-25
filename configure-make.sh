#!/usr/bin/env bash

UBENCHOS_COMMON_CONFIG=make/ubenchos-common-config.mk

SOURCE=${BASH_SOURCE[0]}
while [ -L "$SOURCE" ]; do
  SCRIPT_DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )
  SOURCE=$(readlink "$SOURCE")
  [[ $SOURCE != /* ]] && SOURCE=$DIR/$SOURCE
done
SCRIPT_DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )

(
    echo "UBENCHOS_DIR := $SCRIPT_DIR"
    echo "UBENCHOS_MAKE_DIR := $SCRIPT_DIR/make"
    echo "UBENCHOS_THIRD_PARTY_DIR := $SCRIPT_DIR/third_party"
) > $UBENCHOS_COMMON_CONFIG
