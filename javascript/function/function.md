Javascript - function

# Tools

Firefox + Firebug.

在Firebug上输入一段代码，“运行”，在Firefox的控制台上观察执行结果。

# Example - fib

    function fib(n) {
      if (n <= 1) {
        return 1;
      }
      
      return fib(n-1) + fib(n-2);
    }

    for (var i = 1; i < 10; i++) {
      console.log(i + ": " + fib(i));
    }

Result:  

    1: 1 
    2: 2 
    3: 3 
    4: 5 
    5: 8 
    6: 13 
    7: 21 
    8: 34 
    9: 55

# Example - Distance of two points

## Version 1

    function distance(p1, p2) {
        var dx = p1.x - p2.x;
        var dy = p1.y - p2.y;

        return Math.sqrt(dx * dx + dy * dy);
    }

    function dist_ex() {
        var p1 = {x : 1, y : 1};
        var p2 = {x : 4, y : 5};

        var dist = distance(p1, p2);
        console.log("distance: " + dist);
    }

    dist_ex(); // distance: 5

## Version 2

    var distance = function(p1, p2) {
        var dx = p1.x - p2.x;
        var dy = p1.y - p2.y;

        return Math.sqrt(dx * dx + dy * dy);
    }

    var dist_ex = function() {
        var p1 = {x : 1, y : 1};
        var p2 = {x : 4, y : 5};

        var dist = distance(p1, p2);
        console.log("distance: " + dist);
    }

    dist_ex(); // distance: 5

## Version 3

    var distance = function(p1, p2) {
        var dx = p1.x - p2.x;
        var dy = p1.y - p2.y;

        return Math.sqrt(dx * dx + dy * dy);
    }

    var dist_ex = function() {
        var p1 = {x : 1, y : 1};
        var p2 = {x : 4, y : 5};

        var dist = distance(p1, p2);
        console.log("distance: " + dist);
    }(); // distance: 5

## Version 4

    var dist_ex = function() {
        var p1 = {x : 1, y : 1};
        var p2 = {x : 4, y : 5};

        var distance = function(p1, p2) {
            var dx = p1.x - p2.x;
            var dy = p1.y - p2.y;

            return Math.sqrt(dx * dx + dy * dy);
        } (p1, p2);

        console.log("distance: " + distance);
    }(); // distance: 5

## Version 5

    var dist_ex = function() {
        var distance = function(p1, p2) {
            var dx = p1.x - p2.x;
            var dy = p1.y - p2.y;

            return Math.sqrt(dx * dx + dy * dy);
        } ({x : 1, y : 1}, {x : 4, y : 5});

        console.log("distance: " + distance);
    }(); // distance: 5

## Version 6

    var p1 = {x : 1, y : 1};
    p1.distance = function(p2) {
        var dx = p1.x - p2.x;
        var dy = p1.y - p2.y;

        return Math.sqrt(dx * dx + dy * dy);
    };

    var dist = p1.distance({x : 4, y : 5});
    console.log("distance: " + dist); // distance: 5

## Version 7

    function Point(x, y) {
        this.x = x;
        this.y = y;
    }

    Point.prototype = {
        distance: function(p) {
            var dx = this.x - p.x;
            var dy = this.y - p.y;

            return Math.sqrt(dx * dx + dy * dy);
        }
    };

    var p1 = new Point(1, 1);
    var p2 = new Point(4, 5);
    console.log("p1: " + JSON.stringify(p1)); // p1: {"x":1,"y":1} 
    console.log("distance: " + p1.distance(p2)); // distance: 5

## Version 8

    function Point(x, y) {
        this.x = x;
        this.y = y;
    }

    Point.prototype = {
        distance: function(p) {
            var dx = this.x - p.x;
            var dy = this.y - p.y;

            return Math.sqrt(dx * dx + dy * dy);
        },

        toString: function() {
            return "{x:" + this.x + ", y:" + y + "}";
        }
    };

    var p1 = new Point(1, 1);
    var p2 = new Point(4, 5);
    console.log("p1: " + p1); // p1: {"x":1, "y":1} 
    console.log("distance: " + p1.distance(p2)); // distance: 5

## Version 9

    function Point(x, y) {
        this.x = x;
        this.y = y;
    }

    Point.prototype.distance = function(p) {
        var dx = this.x - p.x;
        var dy = this.y - p.y;

        return Math.sqrt(dx * dx + dy * dy);
    };

    Point.prototype.toString = function() {
        return "{x:" + this.x + ", y:" + y + "}";
    };

    var p1 = new Point(1, 1);
    var p2 = new Point(4, 5);
    console.log("p1: " + p1); // p1: {"x":1, "y":1} 
    console.log("distance: " + p1.distance(p2)); // distance: 5