all: pipeline

Run_pipeline: pipeline
	@./pipeline.out

pipeline:
	@rm -f pipeline.out
	@gcc pipeline.c -lpthread -o pipeline.out

clean:
	@rm *.out
