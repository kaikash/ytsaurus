---
vcsPath: ydb/docs/ru/core/yql/reference/yql-core/syntax/_includes/expressions/is-distinct-from.md
sourcePath: ydb/docs/ru/core/yql/reference/yql-core/syntax/_includes/expressions/is-distinct-from.md
---
## IS \[NOT\] DISTINCT FROM {#is-distinct-from}

Comparing of two values. Unlike regular [comparison operators](#comparison-operators), NULLs are considered equal to each other.
More precisely, the comparison is carried out according to the following rules:
1) `IS DISTINCT FROM`/`IS NOT DISTINCT FROM` operators are defined for those (and only those) arguments for which `!=` and `=` operators are defined.
2) The result of `IS NOT DISTINCT FROM` is equal to the logical negation of the `IS DISTINCT FROM` result for these arguments.
3) If the result of the `==` operator is not equal to zero for some arguments, then it is equal to the result of the `IS NOT DISTINCT FROM` operator for the same arguments.
4) If both arguments are empty `Optional` or `NULL`s, then the value of `IS NOT DISTINCT FROM` is `True`.
5) The result of `IS NOT DISTINCT FROM` for an empty `Optional` or `NULL` and filled-in `Optional` or non-`Optional` value is `False`.

For values of composite types, these rules are used recursively.