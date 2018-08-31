# Tool

http://rubular.com/

# Example

    dt_strings = ["Now is 2018/08/30 17:14:20.829128.", "Now is 2018/08/301 17:14:20.829128."]
    dt_regexp = /^(?:.+)(\d{4}\/\d{2}\/\d{2})\x20(\d{2}:\d{2}:\d{2})\.(\d{6})(?:.+)$/m
    for item in dt_strings
        matches = dt_regexp.match(item)
        if matches
            date = matches[1]
            time = matches[2]
            microseconds = matches[3].to_i()
            puts "Matched. Date: #{date}, Time: #{time}, Microseconds: #{microseconds}"
        else
            puts "Not match. Value: #{item}"
        end
    end

Result:

    Matched. Date: 2018/08/30, Time: 17:14:20, Microseconds: 829128
    Not match. Value: Now is 2018/08/301 17:14:20.829128.
