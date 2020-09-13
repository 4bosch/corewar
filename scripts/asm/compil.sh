#!/bin/bash
./zasm test.s; mv test.cor zaz.cor; ./asm test.s; mv test.cor my.cor; vbindiff zaz.cor my.cor;
rm zaz.cor my.cor
