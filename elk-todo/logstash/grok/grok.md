Logstash - grok

# Ref

- [Grok filter plugin](https://www.elastic.co/guide/en/logstash/current/plugins-filters-grok.html)
- [oniguruma/doc/RE](https://github.com/kkos/oniguruma/blob/master/doc/RE)

# Key Points

pipeline使用stdin & stdout进行调试：

- input stdin: 在控制台输入待分析字符串
- output stdout: 直接查看分析结果

# Spring 1

首先使用最简单的配置文件，便于验证Logstash环境。

## conf(test1.conf)

    input {
        stdin {}
    }

    output {
        stdout { codec => rubydebug }
    }

## Run

    /your_dir/logstash-5.5.2/bin/logstash --path.settings /your_dir/logstash-grok/config -f /your_dir/logstash-grok/test1.conf 

这里不需要--config.reload.automatic来检查配置文件。

尝试在控制台上输入数据：

    <--- Enter
    {
        "@timestamp" => 2017-11-14T02:00:20.398Z,
          "@version" => "1",
              "host" => "hostname",
           "message" => ""
    }
    hello <--- Your Input
    {
        "@timestamp" => 2017-11-14T02:00:54.003Z,
          "@version" => "1",
              "host" => "hostname",
           "message" => "hello"
    }

Ctrl + C 停止运行。

# Sprint 2

增加filter+grok，对日志进行解析。这里以解析日期字符串为例。

- 日期字符串: 2017-11-14T10:04:09,167
- 要求提取出: year, month, day, hour, minute, second, msecond

## conf(test2.conf)

    input {
        stdin {}
    }

    filter {
        # 2017-11-14T10:04:09,167
        grok {
            match => { 
                "message" => "^(?<year>\d{4})-(?<month>\d{2})-(?<day>\d{2})T(?<hour>\d{2}):(?<minute>\d{2}):(?<second>\d{2}),(?<msecond>\d+)$"
            }
        }
    }

    output {
        stdout { codec => rubydebug }
    }

## Run

    /your_dir/logstash-5.5.2/bin/logstash --path.settings /your_dir/logstash-grok/config -f /your_dir/logstash-grok/test2.conf 

    <--- Enter
    {
        "@timestamp" => 2017-11-14T02:13:57.297Z,
          "@version" => "1",
              "host" => "hostname",
           "message" => "",
              "tags" => [
            [0] "_grokparsefailure" <--- Will be explained later.
        ]
    }
    2017-11-14T10:04:09,167 <--- Your Input
    {
        "@timestamp" => 2017-11-14T02:14:00.096Z,
           "msecond" => "167",
             "month" => "11",
              "hour" => "10",
              "year" => "2017",
          "@version" => "1",
              "host" => "hostname",
           "message" => "2017-11-14T10:04:09,167",
               "day" => "14",
            "minute" => "04",
            "second" => "09"
    }

# grok语法

grok就是一套正则匹配的[语法规则](http://grokconstructor.appspot.com/RegularExpressionSyntax.txt)。如果对正则语法不是很熟悉，则可以借助调试工具[Grok Constructor](http://grokconstructor.appspot.com/do/match)。

## Grok Constructor

### Basic Usage

在"Some log lines you want to match..."的地方输入待解析的字符串：

    2017-11-14T10:04:09,167

在"The (unquoted!) pattern that should match all logfile lines."的地方输入模式串：

    ^(?<year>\d{4})-(?<month>\d{2})-(?<day>\d{2})T(?<hour>\d{2}):(?<minute>\d{2}):(?<second>\d{2}),(?<msecond>\d+)$

然后'Go'，在最下面就可以看到匹配结果。

### Debuger

如果模式串不对，那么会给出详细的出错点。比如把 month 和 day 之间的'-'去掉，会提示如下：

    2017-11-14T10:04:09,167
    NOT MATCHED. The longest regex prefix matching the beginning of this line is as follows:
    prefix  ^(?<year>\d{4})-(?<month>\d{2})
    year    2017
    month   11
    after match:    -14T10:04:09,167

### Multiple Match

在原始字符串中，可以写入多行待匹配的字符串，最后会显示每条日志的匹配结果。

### Sub Pattern Definition

可以为模式定义一个名字。

You can also provide a library of some additional grok patterns in the same format as the pattern files linked above. --- 在这里输入下面的内容：

    YEARX \d{4}
    MONTHX \d{2}
    DAYX \d{2}
    HOURX \d{2}
    MINUTEX \d{2}
    SECONDX \d{2}
    MSECONDX \d+

注意每行后面不要有多余的空格，否则不匹配。

现在把模式串改为：

    ^%{YEAR:year}-%{MONTH:month}-%{DAY:day}T%{HOUR:hour}:%{MINUTE:minute}:%{SECOND:second},%{MSECOND:msecond}$

### grok patterns

在上面的例子中，YEAR等后面加了一个加扰字符X。用这种奇怪的名字，是为了避免和grok预定义的模式名称发生冲突。在匹配的时候，grok优先用[grok pattern](http://grokconstructor.appspot.com/groklib/grok-patterns)。

拷贝部分：

    # Months: January, Feb, 3, 03, 12, December
    MONTH \b(?:[Jj]an(?:uary|uar)?|[Ff]eb(?:ruary|ruar)?|[Mm](?:a|ä)?r(?:ch|z)?|[Aa]pr(?:il)?|[Mm]a(?:y|i)?|[Jj]un(?:e|i)?|[Jj]ul(?:y)?|[Aa]ug(?:ust)?|[Ss]ep(?:tember)?|[Oo](?:c|k)?t(?:ober)?|[Nn]ov(?:ember)?|[Dd]e(?:c|z)(?:ember)?)\b
    MONTHNUM (?:0?[1-9]|1[0-2])
    MONTHNUM2 (?:0[1-9]|1[0-2])
    MONTHDAY (?:(?:0[1-9])|(?:[12][0-9])|(?:3[01])|[1-9])

    # Days: Monday, Tue, Thu, etc...
    DAY (?:Mon(?:day)?|Tue(?:sday)?|Wed(?:nesday)?|Thu(?:rsday)?|Fri(?:day)?|Sat(?:urday)?|Sun(?:day)?)

    # Years?
    YEAR (?>\d\d){1,2}
    HOUR (?:2[0123]|[01]?[0-9])
    MINUTE (?:[0-5][0-9])
    # '60' is a leap second in most time standards and thus is valid.
    SECOND (?:(?:[0-5]?[0-9]|60)(?:[:.,][0-9]+)?)
    
如果在前面的调试中，取名MONTH，那么就会匹配失败。原因就在于grok使用了grok pattern中的MONTH定义，即Jan这种定义，而不是数字。

实际使用grok的时候，需要首先查询grok已经提供的名字，然后再定义自己的一套模式库。

### 提取匹配结果

grok中，提取匹配结果的两种形式：

    %{YEAR:year}
    (?<year>\d{4})

第一种花括号形式的，是针对有名模式；第二种圆括号针对原始正则模式串。即语法形式为：

    %{PATTERN_NAME:VAR_NAME}
    (?<VAR_NAME>RAW_REG_EXPRESS)

如果只匹配，但不要将匹配结果赋值到变量中，那么直接省略掉VAR_NAME部分即可：

    %{PATTERN_NAME}
    RAW_REG_EXPRESS

注意第二种不要圆括号，不要'?'。

# Sprint 3

现在用[grok-patters](http://grokconstructor.appspot.com/groklib/grok-patterns)优化pipeline配置文件。

## conf(test3.conf)

    input {
        stdin {}
    }

    filter {
        # 2017-11-14T10:04:09,167
        grok {
            match => { 
                "message" => "^%{YEAR:year}-%{MONTHNUM:month}-%{MONTHDAY:day}T%{HOUR:hour}:%{MINUTE:minute}:%{SECOND:second},(?<msecond>\d+)$"
            }
        }
    }

    output {
        stdout { codec => rubydebug }
    }

## Run

    <--- Enter
    {
        "@timestamp" => 2017-11-14T03:26:54.909Z,
          "@version" => "1",
              "host" => "hostname",
           "message" => "",
              "tags" => [
            [0] "_grokparsefailure"
        ]
    }
    2017-11-14T10:04:09,167 <--- Your Input
    {
        "@timestamp" => 2017-11-14T03:27:00.796Z,
           "msecond" => "167",
             "month" => "11",
              "hour" => "10",
              "year" => "2017",
          "@version" => "1",
              "host" => "hostname",
           "message" => "2017-11-14T10:04:09,167",
               "day" => "14",
            "minute" => "04",
            "second" => "09"
    }

# Sprint 4

现在考虑数据类型的问题。

缺省情况下，匹配结构都是字符串形式。也可以指定要转化成什么数据类型，——只支持int & float两种类型。

## conf(test4.conf)

    input {
        stdin {}
    }

    filter {
        # 2017-11-14T10:04:09,167
        grok {
            match => { 
                "message" => "^%{YEAR:year}-%{MONTHNUM:month}-%{MONTHDAY:day}T%{HOUR:hour}:%{MINUTE:minute}:%{SECOND:second:int},(?<msecond:int>\d+)$"
            }
        }
    }

    output {
        stdout { codec => rubydebug }
    }

修改点：

    %{SECOND:second:int}
    (?<msecond:int>\d+)

## Run

    {
        "@timestamp" => 2017-11-14T04:00:56.310Z,
          "@version" => "1",
              "host" => "hostname",
           "message" => "",
              "tags" => [
            [0] "_grokparsefailure"
        ]
    }
    2017-11-14T10:04:09,167
    {
        "@timestamp" => 2017-11-14T04:01:09.892Z,
             "month" => "11",
              "hour" => "10",
              "year" => "2017",
          "@version" => "1",
              "host" => "hostname",
           "message" => "2017-11-14T10:04:09,167",
               "day" => "14",
               "int" => "167", <--- field_name & result都不是预期值
            "minute" => "04",
            "second" => 9  <--- 整数
    }

在grok filter文档中，只提到了命名模式的类型转换。因此，需要接下来介绍的模式命名。

# Sprint 5

## pattern_definitions

    Value type is hash
    Default value is {}
    A hash of pattern-name and pattern tuples defining custom 
    patterns to be used by the current filter. Patterns matching 
    existing names will override the pre-existing definition. 
    Think of this as inline patterns available just for this 
    definition of grok

file my_patterns:

    MSECOND \d{3}

## conf(test5.conf)

    input {
        stdin {}
    }

    filter {
        # 2017-11-14T10:04:09,167
        grok {
            pattern_definitions => {
                "MSECOND" => "\d{3}" 
            }
            match => { 
                "message" => "^%{YEAR:year}-%{MONTHNUM:month}-%{MONTHDAY:day}T%{HOUR:hour}:%{MINUTE:minute}:%{SECOND:second:int},%{MSECOND:msecond:int}$"
            }
        }
    }

    output {
        stdout { codec => rubydebug }
    }

主要修改点：

- 增加了pattern_definitions
- match中使用了pattern_difinitions中定义的模式名称

## Result

    2017-11-14T10:04:09,167
    {
        "@timestamp" => 2017-11-14T05:10:11.102Z,
           "msecond" => 167,  <--- Correct!
             "month" => "11",
              "hour" => "10",
              "year" => "2017",
          "@version" => "1",
              "host" => "hostname",
           "message" => "2017-11-14T10:04:09,167",
               "day" => "14",
            "minute" => "04",
            "second" => 9 <--- Correct as before!
    }

# Sprint 6

尽管可以在grok-pattern_definitions中定义模式，但考虑到重用性，我们进一步把模式定义放到一个公共文件中，即这里用到的patterns_dir属性。

## patterns_dir

    Value type is array
    Default value is []
    Logstash ships by default with a bunch of patterns, so you 
    don’t necessarily need to define this yourself unless you 
    are adding additional patterns. You can point to multiple 
    pattern directories using this setting. Note that Grok will 
    read all files in the directory matching the patterns_files_glob 
    and assume it’s a pattern file (including any tilde backup files).
    //
        patterns_dir => ["/opt/logstash/patterns", "/opt/logstash/extra_patterns"]
    //
    Pattern files are plain text with format:
    //
        NAME PATTERN
    //
    For example:
    //
        NUMBER \d+
    The patterns are loaded when the pipeline is created.

## patterns_files_glob

    Value type is string
    Default value is "*"
    Glob pattern, used to select the pattern files in the directories 
    specified by patterns_dir

## conf(test6.conf)

    input {
        stdin {}
    }

    filter {
        # 2017-11-14T10:04:09,167
        grok {
            patterns_dir => ["/your_dir/logstash-grok/my_patterns"]
            match => { 
                "message" => "^%{YEAR:year}-%{MONTHNUM:month}-%{MONTHDAY:day}T%{HOUR:hour}:%{MINUTE:minute}:%{SECOND:second:int},%{MSECOND:msecond:int}$"
            }
        }
    }

    output {
        stdout { codec => rubydebug }
    }

修改点:

    patterns_dir => ["/your_dir/logstash-grok/my_patterns"]

# Sprint 7

时间表示可能有多种形式，如：

    2017-11-14T10:04:09,167
    2017-11-14 10:04:09,167
    2017-11-14 10:04:09.167

因此，在filter的时候需要支持以上形式。

## patterns_definition(my_patterns)

    MSECOND \d{3}

    DATETIME1 %{YEAR:year:int}-%{MONTHNUM:month:int}-%{MONTHDAY:day:int}T%{HOUR:hour:int}:%{MINUTE:minute:int}:%{SECOND:second:int},%{MSECOND:msecond:int}
    DATETIME2 %{YEAR:year:int}-%{MONTHNUM:month:int}-%{MONTHDAY:day:int}\s%{HOUR:hour:int}:%{MINUTE:minute:int}:%{SECOND:second:int},%{MSECOND:msecond:int}
    DATETIME3 %{YEAR:year:int}-%{MONTHNUM:month:int}-%{MONTHDAY:day:int}\s%{HOUR:hour:int}:%{MINUTE:minute:int}:%{SECOND:second:int}\.%{MSECOND:msecond:int}

    DATETIME_ALL %{DATETIME2}|%{DATETIME1}|%{DATETIME3}
    
## conf(test7.conf)

    input {
        stdin {}
    }

    filter {
        # 2017-11-14T10:04:09,167
        # 2017-11-14 10:04:09,167
        # 2017-11-14 10:04:09.167
        grok {
            patterns_dir => ["/your_dir/logstash-grok/my_patterns"]
            match => { "message" => "^%{DATETIME1}$" }
            match => { "message" => "^%{DATETIME2}$" }
            match => { "message" => "^%{DATETIME3}$" }
        }
    }

    output {
        stdout { codec => rubydebug }
    }

## Run

    2017-11-14T10:04:09,167 <--- Your Input
    {
        "@timestamp" => 2017-11-14T05:36:52.592Z,
           "msecond" => 167,
             "month" => 11,
              "hour" => 10,
              "year" => 2017,
          "@version" => "1",
              "host" => "hostname",
           "message" => "2017-11-14T10:04:09,167",
               "day" => 14,
            "minute" => 4,
            "second" => 9
    }
    2017-11-14 10:04:09,167 <--- Your Input
    {
        "@timestamp" => 2017-11-14T05:37:01.679Z,
           "msecond" => 167,
             "month" => 11,
              "hour" => 10,
              "year" => 2017,
          "@version" => "1",
              "host" => "hostname",
           "message" => "2017-11-14 10:04:09,167",
               "day" => 14,
            "minute" => 4,
            "second" => 9
    }
    2017-11-14 10:04:09.167 <--- Your Input
    {
        "@timestamp" => 2017-11-14T05:37:10.511Z,
           "msecond" => 167,
             "month" => 11,
              "hour" => 10,
              "year" => 2017,
          "@version" => "1",
              "host" => "hostname",
           "message" => "2017-11-14 10:04:09.167",
               "day" => 14,
            "minute" => 4,
            "second" => 9
    }

# Sprint 8

Sprint 7的等价形式：

## conf(test8.conf)

    input {
        stdin {}
    }

    filter {
        # 2017-11-14T10:04:09,167
        # 2017-11-14 10:04:09,167
        # 2017-11-14 10:04:09.167
        grok {
            patterns_dir => ["/your_dir/logstash-grok/my_patterns"]
            match => { "message" => "^%{DATETIME_ALL}$" }
        }
    }

    output {
        stdout { codec => rubydebug }
    }

## Run

    2017-11-14T10:04:09,167
    {
        "@timestamp" => 2017-11-14T05:58:19.287Z,
           "msecond" => 167,
             "month" => 11,
              "hour" => 10,
              "year" => 2017,
          "@version" => "1",
              "host" => "hostname",
           "message" => "2017-11-14T10:04:09,167",
               "day" => 14,
            "minute" => 4,
            "second" => 9
    }
    2017-11-14 10:04:09,167
    {
        "@timestamp" => 2017-11-14T05:58:25.821Z,
           "msecond" => "167",
             "month" => "11",
              "hour" => "10",
              "year" => "2017",
          "@version" => "1",
              "host" => "hostname",
           "message" => "2017-11-14 10:04:09,167",
               "day" => "14",
            "minute" => "04",
            "second" => "09"
    }
    2017-11-14 10:04:09.167
    {
        "@timestamp" => 2017-11-14T05:58:31.981Z,
           "msecond" => "167",
             "month" => "11",
              "hour" => "10",
              "year" => "2017",
          "@version" => "1",
              "host" => "hostname",
           "message" => "2017-11-14 10:04:09.167",
               "day" => "14",
            "minute" => "04",
            "second" => "09"
    }

只有符合DATETIME_ALL的第一种pattern（这里是DATETIME1），其数据类型才符合预期，其他两种情况都不行。

直接在conf中，如下定义也不行：

    match => { "message" => "^%{DATETIME1}|%{DATETIME2}|%{DATETIME3}$" }

接下来用mutate插件来解决这个问题。

# Sprint 9

mutate插件可以做数据转换。

## Ref

- [Mutate Filter Plugin](https://www.elastic.co/guide/en/logstash/current/plugins-filters-mutate.html)

## Install

    bin/logstash-plugin install logstash-filter-mutate

## patterns_definition(my_patterns2)

因为有mutate专门做数据类型转换，所以在pattern definitions中就不需要:int了。修改如下：

    MSECOND \d{3}

    DATETIME1 %{YEAR:year}-%{MONTHNUM:month}-%{MONTHDAY:day}T%{HOUR:hour}:%{MINUTE:minute}:%{SECOND:second},%{MSECOND:msecond}
    DATETIME2 %{YEAR:year}-%{MONTHNUM:month}-%{MONTHDAY:day}\s%{HOUR:hour}:%{MINUTE:minute}:%{SECOND:second},%{MSECOND:msecond}
    DATETIME3 %{YEAR:year}-%{MONTHNUM:month}-%{MONTHDAY:day}\s%{HOUR:hour}:%{MINUTE:minute}:%{SECOND:second}\.%{MSECOND:msecond}

    DATETIME_ALL %{DATETIME1}|%{DATETIME2}|%{DATETIME3}

## conf(test9.conf)

    input {
        stdin {}
    }

    filter {
        # 2017-11-14T10:04:09,167
        # 2017-11-14 10:04:09,167
        # 2017-11-14 10:04:09.167
        grok {
            patterns_dir => ["/your_dir/logstash-grok/my_patterns2"]
            match => { "message" => "^%{DATETIME_ALL}$" }
        }

        mutate {
            convert => {
                "year" => "integer"
                "month" => "integer"
                "day" => "integer"
                "hour" => "integer"
                "minute" => "integer"
                "second" => "integer"
                "msecond" => "integer"
            }
        }
    }

    output {
        stdout { codec => rubydebug }
    }

## Run

    2017-11-14T10:04:09,167
    {
        "@timestamp" => 2017-11-14T07:14:42.808Z,
           "msecond" => 167,
             "month" => 11,
              "hour" => 10,
              "year" => 2017,
          "@version" => "1",
              "host" => "hostname",
           "message" => "2017-11-14T10:04:09,167",
               "day" => 14,
            "minute" => 4,
            "second" => 9
    }
    2017-11-14 10:04:09,167
    {
        "@timestamp" => 2017-11-14T07:14:49.527Z,
           "msecond" => 167,
             "month" => 11,
              "hour" => 10,
              "year" => 2017,
          "@version" => "1",
              "host" => "hostname",
           "message" => "2017-11-14 10:04:09,167",
               "day" => 14,
            "minute" => 4,
            "second" => 9
    }
    2017-11-14 10:04:09.167
    {
        "@timestamp" => 2017-11-14T07:14:55.959Z,
           "msecond" => 167,
             "month" => 11,
              "hour" => 10,
              "year" => 2017,
          "@version" => "1",
              "host" => "hostname",
           "message" => "2017-11-14 10:04:09.167",
               "day" => 14,
            "minute" => 4,
            "second" => 9
    }

