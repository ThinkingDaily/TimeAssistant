#!/usr/bin/env python3

class LinkNode:
    def __init__(self, val):
        self.val = val
        self.next = None

def mergeSort(nodes, length):
    count = 1
    indices = [i for i in range(length)]
    helper = [0]*length
    while count < length:
        for i in range(0, length, 2 * count):
            merge(i, count, length, nodes, indices, helper)
        
        count *= 2
        #nums = helper[:]
        #print('count: {}, nums: {}'.format(count, nums))
    
    return indices

def merge(i, count, length, nodes, indices, helper):
    # [ left... | right...]
    # left:  [i,         i + count - 1]
    # right: [i + count, i + 2 * count - 1]
    
    #print('merge(), i: {}, count: {}'.format(i, count))
    leftStart = i
    leftEnd = min(i + count, length)
    rightStart = i + count
    rightEnd = min(i + 2 * count, length)

    p = leftStart
    q = rightStart
    pos = leftStart
    while True:
        #print('p: {}, q: {}'.format(p, q))
        if p >= leftEnd:
            for k in range(q, rightEnd):
                helper[pos] = indices[k]
                pos += 1
            break

        if q >= rightEnd:
            for k in range(p, leftEnd):
                helper[pos] = indices[k]
                pos += 1

            break

        if nodes[indices[p]].val <= nodes[indices[q]].val:
            helper[pos] = indices[p]
            p += 1
        else:
            helper[pos] = indices[q]
            q += 1
        pos += 1
        #print('helper:', helper)
    
    for k in range(i, min(i + count * 2, length)):
        indices[k] = helper[k]

    #print('helper:', helper)

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

    length = len(nodes)
    indices = mergeSort(nodes, length)
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
