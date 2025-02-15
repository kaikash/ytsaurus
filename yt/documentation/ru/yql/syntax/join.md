---
vcsPath: yql/docs_yfm/docs/ru/yql-product/syntax/join.md
sourcePath: yql-product/syntax/join.md
---
{% include [x](_includes/join.md) %}


## Стратегии выполнения JOIN в {{product-name}}

### Введение


В стандартном SQL поддерживается следующий синтаксис `JOIN`:
``` yql
SELECT
  ...
FROM T1 <Join_Type> JOIN T2
ON F(T1, T2);
```

где `F(T1, T2)` - произвольный предикат зависящий от колонок обоих таблиц `T1, T2`.
В YQL подерживается только частный случай – когда предикат `F` сепарабельный, т.е имеет следующий вид:

``` yql
SELECT
  ...
FROM T1 <Join_Type> JOIN T2
ON F1(T1) = G1(T2) AND F2(T1) = G2(T2) AND ...;
```

Такая структура предиката позволяет эффективно реализовать `JOIN` в рамках концепции map-reduce.

В YQL также как и в стандартном SQL можно сделать несколько `JOIN` в одном SELECT:
``` yql
SELECT
  ...
FROM
T1 <Join_Type> JOIN T2 ON F1(T1) = G1(T2) AND F2(T1) = G2(T2) AND ...
   <Join_Type> JOIN T3 ON H1(T1,T2) = J1(T3) AND H2(T1,T2) = J2(T3) AND ...;
```

В настоящий момент такие `JOIN` выполняются последовательно и именно в том порядка, в котором написано в запросе.
Единственным исключением является стратегия StarJoin.

### Вычисление ключей JOIN

Выполнение `JOIN` начинается с вычислениия ключей и сохранения из значений в отдельную колонку.
Такое преобразования происходит еще на уровне SQL парсера и является общиим для всех бэкендов (YDB, {{product-name}}, DQ и т.п.)

Фактически запрос
``` yql
SELECT
  ...
FROM T1 <Join_Type> JOIN T2
ON F1(T1) = G1(T2) AND F2(T1) = G2(T2) AND ...;
```

преобразуется в
``` yql
SELECT
...
FROM (
    SELECT t.*,
           F1(...) as _yql_join_key1,
           F2(...) as _yql_join_key2, ...
    FROM T1 as t
) as t1
<Join_Type> JOIN (
     SELECT t.*,
            G1(...) as _yql_join_key1,
            G2(...) as _yql_join_key2, ...
    FROM T2 as t
) as t2
ON t1._yql_join_key1 = t2._yql_join_key1 AND t1._yql_join_key2 = t2._yql_join_key2 AND ...;
```

### Приведение ключей к простому общему типу

Данная стадия уже является специфичной для {{product-name}}. В ней ключевые колонки с обоих сторон приводятся к одинаковому простому типу.

Запрос
``` yql
SELECT
  ...
FROM T1 as t1 <Join_Type> JOIN T2 as t2
ON t1.key1 = t2.key1 AND t1.key2 = t2.key2 AND ...;
```

преобразуется в
``` yql
SELECT
...
FROM (
    SELECT t.*,
           CastToCommonKeyType(key1) as _yql_join_key1,
           CastToCommonKeyType(key2) as _yql_join_key2,
    FROM T1 as t
) as t1
<Join_Type> JOIN (
     SELECT t.*,
           CastToCommonKeyType(key1) as _yql_join_key1,
           CastToCommonKeyType(key2) as _yql_join_key2,
    FROM T2 as t
) as t2
ON t1._yql_join_key1 = t2._yql_join_key1 AND t1._yql_join_key2 = t2._yql_join_key2 AND ...;
```

Приведение к общему типу необходимо для корректной работы map-reduce по ключам родственных, но разных типов.
Например, для ключей типа `Int32` и `Uint32`, общим типом будет `Optional<Int32>`.
Если конвертацию в общий тип не сделать и оставить исходные колонки в качестве ключевых для map-reduce операций,
то {{product-name}} будет рассматривать ключи -1 и 4294967295 как равные.

Такая конвертация нужна не всегда - например ключи типов Int32 и Optional<Int32> работают корректно.

Дополнительно, ключи сложного типа (все что сложнее Optional от [простого типа](../types/primitive.md)))
после каста в общий тип еще и конвертируются в строку:

```yql

if (
    YQL::HasNulls(casted_key), -- если где-то в ключе встречается null
    null,                      -- то конвертируем значение в null строкового типа (null в SQL не равен никакому значению, в том числа самому себе)
    StablePickle(casted_key),  -- иначе сериализуем значение в строковое представление
)

```

