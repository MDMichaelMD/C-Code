CCFLAGS = -fopenmp -lm
OBJ = model.o reactiondiffusion.o
.INTERMEDIATE: $(OBJ)

reactiondiffusion: $(OBJ)
	gcc -o $@ $^ $(CCFLAGS)

%.o: %.c
	gcc -c -o $@ $< $(CCFLAGS)

.PHONY: clean
clean:
	rm -f reactiondiffusion
