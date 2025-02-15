---
vcsPath: ydb/docs/ru/core/yql/reference/yql-core/syntax/_includes/upsert_into.md
sourcePath: ydb/docs/ru/core/yql/reference/yql-core/syntax/_includes/upsert_into.md
---
# UPSERT INTO

UPSERT (расшифровывается как UPDATE or INSERT) обновляет или добавляет множество строк в таблице на основании сравнения по первичному ключу. Отсутствующие строки добавляются. В присутствующих строках обновляются значения заданных столбцов, значения остальных столбцов остаются неизменными.

  Таблица по имени ищется в базе данных, заданной оператором [USE](../use.md).

`UPSERT` является единственной операцией модификации данных, которая не требует их предварительного чтения, за счет чего работает быстрее и дешевле других операций.

Сопоставление столбцов при использовании `UPSERT INTO ... SELECT` производится по именам. Используйте `AS` для получения колонки с нужным именем в `SELECT`.

**Примеры**

``` yql
UPSERT INTO my_table
SELECT pk_column, data_column1, col24 as data_column3 FROM other_table  
```

``` yql
UPSERT INTO my_table ( pk_column1, pk_column2, data_column2, data_column5 )
VALUES ( 1, 10, 'Some text', Date('2021-10-07')),
       ( 2, 10, 'Some text', Date('2021-10-08'))
```