Такая конвертаця нужна, поскольку ключи сложных типов не поддерживаются в качестве ключей reduce операций в {{product-name}}.

Таким образом, после всех конвертаций, мы получаем c обоих сторон `JOIN` ключи попарно однакового простого типа (с точностью до Optional).

### Базовая стратегия JOIN (aka CommonJoin)

Базовая стратегия `JOIN` выбирается в тех случаях, когда не удается применить по каким-либо причнам остальные стратегии `JOIN`.
Эта стратегия поддерживает все типы `JOIN`, включая `CROSS JOIN` и реализуется через одну MapReduce операцию.

При этом в map стадии происходит:

1) приведение ключей к простому общему типу
2) при наличии модификатотора ANY одинаковые ключи "прореживаются" отдельным оконным фильтром – на окне некоторого размера (сотни мегабайт) детектятся строки с одинаковыми ключами и дубликаты отфильтровываются
3) обработка нуллов в ключах. При этом для `INNER JOIN` нуллы с обоих сторон отфильтровываются,
   а для `LEFT/RIGHT/FULL JOIN` строки с нулевыми ключами идут в отдельную выходную таблицу сразу из map стадии

Из map стадии строки с однаковым ключем попадают в одну {{product-name}} reduce джобу, в которой собственно и происходиит `JOIN`.
Если необходимо, то результирующая таблца из reduce стадии объединяется с выходными таблцам из map стадии с помощью отдельной {{product-name}} Merge операции.

Чтобы выполнить `CROSS JOIN` (в котором ключей нет), на map стадии всем строчкам обоих входных таблиц назначается одинаковый ключ 0.

### Стратегия LookupJoin

Данная стратегия срабатывает, когда одна из таблиц сортирована по ключам `JOIN`, а вторая имеет очень малый размер (меньше ~900 строк).

{% note info %}

Здесь и далее таблица называется _сортированной по ключам JOIN_, если список ключей `JOIN` является префиксом ключей сортировки для некоторого порядка ключей `JOIN`.
Например, таблица с ключами `JOIN` `b, a` и сортировкой по `a, b, c` является сортированной по ключам `JOIN`.

{% endnote %}


LookupJoin поддерживается для следующих типов JOIN:
* `INNER` (малая таблица может быть с произвольной стороны)
* `LEFT SEMI` (малая таблца справа)
* `RIGHT SEMI` (малая таблица слева)

Стратегия LookupJoin реализуется через одну Map операцию по большой таблице, при этом малая таблица загружается в память.
Типы ключей при этом не обязательно должны совпадать – ключи малой таблицы кастятся к типу ключей в большой таблице.

