
## На каких языках можно писать? { #lang }

На Spark можно писать на одном из трех языков: Python, Java и Scala.

## Когда использовать SPYT? { #what-to-do }

SPYT стоит выбрать в любом из следующих случаев:
- при разработке на Java с использованием MapReduce в {{product-name}};
- при оптимизации производительность пайплайна на {{product-name}} с двумя и более джойнами или группировками.

SPYT не стоит выбирать, если:
- существует необходимость в обработке более 10 ТБ данных в одной транзакции;
- процессинг сводится к единичным Map или MapReduce.

## Как получить доступ к SPYT? { #access }

1. Павести кластер Spark.
2. Использовать кластер Spark несколькими способами:
    * Писать код в [Jupyter](../spyt/API/spyt-jupyter.md).
    * Писать код на [Python](../spyt/API/spyt-python.md) и запускать на кластере.
    * Писать код на [Java](../spyt/API/spyt-java.md) и запускать на кластере.
    * Писать код на [Scala](../spyt/API/spyt-scala.md) и запускать на кластере.


