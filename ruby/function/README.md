# Return Multiple Value

    def foo(x, y)
        return x + y, x - y
    end

    a, b = foo(3, 2)
    puts "a=#{a}, b=#{b}" # a=5, b=1
