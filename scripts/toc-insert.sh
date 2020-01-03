#!/usr/bin/env bash
ROOT_DIR="$(cd -P "$(dirname "${BASH_SOURCE[0]}")/.." && pwd )"

${ROOT_DIR}/scripts/gh-md-toc --insert ${ROOT_DIR}/README.md
rm -f ${ROOT_DIR}/*.md.orig.*
rm -f ${ROOT_DIR}/*.md.toc.*
