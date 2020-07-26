#!/usr/bin/env python3

class LinkNode:
    def __init__(self, val):
        self.val = val
        self.next = None

def list2link(values):
    length = len(values)
    if values is None or length == 0:
        return None

    head = LinkNode(values[0])
    p = head
    for i in range(1, length):
        q = LinkNode(values[i])
        p.next = q
        p = q

    return head

def link2list(head):
    values = []
    p = head
    while p:
        values.append(p.val)
        p = p.next

    return values

def sort(head):
    if head is None or head.next is None:
        return head

    nodes = []
    p = head
    while p:
        nodes.append(p)
        p = p.next

    indices = []
    def insert(pos):
        indicesLength = len(indices)
        if indicesLength == 0:
            indices.append(pos)
            return

        low = 0
        high = indicesLength - 1
        val = nodes[pos].val
        #print('indices: {}, insert: {}/{}'.format(indices, pos, val))
        while low <= high:
            mid = (low + high) // 2
            #print('low: {}, high: {}, mid: {}'.format(low, high, mid))
            midVal = nodes[indices[mid]].val
            if val < midVal:
                high = mid - 1
            else:
                low = mid + 1
        indices.insert(low, pos)

    length = len(nodes)
    for i in range(length):
        insert(i)

    for i in range(length - 1):
        nodes[indices[i]].next = nodes[indices[i + 1]]
    nodes[indices[-1]].next = None

    return nodes[indices[0]]

if __name__ == '__main__':
    fail = False
    for values in [
        [],
        [1],
        [4,2,1,3],
        [-1,5,3,4,0],
        [1, 2, 3] * 3,
    ]:
        expect = values[:]
        expect.sort()

        #print('current values:', values)
        head = list2link(values)
        hs = sort(head) # Head of Sorted link
        hsValues = link2list(hs)
        
        if expect == hsValues:
            print("PASS: ({}) -> {})".format(
                values, hsValues))
        else:
            fail = True
            print("FAIL: ({}) -> {}, not {}".format(
                values, hsValues, expect))
        
    if fail:
        print("FAIL")
    else:
        print("PASS")
