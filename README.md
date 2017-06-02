#Queues

Queues is a project for simulating M/M/1 queues. It uses an Unity part to show the results on graph to check if it matches the expected average.
You can see an example on: http://juscelinotanaka.com.br/avaldes/

Using the library you can use the function ExecMM1(params..); to get a double with the average time spent to run the M/M/1 queue.

This library was developed using a Clion and is under the QueuesLib folder.

The Unity project is under the folder Unity but the lib itselfs is completely independent of it.

This project is part of the class "Avaliação de Desempenho" (Perfomance Evaluation) at UFAM and is under development by Juscelino Tanaka.

The goals now are:
Implement new Queues Support (M/M/m, M/M/m/B, M/D/1, M/E/1, M/H/1).

This library uses Mersenne Twister to generate random numbers. However, we do not support this library and it has its own license.
You can read more about it in here: https://en.wikipedia.org/wiki/Mersenne_Twister.
The C++ code was taken from here: http://jblevins.org/projects/mt

This code is free to be used.
License is under its license file.
