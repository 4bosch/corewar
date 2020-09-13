#!/bin/zsh

header=\
'.name  "get operation"
.comment "no comment"

'
echo "$header$1" > /tmp/operation_bin.s
hexa=$(./asm /tmp/operation_bin.s 1>/dev/null && cat /tmp/operation_bin.cor \
	| xxd -u | tail +138 | tail -c +11 | sed 's/  .*//')

deci=$(echo "ibase=16; $(printf $hexa | sed 's/ //g')" | bc)

echo "Hex: $hexa"
echo "dec: $deci"

# $ scripts/getop.sh 'ld %24, r2'
# Hex: 0290 0000 0018 02
# dec: 721279627827202
