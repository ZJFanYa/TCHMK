all:
	g++ -c bigNumDLL.cpp
	g++ -shared -o bigNum.dll bigNumDLL.o
	g++ Tchmk_Lab2.cpp bigNum.dll -I. -Wl,-rpath,. -L. -o bigNum.exe