TARGETS=bubblesort quicksort
all: $(TARGETS)

%: %.c
	gcc $^ -o $@

clean:
	rm -f $(TARGETS)
	rm -f *.o *~
