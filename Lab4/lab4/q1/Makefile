all: writer reader

Run_writer: writer
	@./writer.out

Run_reader: reader
	@./reader.out

writer:
	@rm -f writer.out
	@gcc writer.c -o writer.out

reader:
	@rm -f reader.out
	@gcc reader.c -o reader.out

clean:
	@rm *.outs
