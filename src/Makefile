PROJECT=snake
CXX=g++
CXX_FLAGS= -Wall      \
		  -ansi      \
		  -pedantic  \
		  -O2		 \
		  -std=c++11 
LINK_FLAGS= -lsfml-graphics -lsfml-window -lsfml-system 
		  		  
all: snake
 
snake: snake.o 
	$(CXX) -o $(PROJECT) snake.o $(CXX_FLAGS) $(LINK_FLAGS)
 
snake.o: snake.cpp
	$(CXX)  -o snake.o -c snake.cpp  $(CXX_FLAGS)
  
clean:
	rm -rf *.o *~ $(PROJECT)
