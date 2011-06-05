OBJECTS = kmeans

all: $(OBJECTS)

clean:
	rm -f $(OBJECTS)

kmeans: kmeans.c
	$(CXX) $^ -o $@ `pkg-config --cflags --libs opencv`
