
class Foo
    class Titles
        NAME = "Name"
        AGE = "Age"
    end

    def initialize(name, age)
        @name = name
        @age = age
    end

    def to_s
        "Foo[%s: #{@name}, %s: #{@age}]" % [Titles::NAME, Titles::AGE]
    end

    def name
        return @name
    end

    def age
        return @age
    end

    def age=(age)
        @age = age
    end

    def incr
        incr_impl
    end

    def incr_impl
        @age += 1
    end
end

foo = Foo.new('Tom', 10)
foo.age = 12
foo.incr
puts "#{foo}" # Foo[Name: Tom, Age: 13]
