# Ref

- https://www.elastic.co/guide/en/logstash/current/config-examples.html#using-conditionals
- https://www.elastic.co/guide/en/logstash/current/event-dependent-configuration.html

# 语法

## Field References

访问一个字段的语法： 

    [fieldname]

对于顶层字段，可以省略掉[]。

对于嵌套的字段，语法为：

    [top-level field][nested field]


### 示例

    {
      "agent": "Mozilla/5.0 (compatible; MSIE 9.0)",
      "ip": "192.168.24.44",
      "request": "/index.html"
      "response": {
        "status": 200,
        "bytes": 52353
      },
      "ua": {
        "os": "Windows 7"
      }
    }

- [ua][os]
- request

## sprintf format

语法:

    %{top_level_field}
    %{[top-level field][nested field]}

示例：

    "apache.%{[response][status]}"
    "/var/log/%{type}.%{+yyyy.MM.dd.HH}"

## Conditionals

支持 if, else if, else；且可嵌套。

    if EXPRESSION {
      ...
    } else if EXPRESSION {
      ...
    } else {
      ...
    }

条件表达式包括：比较判断、布尔逻辑，等。

比较操作符：

- equality: ==, !=, <, >, <=, >=
- regexp: =~, !~ (checks a pattern on the right against a string value on the left)
- inclusion: in, not in

布尔逻辑操作符：

- and, or, nand, xor

一元操作符：

    !

复合表达式：支持(...)

### 示例

    filter {
      if [action] == "login" {
        mutate { remove_field => "secret" }
      }
    }

    output {
      # Send production errors to pagerduty
      if [loglevel] == "ERROR" and [deployment] == "production" {
        pagerduty {
        ...
        }
      }
    }

    filter {
      if [foo] in [foobar] {
        mutate { add_tag => "field in field" }
      }
      if [foo] in "foo" {
        mutate { add_tag => "field in string" }
      }
      if "hello" in [greeting] {
        mutate { add_tag => "string in field" }
      }
      if [foo] in ["hello", "world", "foo"] {
        mutate { add_tag => "field in list" }
      }
      if [missing] in [alsomissing] {
        mutate { add_tag => "shouldnotexist" }
      }
      if !("foo" in ["hello", "world"]) {
        mutate { add_tag => "shouldexist" }
      }
    }

    output {
      if "_grokparsefailure" not in [tags] {
        elasticsearch { ... }
      }
    }

You can check for the existence of a specific field, but there’s currently no way to differentiate between a field that doesn’t exist versus a field that’s simply false. The expression if [foo] returns false when:

- [foo] doesn’t exist in the event,
- [foo] exists in the event, but is false, or
- [foo] exists in the event, but is null

For more complex examples, see Using Conditionals.

# Example1

工具日志对应的文件名，增加相应的label:

    input {
      file {
        path => "/tmp/*_log"
      }
    }

    filter {
      if [path] =~ "access" {
        mutate { replace => { type => "apache_access" } }
        ...
      } else if [path] =~ "error" {
        mutate { replace => { type => "apache_error" } }
      } else {
        mutate { replace => { type => "random_logs" } }
      }
    }

    ...

# Example 2

    output {
      if [type] == "apache" {
        if [status] =~ /^5\d\d/ {
          nagios { ...  }
        } else if [status] =~ /^4\d\d/ {
          elasticsearch { ... }
        }
        statsd { increment => "apache.%{status}" }
      }
    }


To tell nagios about any http event that has a 5xx status code, you first need to check the value of the type field. If it’s apache, then you can check to see if the status field contains a 5xx error. If it is, send it to nagios. If it isn’t a 5xx error, check to see if the status field contains a 4xx error. If so, send it to Elasticsearch. Finally, send all apache status codes to statsd no matter what the status field contains:

如果状态码是5xx，则nagios；如果是400，则es。
