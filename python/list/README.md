# append a single item or multiple items

	>>> a = [1, 2, 'one']
	>>> b = [3, 4]
	>>> a.append(5)
	>>> a
	[1, 2, 'one', 5]
	>>> a.extend(b)
	>>> a
	[1, 2, 'one', 5, 3, 4]

# sort and reverse sort

	>>> a.sort()
	>>> a
	[1, 2, 3, 4, 5, 'one']
	>>> a.sort(reverse=True)
	>>> a
	['one', 5, 4, 3, 2, 1]
	>>> 
