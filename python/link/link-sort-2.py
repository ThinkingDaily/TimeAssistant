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

    def insert(theHead, theNode):
        if theHead is None:
            theNode.next = None
            theHead = theNode
            return theHead

        # insert before the head
        if theNode.val <= theHead.val:
            theNode.next = theHead
            theHead = theNode
            return theNode

        # insert after the head
        p = theHead
        while p.next:
            # in the midlle of link
            if theNode.val > p.val and theNode.val <= p.next.val:
                theNode.next = p.next
                p.next = theNode
                return theHead

            p = p.next

        # in the last of the link
        p.next = theNode
        theNode.next = None

        return theHead

    h = None
    p = head
    while p:
        q = p.next
        h = insert(h, p)
        p = q

    return h

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
