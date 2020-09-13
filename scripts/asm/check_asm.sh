rm log 2> /dev/null;
for i in champ/*.s;
do
	echo $i >> log;
	./asm $i >> log;
	i=${i/.s/.cor};
	mv $i mycor.cor;
	i=${i/.cor/.s};
	./zasm $i >> log;
	i=${i/.s/.cor};
	mv $i zazcor.cor;
	diff mycor.cor zazcor.cor >> log;
done
