---
vcsPath: ydb/docs/ru/core/yql/reference/yql-core/builtins/_includes/basic/current_tz.md
sourcePath: ydb/docs/ru/core/yql/reference/yql-core/builtins/_includes/basic/current_tz.md
---
## CurrentTz... {#current-tz}

`CurrentTzDate()`, `CurrentTzDatetime()`, and `CurrentTzTimestamp()`: Get the current date and/or time in the [IANA time zone](https://en.wikipedia.org/wiki/List_of_tz_database_time_zones) specified in the first argument. The result data type is specified at the end of the function name.

**Signatures**
```
CurrentTzDate(String, ...)->TzDate
CurrentTzDatetime(String, ...)->TzDatetime
CurrentTzTimestamp(String, ...)->TzTimestamp
```

The arguments that follow are optional and work the same as [RANDOM](#random).

**Examples**
```yql
SELECT CurrentTzDate("Europe/Moscow");
```
```yql
SELECT CurrentTzTimestamp("Europe/Moscow", TableRow()) FROM my_table;
```

## AddTimezone

Adding the time zone information to the date/time in UTC. In the result of `SELECT` or after `CAST`, a `String` will be subject to the time zone rules used to calculate the time offset.

**Signature**
```
AddTimezone(Date, String)->TzDate
AddTimezone(Date?, String)->TzDate?
AddTimezone(Datetime, String)->TzDatetime
AddTimezone(Datetime?, String)->TzDatetime?
AddTimezone(Timestamp, String)->TzTimestamp
AddTimezone(Timestamp?, String)->TzTimestamp?
```

Arguments:

1. Date: the type is `Date`/`Datetime`/`Timestamp`.
2. [IANA name of the time zone](https://en.wikipedia.org/wiki/List_of_tz_database_time_zones).

Result type: `TzDate`/`TzDatetime`/`TzTimestamp`, depending on the input data type.

**Examples**
```yql
SELECT AddTimezone(Datetime("2018-02-01T12:00:00Z"), "Europe/Moscow");
```

## RemoveTimezone

Removing the time zone data and converting the value to date/time in UTC.

**Signature**
```
RemoveTimezone(TzDate)->Date
RemoveTimezone(TzDate?)->Date?
RemoveTimezone(TzDatetime)->Datetime
RemoveTimezone(TzDatetime?)->Datetime?
RemoveTimezone(TzTimestamp)->Timestamp
RemoveTimezone(TzTimestamp?)->Timestamp?
```

Arguments:

1. Date: the type is `TzDate`/`TzDatetime`/`TzTimestamp`.

Result type: `Date`/`Datetime`/`Timestamp`, depending on the input data type.

**Examples**
```yql
SELECT RemoveTimezone(TzDatetime("2018-02-01T12:00:00,Europe/Moscow"));
```
