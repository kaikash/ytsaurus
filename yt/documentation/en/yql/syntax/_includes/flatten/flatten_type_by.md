---
vcsPath: ydb/docs/ru/core/yql/reference/yql-core/syntax/_includes/flatten/flatten_type_by.md
sourcePath: ydb/docs/ru/core/yql/reference/yql-core/syntax/_includes/flatten/flatten_type_by.md
---
### Specifying the container type {#flatten-by-specific-type}

To specify the type of container to convert to, you can use:

* `FLATTEN LIST BY`

   For `Optional<List<T>>`, the `FLATTEN LIST BY` operation will deploy the list and interpret `NULL` values as an empty list.
* `FLATTEN DICT BY`

   For `Optional<Dict<T>>`, the `FLATTEN DICT BY` operation will deploy a dictionary and interpret `NULL` values as an empty dictionary.
* `FLATTEN OPTIONAL BY`

   To filter the `NULL` values without serialization, specify the operation by using `FLATTEN OPTIONAL BY`.

**Examples**

```sql
SELECT
  t.item.0 AS key,
  t.item.1 AS value,
  t.dict_column AS original_dict,
  t.other_column AS other
FROM my_table AS t
FLATTEN DICT BY dict_column AS item;
```

```sql
SELECT * FROM (
    SELECT
        AsList(1, 2, 3) AS a,
        AsList("x", "y", "z") AS b
) FLATTEN LIST BY (a, b);
```

```yql
SELECT * FROM (
    SELECT
        "1;2;3" AS a,
        AsList("x", "y", "z") AS b
) FLATTEN LIST BY (String::SplitToList(a, ";") as a, b);
```
