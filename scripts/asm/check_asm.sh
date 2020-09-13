rm log 2> /dev/null;
for i in champ/valid/*.s;
do
	echo $i >> log;
	$1 $i >> log;
	i=${i/.s/.cor};
	mv $i mycor.cor;
	i=${i/.cor/.s};
	scripts/asm/zasm $i >> log;
	i=${i/.s/.cor};
	mv $i zazcor.cor;
	diff mycor.cor zazcor.cor >> log;
done
