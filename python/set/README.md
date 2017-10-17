foo()...
s1: set([1, 3, 5, 7, 8, 10])
s2: set([2, 4, 6, 8, 10, 12])
common: set([8, 10])
only in s1: set([1, 3, 5, 7])
only in s2: set([12, 2, 4, 6])
bar()...
s1: set(['Helen', 'Tom', 'John', 'tom'])
s2: set(['Mary', 'Helen', 'Jerry', 'Tom'])
common: set(['Tom', 'Helen'])
only in s1: set(['John', 'tom'])
only in s2: set(['Mary', 'Jerry'])
baz()...
s1: set([(0, 1), (1, 0), (0, 0), (1, 1)])
s2: set([(0, 1), (-1, -1), (-1, 0), (1, 1)])
common: set([(0, 1), (1, 1)])
only in s1: set([(1, 0), (0, 0)])
only in s2: set([(-1, 0), (-1, -1)])
