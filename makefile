CXX = g++
FLAGS = -gstabs+

all: cTest.out t1.out t2.out t3.out proj2.out

cTest.out: SqList.o INode.o DNode.o Int341.o p2comptest.cpp
	$(CXX) $(FLAGS) SqList.o INode.o DNode.o Int341.o p2comptest.cpp -o cTest.out

t1.out: SqList.o INode.o DNode.o Int341.o p2timetest1.cpp
	$(CXX) $(FLAGS) SqList.o INode.o DNode.o Int341.o p2timetest1.cpp -o t1.out

t2.out: SqList.o INode.o DNode.o Int341.o p2timetest2.cpp
	$(CXX) $(FLAGS) SqList.o INode.o DNode.o Int341.o p2timetest2.cpp -o t2.out

t3.out: SqList.o INode.o DNode.o Int341.o p2timetest3.cpp
	$(CXX) $(FLAGS) SqList.o INode.o DNode.o Int341.o p2timetest3.cpp -o t3.out

proj2.out: SqList.o INode.o DNode.o Int341.o driver.cpp
	$(CXX) $(FLAGS) SqList.o INode.o DNode.o Int341.o driver.cpp -o proj2.out

SqList.o: SqList.cpp SqList.h INode.o DNode.o Int341.o
	$(CXX) $(FLAGS) -c SqList.cpp

INode.o: INode.cpp INode.h DNode.o Int341.o
	$(CXX) $(FLAGS) -c INode.cpp

DNode.o: DNode.cpp DNode.h Int341.o
	$(CXX) $(FLAGS) -c DNode.cpp

Int341.o: Int341.cpp Int341.h
	$(CXX) $(FLAGS) -c Int341.cpp

run:
	./proj2.out

testc:
	./cTest.out
test1:
	./t1.out
test2:
	./t2.out
test3:
	./t3.out

val:
	valgrind ./proj2.out

valc:
	valgrind ./cTest.out
val1:
	valgrind ./t1.out
val2:
	valgrind ./t2.out
val3:
	valgrind ./t3.out

leak:
	valgrind --leak-check=full ./proj2.out

clean:
	rm *~

cleaner:
	rm *.o

cleanest:
	rm *~
	rm *.o