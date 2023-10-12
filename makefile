lexer: lexer.o lexeme.o
	gcc lexer.c lexeme.c -o lexer

run: lexer
	./lexer files/complex.cci files/complex.cci.lexer && \
	./lexer files/complex.ccx files/complex.ccx.lexer && \
	./lexer files/date.cci files/date.cci.lexer && \
	./lexer files/date.ccx files/date.ccx.lexer && \
	./lexer files/hello_world.ccx files/hello_world.ccx.lexer && \
	./lexer files/list.cci files/list.cci.lexer && \
	./lexer files/list.ccx files/list.ccx.lexer && \
	./lexer files/natural.cci files/natural.cci.lexer &&\
	./lexer files/natural.ccx files/natural.ccx.lexer &&\
	./lexer files/trie.cci files/trie.cci.lexer &&\
    ./lexer files/trie.ccx files/trie.ccx.lexer && \
    ./lexer files/widget.cci files/widget.cci.lexer &&\
    ./lexer files/widget.ccx files/widget.ccx.lexer

clean:
	rm -f files/*.lexer

