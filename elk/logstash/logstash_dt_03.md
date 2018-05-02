# Overview

本文主要讨论conditional。

# 问题由来

Logstash处理日志后，通常要存储到Elasticsearch或其它的地方。对于错误的日志，Logstash无法解析，这种情况下的数据就不需要存储到Elasticsearch等地发。为此在output的时候，要做判断。

# Conditional

参考[conditional.md]。

