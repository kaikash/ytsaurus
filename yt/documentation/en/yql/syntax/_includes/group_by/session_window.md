---
vcsPath: ydb/docs/ru/core/yql/reference/yql-core/syntax/_includes/group_by/session_window.md
sourcePath: ydb/docs/ru/core/yql/reference/yql-core/syntax/_includes/group_by/session_window.md
---
## GROUP BY ... SessionWindow() {#session-window}

YQL supports grouping by session. To standard expressions in `GROUP BY`, you can add a special `SessionWindow` function:

```sql
SELECT
  user,
  session_start,
  SessionStart() AS same_session_start, -- the same as session_start
  COUNT(*) AS session_size,
  SUM(value) AS sum_over_session,
FROM my_table
GROUP BY user, SessionWindow(<time_expr>, <timeout_expr>) AS session_start
```

The following happens in this case:

1) The input table is partitioned by the grouping keys specified in `GROUP BY`, ignoring SessionWindow (in this case, it's based on `user`).
   If `GROUP BY` includes nothing more than SessionWindow, then the input table gets into one partition
2) Each partition is split into disjoint subsets of rows (sessions).
   For this, the partition is sorted in the ascending order of the `time_expr` expression.
   The session limits are drawn between neighboring items of the partition, that differ in their `time_expr` values by more than `timeout_expr`
3) The sessions obtained in this way are the final partitions on which aggregate functions are calculated.

The SessionWindow() key column (in the example, it's `session_start`) has the value "the minimum `time_expr` in the session".
Also, if SessionWindow() is present in `GROUP BY`, you can use the special
`SessionStart` aggregate function.

An extended version of SessionWindow with four arguments is also supported:

`SessionWindow(<order_expr>, <init_lambda>, <update_lambda>, <calculate_lambda>)`

Where:
* `<order_expr>` is an expression based on which the original partition is sorted
* `<init_lambda>` is a lambda function for initializing the session calculation status. It has the signature `(TableRow())->State`. It's called once for the first (following the sorting order) element of the source partition
* `<update_lambda>` is a lambda function for refreshing the session calculation state and defining session limits. It has the signature `(TableRow(), State)->Tuple<Bool, State>`. It's called for every item of the source partition, except the first one. The new value of state is calculated based on the current row of the table and the previous state. If the first item in the return tuple is `True`, then a new session starts from the _current_ row. The new session key is obtained by applying `<calculate_lambda>` to the second tuple element.
* `<calculate_lambda>`: A lambda function for calculating the session key (the "value" of SessionWindow() that is also accessible via SessionStart()). The function has the signature `(TableRow(), State)->SessionKey`. It's called in the first partition element (after `<init_lambda>`) and on those elements for which `<update_lambda>` returned`True` as the first tuple element. It's worth noting that to start a new session, `<calculate_lambda>` must return a value that is different from the previous session key. Sessions having the same keys are not merged. For example, if `<calculate_lambda>` sequentially returns `0, 1, 0, 1`, they will be four different sessions.

Using the extended version of SessionWindow, you can, for example, do the following: divide a partition into sessions, as in the SessionWindow use case with two arguments, but with the maximum session length limited by a certain constant:

**Example**
```sql
$max_len = 1000; -- maximum session length
$timeout = 100; -- timeout (timeout_expr in a simplified variant of SessionWindow)

$init = ($row) -> (AsTuple($row.ts, $row.ts)); -- session state - tuple of 1) values of temporary ts column in the first session row and 2) in the current row
$update = ($row, $state) -> {
  $is_end_session = $row.ts - $state.0 > $max_len OR $row.ts - $state.1 > $timeout;
  $new_state = AsTuple(IF($is_end_session, $row.ts, $state.0), $row.ts);
  return AsTuple($is_end_session, $new_state);
};
$calculate = ($row, $state) -> ($row.ts);
SELECT
  user,
  session_start,
  SessionStart() AS same_session_start, -- the same as session_start
  COUNT(*) AS session_size,
  SUM(value) AS sum_over_session,
FROM my_table
GROUP BY user, SessionWindow(ts, $init, $update, $calculate) AS session_start
```

You can use SessionWindow in GROUP BY only once.
