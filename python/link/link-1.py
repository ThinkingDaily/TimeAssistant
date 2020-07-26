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

def printLink(h):
    p = h
    while p:
        print(p.val, end = ' ')
        p = p.next
    print()

def testCreateLink():
    fail = False
    for nums in [
        ([]),
        ([1]),
        ([1, 2, 3]),
    ]:
        head = list2link(nums)
        printLink(head)
        nums2 = link2list(head)
        if nums != nums2:
            fail = True
            print("FAIL: {} -> {}".format(nums, nums2))
    
    return fail

if __name__ == '__main__':
    fail = testCreateLink()

    if fail:
        print("FAIL")
    else:
        print("PASS")