В отличии от стратегии MapJoin (смотрите ниже), в LookupJoin значения ключей `JOIN` из малой таблицы попадают в
настройку `ranges` в YPath большой таблицы.<!--(../../user-guide/storage/ypath.md#known_attributes)--> Таким образом из большой таблицы вычитываются только строки с ключами `JOIN`, которые есть в малой таблице.

LookupJoin является наиболее эффективной стратегией `JOIN`, но налагает самые жесткие условия на типы `JOIN`
(они должны быть "фильтрующими" по большой таблице) и на размер малой таблицы (ключи должны "влезать" в максимально допустимое число `ranges` в YPath).
Кроме того, в LookupJoin не поддерживается `ANY` на стороне большой таблицы.

Настройки (PRAGMA) для стратегии:

| Название | Описание |
| --- | --- |
| [`yt.LookupJoinLimit`](pragma.md#lookupjoinlimit) | Максимальный размер малой таблицы в байтах (не более 10М) |
| [`yt.LookupJoinMaxRows`](pragma.md#lookupjoinmaxrows) | Максимальный размер малой таблицы в строках (не более 1000)|

Установка любого из этих значений в 0 приводит к отключению LookupJoin стратегии.

### Стратегия SortedJoin (aka MergeJoin)

Данная стратегия срабатывает, когда обе таблицы сортированы по ключам `JOIN`.
При этом ключи `JOIN` должны быть совпадать по типам с точностью до Optional на верхнем уровне.

Если сортирована только одна таблица, а размер другой не превышает `yt.JoinMergeUnsortedFactor * <размер сортированной таблицы>`,
то стратегия SortedJoin также выбирается, при этом несортированная таблица сортируется отдельной {{product-name}} операцией.
Значение настройки [`yt.JoinMergeUnsortedFactor`](pragma.md#ytjoinmergeunsortedfactor) по умолчанию составляет `0.2`.

Стратегия SortedJoin поддерживает все виды `JOIN` кроме `CROSS JOIN` и реализуется через одну операцию Reduce.
При этом, по возможности используется режим reduce с внешними таблицами.<!--(../user-guide/data-processing/operations/reduce.md#foreign_tables).-->
Кроме того, при уникальности ключей `JOIN` дополнительно включается настройка `enable_key_guarantee = false`.<!--(../user-guide/data-processing/operations/reduce.md#foreign_tables)-->

Стратегию SortedJoin можно выбрать принудительно через [SQL хинт](lexer.md#sql-hints):

```yql
SELECT * FROM T1 AS a JOIN /*+ merge() */ T2 AS b ON a.key = b.key;
```

В этом случае (если необходимо)
1) ключи `JOIN` будут приведены к общему типу
2) обе таблицы будут отсортированы по ключам `JOIN`

Настройки (PRAGMA) для стратегии:

| Название | Описание |
| --- | --- |
| [`yt.JoinMergeUnsortedFactor`](pragma.md#ytjoinmergeunsortedfactor)   | смотрите выше |
| [`yt.JoinMergeTablesLimit`](pragma.md#ytjoinmergetableslimit)   | Максимальное количество таблиц на входе `JOIN` (при использовании [RANGE,CONCAT](select.md#concat) и т.п.) |
| [`yt.JoinMergeUseSmallAsPrimary`](pragma.md#ytjoinmergeusesmallasprimary) | Влияет на выбор primary таблицы при выполнении Reduce операции |
| [`yt.JoinMergeForce`](pragma.md#ytjoinmergeforce) | Форсирует выбор SortedJoin стратегии для всех `JOIN` в запросе  |

Установка `yt.JoinMergeTablesLimit` в 0 отключает стратегию SortedJoin.

### Стратегия MapJoin

Данная стратегия срабатывает, если одна из входных таблиц достаточно маленькая (размером не более чем [`yt.MapJoinLimit`](pragma.md#ytmapjoinlimit)).
При этом меньшая таблица загружается в память (в виде словаря по ключам `JOIN`), а затем производится Map по большой таблице.

Данная стратегия поддерживает все виды `JOIN` (в том числе `CROSS`), но не выбирается если имеется `ANY` на большей стороне.

Уникальной особенностью MapJoin стратегии является возможность раннего выбора этой страттегии.
Т.е. когда малая входная таблица уже посчиталась и попадает под ограничения на размер, а большая таблица еще не готова.
В этом случае мы можем сразу выбрать MapJoin,
причем есть шанс что Map операция по большой таблице "склеится" с Map оперцией (например фильтром), которая эту большу таблиицу готовит.



Существует также шардированный варант MapJoin: малая таблица разбивается на [`yt.MapJoinShardCount`](pragma.md#ytmapjoinshardcount) частей
(каждая часть при этом не должна превышать `yt.MapJoinLimit`), каждая часть параллельно и независимо `JOIN`ится с большой таблицей через Map операцию,
и затем все полученные части объединяются через {{product-name}} Merge.

Шардированый MapJoin возможен только для некоторых типов `JOIN` (`INNER`,`CROSS`, `LEFT SEMI` при условии что малая таблиица справа ункальна).

Настройки (PRAGMA) для стратегии:

| Название | Описание |
| --- | --- |
| [`yt.MapJoinLimit`](pragma.md#ytmapjoinlimit)   | Максимальный размер представления в памяти меньшей стороны `JOIN` при котором выбирается стратегия MapJoin |
| [`yt.MapJoinShardCount`](pragma.md#ytmapjoinshardcount)   | Максимальное число шардов |
| [`yt.MapJoinShardMinRows`](pragma.md#ytmapjoinshardminrows) | Минимальное число строк в одном шарде |

Установка `yt.MapJoinLimit` в 0 отключает стратегию MapJoin.

### Стратегия StarJoin

Особенностью данной стратегии является то, что она позволяет выполнять сразу несколько последовательных `JOIN` через одну операцию Reduce.

Стратегия возможна, когда к одной ("главной") таблице последовательно через `INNER JOIN` или `LEFT JOIN` присоединяются таблицы-словари, причем:
1) из главной таблицы во всех `JOIN`ах используются одинаковые ключи
2) все таблиицы сортированы по ключам `JOIN`
3) таблицы-словари еще и уникальны по ключам `JOIN`

Настройки (PRAGMA) для стратегии:

| Название | Описание |
| --- | --- |
| [`yt.JoinEnableStarJoin`](pragma.md#ytjoinenablestarjoin) | Включает/отключает выбор стратегии StarJoin (включена по умолчаню)|

### Порядок выбора стратегий

При выполнении `JOIN` стратегии пробуются в определенном порядке и выбирается первая подходящая.
Порядок при этом следующий:

1) StarJoin
2) LookupJoin
3) OrderedJoin
4) MapJoin
5) CommonJoin (всегда возможна)


