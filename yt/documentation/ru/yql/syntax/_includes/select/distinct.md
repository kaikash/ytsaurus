---
vcsPath: ydb/docs/ru/core/yql/reference/yql-core/syntax/_includes/select/distinct.md
sourcePath: ydb/docs/ru/core/yql/reference/yql-core/syntax/_includes/select/distinct.md
---


## DISTINCT {#distinct}

Выбор уникальных строк.

{% note info %}

Применение `DISTINCT` к вычислимым значениям на данный момент не реализовано. С этой целью можно использовать подзапрос или выражение [`GROUP BY ... AS ...`](../../group_by.md).

{% endnote %}

**Пример**

``` yql
SELECT DISTINCT value -- только уникальные значения из таблицы
FROM my_table;
```

Также ключевое слово `DISTINCT` может использоваться для применения агрегатных функций только к уникальным значениям. Подробнее можно прочитать вдокументации по [GROUP BY](../../group_by.md).