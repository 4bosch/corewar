rm log 2> /dev/null;
for i in $@;
do
	echo $i >> log;
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./asm $i 2>&1 | egrep 'lost:|still reachable:' >> log;
	./asm $i >> log;
	./zasm $i >> log;
done
