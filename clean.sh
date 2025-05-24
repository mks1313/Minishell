#!/bin/bash

echo "🧹 Limpiando todo excepto inc/, src/, obj/, Makefile, minishell, y tests .sh/.txt..."

find . -mindepth 1 -maxdepth 1 \( ! -name 'inc' ! -name 'src' ! -name 'obj' \
  ! -name 'Makefile' ! -name 'minishell' \
  ! -name 'test_cases.txt' ! -name 'test_compare.sh'  ! -name 'clean.sh'  \
  ! -name '.git' ! -name '.gitignore' ! -name 'test_compare_clean.sh' \) -exec rm -rf {} +

echo "✅ Limpieza completada."
