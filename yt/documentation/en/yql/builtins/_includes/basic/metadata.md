---
vcsPath: ydb/docs/ru/core/yql/reference/yql-core/builtins/_includes/basic/metadata.md
sourcePath: ydb/docs/ru/core/yql/reference/yql-core/builtins/_includes/basic/metadata.md
---
## Access to the metadata of the current operation {#metadata}

When you run YQL operations via the web interface or HTTP API, you get access to the following data:

* `CurrentOperationId()`: The private ID of the operation.
* `CurrentOperationSharedId()`: The public ID of the operation.
* `CurrentAuthenticatedUser()`: The username of the current user.

**Signatures**
```
CurrentOperationId()->String
CurrentOperationSharedId()->String
CurrentAuthenticatedUser()->String
```

No arguments.

If this data is missing, for example, when you run operations in the embedded mode, the functions return an empty string.

**Examples**
```yql
SELECT
    CurrentOperationId(),
    CurrentOperationSharedId(),
    CurrentAuthenticatedUser();
```
