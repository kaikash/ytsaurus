---
vcsPath: ydb/docs/ru/core/yql/reference/yql-core/builtins/_includes/basic/pickle.md
sourcePath: ydb/docs/ru/core/yql/reference/yql-core/builtins/_includes/basic/pickle.md
---
## Pickle, Unpickle {#pickle}

`Pickle()` and `StablePickle()` serialize an arbitrary object into a sequence of bytes, if possible. Typical non-serializable objects are Callable and Resource. The serialization format is not versioned and can be used within a single query. For the Dict type, the StablePickle function pre-sorts the keys, and for Pickle, the order of dictionary elements in the serialized representation isn't defined.

`Unpickle()` is the inverse operation (deserialization), where with the first argument being the data type of the result and the second argument is the string with the result of `Pickle()` or `StablePickle()`.

**Signatures**
```
Pickle(T)->String
StablePickle(T)->String
Unpickle(Type<T>, String)->T
```

Examples:
```yql
SELECT *
FROM my_table
WHERE Digest::MurMurHash32(
        Pickle(TableRow())
    ) % 10 == 0; -- from practical viewpoint, it's better to use TABLESAMPLE

$buf = Pickle(123);
SELECT Unpickle(Int32, $buf);
```
