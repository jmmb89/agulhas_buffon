#!/bin/bash

PROG=ado
SENSEI=$(whoami)

[ "$1" == "-c" ] || [ "$1" == "--compile" ] && [ -f "$PROG" ] && rm $PROG

echo -e "\e[38;5;$((RANDOM%257))m
    3.141592
   653589793
  23    84
 6 2    64
   3    38
   3    27
   9    50 2
 8 8    4197
  16     93\e[0m"

echo -e "\nBem vindo $SENSEI!\n"

if ! [ -f "$PROG" ]; then
  echo -e "\nCompilando EP.."
  gcc $PROG.c -o $PROG -lm && chmod +x $PROG && echo "Compilado com sucesso!" || exit 
fi

./$PROG

cat << 'EOF'


 ___________________________
< May the source be with you >
 --------------------------- 
   \
    \
        .--.
       |o_o |
       |:_/ |
      //   \ \
     (|     | )
    /'\_   _/`\
    \___)=(___/

EOF
