# Queues (Portuguese)

Queues é um projeto de simulação de filas M/M/1. Este projeto tem um parte Unity que  utilizada para gerar um gráfico a partir dos resultados obtidos da biblioteca para checagem se os valores correspodem às médias esperadas.

Você pode conferir o exemplo da interface em: http://juscelinotanaka.com.br/avaldes/

Ao usar a biblioteca, você pode invocar a função ExecMM1 (com seus respectivos parâmetros) que retornará um valor double com o tempo médio gasto para a execução da fila M/M/1.

- O parâmetro exponent será a quantidade 10^exponent elementos que passarão na fila.
- Os demais parâmetros são respectivos aos valores para execução da fila.
- O parâmetro "server" deve ser 1, no caso de filas M/M/"1". Esta é uma abertura para futuras implementações.
- O parâmetro listQueue pode ser qualquer valor até futuras correções/remoção.

A biblioteca em si foi desenvolvida dentro da IDE Clion e está na pasta QueueLib. (Se você usar está IDE é só abrir o projeto por ela. Caso contrário, você pode apenas copiar os arquivos .h e .cpp para um novo projeto na sua IDE de preferência).

O projeto Unity esta na pasta Unity, contudo a biblioteca de filas funciona totalmente independente da parte Unity.

Este projeto é parte da matéria Avaliação de Desempenho, ministrada pelo professor Dr. Edjair Mota, durante o período 2017/01 da UFAM e está em desenvolvimento pelo aluno Juscelino Tanaka.

Os próximos passos para o desenvolvimento são:
Implementar suporte a novas filas: M/M/m, M/M/m/B, M/D/1, M/E/1, M/H/1.

Esta biblioteca usa a biblioteca de gerador de números aleatórios Mersenne Twister. Com isto, nós não nos responsabilizamos com as partes referentes a esta biblioteca que contem sua própria licença.
Você pode ler mais sobre ela aqui: https://en.wikipedia.org/wiki/Mersenne_Twister.
O código em C++ foi tirado de: http://jblevins.org/projects/mt

Este código é livre para ser usado.
A licença encontra-se no arquivo LICENSE.


# Queues (English)

Queues is a project for simulating M/M/1 queues. It uses an Unity part to show the results on graph to check if it matches the expected average.
You can see an example on: http://juscelinotanaka.com.br/avaldes/

Using the library you can use the function ExecMM1(params..); to get a double with the average time spent to run the M/M/1 queue.

This library was developed using a Clion IDE and is under the QueueLib folder.

The Unity project is under the folder Unity but the lib itselfs is completely independent of it.

This project is part of the class "Avaliação de Desempenho" (Perfomance Evaluation) under the orientation of Prof. Dr. Edjair Mota at UFAM 2017/01 and is under development by Juscelino Tanaka.

The goals now are:
Implement new Queues Support (M/M/m, M/M/m/B, M/D/1, M/E/1, M/H/1).

This library uses Mersenne Twister to generate random numbers. However, we do not support this library and it has its own license.
You can read more about it in here: https://en.wikipedia.org/wiki/Mersenne_Twister.
The C++ code was taken from here: http://jblevins.org/projects/mt

This code is free to be used.
License is under its license file.
