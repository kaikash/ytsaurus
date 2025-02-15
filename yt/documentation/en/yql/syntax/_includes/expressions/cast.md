---
vcsPath: ydb/docs/ru/core/yql/reference/yql-core/syntax/_includes/expressions/cast.md
sourcePath: ydb/docs/ru/core/yql/reference/yql-core/syntax/_includes/expressions/cast.md
---
## CAST {#cast}

Tries to cast the value to the specified type. The attempt may fail and return `NULL`. When used with numbers, it may lose precision or most significant bits.
For lists and dictionaries, it can either delete or replace with `NULL` the elements whose conversion failed.
For structures and tuples, it deletes elements that are omitted in the target type.
To learn more about conversions, see [here](../../../types/cast.md).

{% include [decimal_args](../../../_includes/decimal_args.md) %}

**Examples**

{% include [cast_examples](../../../_includes/cast_examples.md) %}
