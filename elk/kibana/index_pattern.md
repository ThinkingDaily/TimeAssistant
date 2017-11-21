Kibana-index pattern

# Management Tab

在Management Tab中定义index pattern，如果这个index pattern对应的index包括了timestamp字段，那么'Time Filter field name'会自动显示该字段。

# timestamp

如果index包括了timestamp类型的字段，那么可以针对该字段做数据分析(time-based comparisons)。

两点说明：

- 如果index不包括时间字段，那么在创建index pattern的时候，Kibana就不会显示time fileter.
- 如果index包括了时间字段，但并不需要做基于时间的分析，那么就选择"I don’t want to use the Time Filter".

# Date

注意Elasticsearch的日期格式。

并设置某个index pattern为缺省值。比如，"2017-11-21 15:51:00"被认为是字符串，而"2017/11/21 15:51:00"被认为是时间。前者存储为string类型，后者存储为Date类型。

# Default Pattern & Delete

可以设置任何一个index pattern为default pattern，后续的分析就针对这个index pattern。

在Management中，还可以删除某个index pattern。

# Fields List 

Management中会显示index pattern的所有fields。