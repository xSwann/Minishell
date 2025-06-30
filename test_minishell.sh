#!/bin/bash

# Test << ARF | ls | echo "bonjour" > output.txt
./minishell \
    "<<" 4 \
	"ARF" 1 \
    "|" 2 \
	"ls" 1 \
    "|" 2 \
	"echo "bonjour"" 1 \
    ">" 5 \
	"output.txt" 1 \
    "" 7

# Test input.txt cat -e | cat -e > output.txt
./minishell \
    "<<" 4 \
	"ARF" 1 \
    "|" 2 \
	"ls" 1 \
    "|" 2 \
	"echo fdfdf fb fdbdfb dbdfb" 1 \
    ">" 5 \
	"output.txt" 1 \
    "" 7
