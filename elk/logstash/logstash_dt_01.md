# Overview

接下来以datetime为例，介绍Logstash的一些功能：

- add fileds
- remove fields
- grok parse failure
- date filter
- date parse failure
- rename
- conditional

本文首先以grok-pattern定义的pattern执行基本的匹配。

# Ref

- [Grok filter plugin](https://www.elastic.co/guide/en/logstash/current/plugins-filters-grok.html)
- [oniguruma/doc/RE](https://github.com/kkos/oniguruma/blob/master/doc/RE)
- [grok语法规则](http://grokconstructor.appspot.com/RegularExpressionSyntax.txt)
- [调试工具Grok Constructor](http://grokconstructor.appspot.com/do/match)
- grok-patterns: https://github.com/logstash-plugins/logstash-patterns-core/blob/master/patterns/grok-patterns

# grok-pattern

[grok-pattern](https://github.com/logstash-plugins/logstash-patterns-core/blob/master/patterns/grok-patterns)中，有关datetime的pattern如下：

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
	TIME (?!<[0-9])%{HOUR}:%{MINUTE}(?::%{SECOND})(?![0-9])
	# datestamp is YYYY/MM/DD-HH:MM:SS.UUUU (or something like it)
	DATE_US %{MONTHNUM}[/-]%{MONTHDAY}[/-]%{YEAR}
	DATE_EU %{MONTHDAY}[./-]%{MONTHNUM}[./-]%{YEAR}
	ISO8601_TIMEZONE (?:Z|[+-]%{HOUR}(?::?%{MINUTE}))
	ISO8601_SECOND (?:%{SECOND}|60)
	TIMESTAMP_ISO8601 %{YEAR}-%{MONTHNUM}-%{MONTHDAY}[T ]%{HOUR}:?%{MINUTE}(?::?%{SECOND})?%{ISO8601_TIMEZONE}?
	DATE %{DATE_US}|%{DATE_EU}
	DATESTAMP %{DATE}[- ]%{TIME}

接下来的例子中，只用YEAR, MONTHNUM2, MONTHDAY, HOUR, MINUTE, SECOND。进一步，考虑到为后续date filter提供异常输入，本例中不用MINUTE，而用\d{2}。

# 配置文件

- myconf/logstash/logstash_dt_01.conf

# 运行

~/elk/logstash-6.0.0/bin/logstash --path.settings ~/code_snippets/elk/myconf/logstash/config -f ~/code_snippets/elk/myconf/logstash/logstash_dt_01.conf 

# 测试数据

    2017-11-23T22:34:34,977
    2017/11/23 22:34:34,977
    2017-11-23 22:34:34.977
    2017-11-23 22:73:34.977
    2017-11-23 22:3a:34.977

# Result

see logstash_dt_01.result，部分如下：

    2017-11-23 22:34:34.977
    {
        "@timestamp" => 2017-11-25T02:14:13.090Z,
             "month" => "11",
              "hour" => "22",
              "year" => "2017",
          "@version" => "1",
              "host" => "flyingbird",
           "message" => "2017-11-23 22:34:34.977",
               "day" => "23",
            "minute" => "34",
            "second" => "34.977"
    }
    2017-11-23 22:73:34.977
    {
        "@timestamp" => 2017-11-25T02:16:40.375Z,
             "month" => "11",
              "hour" => "22",
              "year" => "2017",
          "@version" => "1",
              "host" => "flyingbird",
           "message" => "2017-11-23 22:73:34.977",
               "day" => "23",
            "minute" => "73",
            "second" => "34.977"
    }
    2017-11-23 22:3a:34.977
    {
          "@version" => "1",
              "host" => "flyingbird",
        "@timestamp" => 2017-11-25T02:16:47.127Z,
           "message" => "2017-11-23 22:3a:34.977",
              "tags" => [
            [0] "_grokparsefailure"
        ]
    }

# Question

接下来讨论@timestamp。