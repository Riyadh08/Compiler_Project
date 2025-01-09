ryad : 
	bison -d ryad.y
	flex ryad.l
	gcc ryad.tab.c lex.yy.c -o ryad
	./ryad

clean:
	del ryad.exe ryad.tab.c ryad.tab.h lex.yy.c output.txt
