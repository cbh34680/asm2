#!/bin/bash

unalias -a
cd "$(dirname "$(readlink -f "${BASH_SOURCE:-$0}")")"

(
cat << EOF
%include "defs.s"

	section	.text
;
EOF

ausyscall --dump | sed 1d | grep -E \
'\b(exit|open|close|read|write|brk)\b' \
| while read sno sname
do
  cat << EOF
global syscall_${sname}

syscall_${sname}:
	mov		eax, ${sno}
	syscall
	ret
;
EOF

done

) > syscall.s

cat syscall.s | awk -F: '$1 ~ /^syscall_.*$/{print "extern " $1}' > ../inc.d/sysc.s

exit 0

