all: scanner rd_parser rd_parser_bonus

scanner: scanner.c
	gcc scanner.c -o scanner

rd_parser: rd_parser.c
	gcc stack.c rd_parser.c -o rd_parser

rd_parser_bonus: rd_parser_bonus.c
	gcc stack.c rd_parser_bonus.c -o rd_parser_bonus

clean:
	rm -rf scanner rd_parser rd_parser_bonus

