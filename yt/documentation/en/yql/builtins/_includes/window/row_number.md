---
vcsPath: ydb/docs/ru/core/yql/reference/yql-core/builtins/_includes/window/row_number.md
sourcePath: ydb/docs/ru/core/yql/reference/yql-core/builtins/_includes/window/row_number.md
---
## ROW_NUMBER {#row_number}

Row number within a [partition](../../../syntax/window.md#partition). Without arguments.

**Signature**
```
ROW_NUMBER()->Uint64
```


**Examples**
```yql
SELECT
    ROW_NUMBER() OVER w AS row_num
FROM my_table
WINDOW w AS (ORDER BY key);
```
